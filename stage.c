#include "stage.h"
#include "def.h"
#include "object.h"

SDL_Surface *gBackGround;
Mix_Music *stageBGM01;

SDL_Rect rectBG; // 背景の表示位置設定のため

extern SDL_Surface *gScreen;
extern int gameState;

// 敵出現時のx座標の定義
enum {
  A = (SCREEN_HEIGHT / 8 * 1) - (ENEMY_HEIGHT / 2),
  B = (SCREEN_HEIGHT / 8 * 2) - (ENEMY_HEIGHT / 2),
  C = (SCREEN_HEIGHT / 8 * 3) - (ENEMY_HEIGHT / 2),
  D = (SCREEN_HEIGHT / 8 * 4) - (ENEMY_HEIGHT / 2),
  E = (SCREEN_HEIGHT / 8 * 5) - (ENEMY_HEIGHT / 2),
  F = (SCREEN_HEIGHT / 8 * 6) - (ENEMY_HEIGHT / 2),
  G = (SCREEN_HEIGHT / 8 * 7) - (ENEMY_HEIGHT / 2)
};

static int stageFrame;

void initStage()
{
  /*
  // 背景画像のロード
  if (!(gBackGround = SDL_LoadBMP(BACKGROUND_IMG))) {
    printf("Couldn't load file: %s\n", BACKGROUND_IMG);
  }
  */
  // BGMのロード
  if (!(stageBGM01 = Mix_LoadMUS(STAGE_BGM))) {
    printf("Couldn't load file: %s\n", STAGE_BGM);
  }

  { // 背景表示位置の初期化
    rectBG.x = 0;
    rectBG.y = 0;
    rectBG.w = SCREEN_WIDTH;
    rectBG.h = SCREEN_HEIGHT;
  }

  Mix_PlayMusic(stageBGM01, -1);

  stageFrame = 0;
}

void endStage()
{
  // BGM停止
  Mix_HaltMusic();

  // stageBGM01の解放
  Mix_FreeMusic(stageBGM01);
}

void drawBG(void)
{
    rectBG.x += BG_SCROLL_SPEED;
    if (rectBG.x >= (gBackGround->w - SCREEN_WIDTH)) {
      rectBG.x = 0;
    }
    SDL_BlitSurface(gBackGround, &rectBG, gScreen, NULL);
}

void stage()
{
  // drawBG();

  switch ( stageFrame ) {
  case 120:
    createEnemy(SCREEN_WIDTH, A, mPatZ);
    break;
  case 135:
    createEnemy(SCREEN_WIDTH, A, mPatZ);
    break;
  case 150:
    createEnemy(SCREEN_WIDTH, A, mPatZ);
    break;
  case 165:
    createEnemy(SCREEN_WIDTH, A, mPatZ);
    break;

  case 255:
    createEnemy(SCREEN_WIDTH, G, mPatZ);
    break;
  case 270:
    createEnemy(SCREEN_WIDTH, G, mPatZ);
    break;
  case 285:
    createEnemy(SCREEN_WIDTH, G, mPatZ);
    break;
  case 300:
    createEnemy(SCREEN_WIDTH, G, mPatZ);
    break;

  case 390:
    createEnemy(SCREEN_WIDTH, B, mPatStraight);
    createEnemy(SCREEN_WIDTH, F, mPatStraight);
    break;
  case 405:
    createEnemy(SCREEN_WIDTH, B, mPatStraight);
    createEnemy(SCREEN_WIDTH, F, mPatStraight);
    break;
  case 420:
    createEnemy(SCREEN_WIDTH, B, mPatStraight);
    createEnemy(SCREEN_WIDTH, F, mPatStraight);
    break;
  case 435:
    createEnemy(SCREEN_WIDTH, B, mPatStraight);
    createEnemy(SCREEN_WIDTH, F, mPatStraight);
    break;

  case 525:
    createEnemy(SCREEN_WIDTH, A, mPatSin);
    break;
  case 540:
    createEnemy(SCREEN_WIDTH, A, mPatSin);
    break;
  case 555:
    createEnemy(SCREEN_WIDTH, A, mPatSin);
    createEnemy(SCREEN_WIDTH, D, mPatSin);
    break;
  case 575:
    createEnemy(SCREEN_WIDTH, A, mPatSin);
    createEnemy(SCREEN_WIDTH, D, mPatSin);
    break;
  case 590:
    createEnemy(SCREEN_WIDTH, D, mPatSin);
    createEnemy(SCREEN_WIDTH, G, mPatSin);
    break;
  case 604:
    createEnemy(SCREEN_WIDTH, D, mPatSin);
    createEnemy(SCREEN_WIDTH, G, mPatSin);
    break;
  case 620:
    createEnemy(SCREEN_WIDTH, G, mPatSin);
    break;
  case 635:
    createEnemy(SCREEN_WIDTH, G, mPatSin);
    stageFrame = 0;
    break;
  }


  // printf("%3d\n", stageFrame);
  stageFrame++;
}
