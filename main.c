#include "def.h"
#include "title.h"
#include "stage.h"
#include "object.h"
#include "checkHitRect.h"
#include "score.h"
#include "input.h"
#include "printText.h"

SDL_Surface *gScreen; // メインスクリーン
int currentFrame = 0;
// int life; // 残機
void (*p)(void); // ゲームの状態を分けるための関数ポインタ
 
int init();       // 初期化処理
void end();       // 終了処理
int PollEvent();  // イベント処理
void titleProc();    // タイトル画面の処理
void lifeProc(); // 残機表示画面
void initGameProc(); // ゲームの初期化
void endGameProc();  // ゲームの終了処理
void gameProc();     // ゲーム中の処理
void waitGame();  // ウェイトをかける

int main(void)
{ 
  if ( init() ) {
    printf("初期化失敗\n");
    return 0;
  }

  initInput();
  initPrintText();
  initTitle();

  // メインループ
  while ( 1 ) {
    // 画面塗りつぶし
    SDL_FillRect(gScreen, NULL, 0x000000); // black

    updateInput();

    // ゲームの状態によって処理を分ける
    (*p)();

    SDL_Flip( gScreen );

    if ( !PollEvent() ) {
      break;
    }

    waitGame();

    currentFrame++;
    // printf("frame:%4d\n", currentFrame);
  }
  
  endPrintText();
  endInput();
  end();
  
  return 0;
}

// 初期化処理
int init(void)
{
  if ( SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_TIMER) < 0 ) {
    SDL_GetError();
    return -1;
  }

  SDL_WM_SetCaption(GAME_CAPTION, NULL);

  // メインスクリーンの初期化
  gScreen = SDL_SetVideoMode(SCREEN_WIDTH,
			     SCREEN_HEIGHT,
			     SCREEN_BPP,
			     SDL_HWSURFACE );

  SDL_ShowCursor(SDL_DISABLE); // マウスカーソル非表示

  // SDL_mixerの初期化  there is no soundcard と表示されるが問題ないのでそのまま
  if ( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) ) {
    exit(-1);
  }

  loadObject(); // オブジェクトの画像、効果音を読み込む

  return 0;
}

// 終了処理
void end(void)
{
  freeObject();
  // SDLの終了
  SDL_Quit();
}

// イベント処理
int PollEvent()
{
  SDL_Event ev;
  SDLKey *key;
  while ( SDL_PollEvent(&ev) ) {
    switch ( ev.type ) {
    case SDL_QUIT: // ウィンドウの×ボタンが押されたときなど
      {
	return 0;
	break;
      }
    case SDL_KEYDOWN: // キーボードからの入力があったとき
      {     
	{
	  key = &(ev.key.keysym.sym); // どのキーが押されたのかを取得
	  if ( *key == 27 ) { // ESCキー
	    return 0;
	  }
	}
	break;
      }
    }
  }
  return 1;
}

// ゲームの初期化
void initGameProc(void)
{
  p = gameProc;

  // initScore();

  initStage();
  
  initPlayer();
  initPlayerShot();
  initEnemy();
  initEnemyShot();
}

void endGameProc(void)
{
  endStage();

  p = lifeProc;
}

// ゲーム中の処理
void gameProc(void)
{
  checkHitPlayer();
  checkHitPlayerShot();

  stage();

  updateEnemyShot();
  updateEnemy();
  updatePlayerShot();
  updatePlayer();

  updateScore();
}

// ウェイトをかける
void waitGame(void)
{
  static Uint32 preCount; // 前回からの途中経過を保持しておく変数
  float waitTime = 1000.0f / (float)FPS_MAX;
  Uint32 waitCount = (Uint32)(waitTime + 0.5f); // 間を開けたい時間
  Uint32 nowCount;
  Uint32 interval; // 前回からの経過時間
  Uint32 delayTime;

  if ( preCount ) { // 2回目以降
    nowCount = SDL_GetTicks();         // 現在の時間を取得し、
    interval = nowCount - preCount;    // 前回から経過時間を計算する。

    if ( interval < waitCount ) {        // 待ち足りない場合、
      delayTime = waitCount - interval;  // どのくらいの時間待てばよいかを計算し、
      SDL_Delay(delayTime);              // その時間だけ待つ。
    }
  }
  preCount = SDL_GetTicks(); // waitGame終了時の時間を取得
}
