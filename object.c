#include "def.h"
#include "object.h"
#include "input.h"
#include <math.h>

extern SDL_Surface *gScreen;
extern int currentFrame;

SDL_Surface *gPlayer;
SDL_Surface *gPlayerShot;
SDL_Surface *gEnemy[ENEMY_TYPE_MAX];
SDL_Surface *gEnemyShot;

Mix_Chunk *sPlayerShot;

OBJECT_DATA playerData;
OBJECT_DATA playerShotData[PLAYER_SHOT_MAX];
OBJECT_DATA enemyData[ENEMY_MAX];
OBJECT_DATA enemyShotData[ENEMY_SHOT_MAX];

void endGameProc(void); // とりあえず

void loadObject()
{
  // loal image
  if (!(gPlayer = IMG_Load(PLAYER_IMAGE))) {
    printf("Couldn't load file: %s\n", PLAYER_IMAGE);
  }
  if (!(gPlayerShot = IMG_Load(PLAYERSHOT_IMAGE))) {
    printf("Couldn't load file: %s\n", PLAYERSHOT_IMAGE);
  }

  if (!(gEnemy[ENEMY_TYPE_A] = IMG_Load(ENEMY_A_IMAGE))) {
    printf("Couldn't load file: %s\n", ENEMY_A_IMAGE);
  }
  if (!(gEnemy[ENEMY_TYPE_B] = IMG_Load(ENEMY_B_IMAGE))) {
    printf("Couldn't load file: %s\n", ENEMY_B_IMAGE);
  }
  if (!(gEnemy[ENEMY_TYPE_C] = IMG_Load(ENEMY_C_IMAGE))) {
    printf("Couldn't load file: %s\n", ENEMY_B_IMAGE);
  }
  
  if (!(gEnemyShot = IMG_Load(ENEMYSHOT_IMAGE))) {
    printf("Couldn't load file: %s\n", ENEMYSHOT_IMAGE);
  }

  // load sound effect
  if (!(sPlayerShot = Mix_LoadWAV(PLAYERSHOT_SE))) {
    printf("Couldn't load file: %s\n", PLAYERSHOT_SE);
  }
}

void freeObject()
{
  int i;

  SDL_FreeSurface(gPlayer);
  SDL_FreeSurface(gPlayerShot);

  for (i = 0; i < ENEMY_TYPE_MAX; i++) {
    SDL_FreeSurface(gEnemy[i]);
  }
  SDL_FreeSurface(gEnemyShot);

  Mix_FreeChunk(sPlayerShot);
}

/* player関連 */
void initPlayer()
{
  // プレイヤーデータの初期化
  playerData.w = PLAYER_WIDTH;
  playerData.h = PLAYER_HEIGHT;
  playerData.x = 0.0;
  playerData.y = (SCREEN_HEIGHT - gPlayer->w) / 2.0;
  playerData.vx = PLAYER_SPEED;
  playerData.vy = PLAYER_SPEED;
  playerData.state = ALIVE;
  playerData.frame = 0;
  playerData.movePattern = NULL;
}

void endPlayer()
{
  SDL_FreeSurface(gPlayer);
}

void updatePlayer()
{
  // 移動
  if ( pressKey[PRESS_KEY_UP   ] ) {
    playerData.y -= playerData.vy;
  }
  if ( pressKey[PRESS_KEY_DOWN ] ) {
    playerData.y += playerData.vy;
  }
  if ( pressKey[PRESS_KEY_LEFT ] ) {
    playerData.x -= playerData.vx;
  }
  if ( pressKey[PRESS_KEY_RIGHT] ) {
    playerData.x += playerData.vx;
  }

  // zを押したら玉を発射
  if ( pressKey[PRESS_KEY_BUTTON_0] ) {
    createPlayerShot( playerData.x + ((gPlayer->w - gPlayerShot->w) / 2.0),
		      playerData.y + ((gPlayer->h - gPlayerShot->h) / 2.0) );
  }

  // 殺すtest
  if ( edgeKey[PRESS_KEY_BUTTON_1] ) {
    playerData.state = DEAD;
  }

  // 画面外にでないように
  if ( playerData.x < 0 ) {
    playerData.x = 0;
  }
  if ( playerData.x > (SCREEN_WIDTH - gPlayer->w ) ) {
    playerData.x = (SCREEN_WIDTH  - gPlayer->w);
  }
  if ( playerData.y < 0 ) {
    playerData.y = 0;
  }
  if ( playerData.y > (SCREEN_HEIGHT - gPlayer->h) ) {
    playerData.y = (SCREEN_HEIGHT - gPlayer->w);
  }


  // もし死んでいたら
  if ( playerData.state == DEAD ) {
    endGameProc();
  }

  // drawPlayer
  SDL_Rect rect;
  rect.x = playerData.x;
  rect.y = playerData.y;
  SDL_BlitSurface( gPlayer, NULL, gScreen, &rect );
}

void initPlayerShot()
{
  int i;

  for ( i = 0; i < PLAYER_SHOT_MAX; i++ ) {
    playerShotData[i].w = PLAYER_SHOT_WIDTH;
    playerShotData[i].h = PLAYER_SHOT_HEIGHT;
    playerShotData[i].x = 0.0;
    playerShotData[i].y = 0.0;
    playerShotData[i].vx = 0.0;
    playerShotData[i].vy = 0.0;
    playerShotData[i].state = DEAD;
    playerShotData[i].frame = 0;
    playerShotData[i].movePattern = NULL;
  }
}

void createPlayerShot(double x, double y)
{
  static int playerShotFrame = 0;
  int i;

  // 前に呼び出されてから数フレーム以上経過していたら
  if ( currentFrame >= playerShotFrame + 8 ) {
    for ( i = 0; i < PLAYER_SHOT_MAX; i++ ) {
      if ( playerShotData[i].state == DEAD ) {
	playerShotData[i].x = x;
	playerShotData[i].y = y;
	playerShotData[i].vx = PLAYER_SHOT_SPEED;
	playerShotData[i].vy = 0.0;
	playerShotData[i].state = ALIVE;
		
	playerShotFrame = currentFrame;

	// 発射音を鳴らす
	Mix_PlayChannel( -1, sPlayerShot, 0); 
	
	break;
      }
    }
  }
  // printf("createPlayerShot!\n");
}

void updatePlayerShot()
{
  int i;
  
  for ( i = 0; i < PLAYER_SHOT_MAX; i++ ) {
    if ( playerShotData[i].state == ALIVE ) {
      playerShotData[i].x += playerShotData[i].vx;
      
      if ( playerShotData[i].x > SCREEN_WIDTH       ||
	   playerShotData[i].x <= -(gPlayerShot->w) ||
	   playerShotData[i].y > SCREEN_HEIGHT      ||
	   playerShotData[i].y <= -(gPlayerShot->h)   ) {
	playerShotData[i].state = DEAD;
      }

      // drawPlayerShot
      SDL_Rect rect;
      rect.x = playerShotData[i].x;
      rect.y = playerShotData[i].y;
      SDL_BlitSurface( gPlayerShot, NULL, gScreen, &rect );
    }
  }
}


/* enemy関連 */
void initEnemy()
{
  int i;
    
  for ( i = 0; i < ENEMY_MAX; i++ ) {
    enemyData[i].w = ENEMY_WIDTH;
    enemyData[i].h = ENEMY_HEIGHT;
    enemyData[i].x = 0.0;
    enemyData[i].y = 0.0;
    enemyData[i].vx = 0.0;
    enemyData[i].vy = 0.0;
    enemyData[i].state = DEAD;
    enemyData[i].frame = 0;
    enemyData[i].movePattern = NULL;
  }
}

void createEnemy(double x, double y, void (*movePattern)(OBJECT_DATA *obj))
{
  int i;
  
  // 敵データの配列から使っていない要素を探して
  // そこへ新しく作られた敵データを入れる
  for ( i = 0; i < ENEMY_MAX; i++ ) {
    if ( enemyData[i].state == DEAD ) {
      enemyData[i].x = x;
      enemyData[i].y = y;
      enemyData[i].vx = 0.0;
      enemyData[i].vy = 0.0;
      enemyData[i].state = ALIVE;
      enemyData[i].frame = 0;
      enemyData[i].movePattern = movePattern;
      break;
    }
  }
  // printf("createEnemy!\n");
}

void updateEnemy()
{
  int i;

  // 敵データの配列を順に調べ、ALIVEの場合は更新する
  for ( i = 0; i < ENEMY_MAX; i++ ) {
    if ( enemyData[i].state == ALIVE ) {
      enemyData[i].frame++;

      // 移動パターン vx, vyを計算
      (*enemyData[i].movePattern)(&enemyData[i]);
      // 移動する
      enemyData[i].x += enemyData[i].vx;
      enemyData[i].y += enemyData[i].vy;

      // ショット 90frame毎
      if (enemyData[i].frame == 60) {
      createEnemyShot( enemyData[i].x + ((enemyData[i].w - gEnemyShot->w ) / 2.0),
		       enemyData[i].y + ((enemyData[i].h - gEnemyShot->h ) / 2.0) );
      }
       
      // 画面外へ出た場合は殺す
      if ( enemyData[i].x > SCREEN_WIDTH  ||
	  enemyData[i].x <= -(enemyData[i].w)  ||
	   enemyData[i].y > SCREEN_HEIGHT ||
	   enemyData[i].y <= -(enemyData[i].h)    ) {
	enemyData[i].state = DEAD;
      }
      
      // drawEnemy  
      SDL_Rect rect;
      rect.x = enemyData[i].x;
      rect.y = enemyData[i].y;
      if (enemyData[i].movePattern == mPatStraight) {
	SDL_BlitSurface(gEnemy[ENEMY_TYPE_A], NULL, gScreen, &rect);
      } else if (enemyData[i].movePattern == mPatSin) {
	SDL_BlitSurface(gEnemy[ENEMY_TYPE_B], NULL, gScreen, &rect);
      } else if (enemyData[i].movePattern == mPatZ) {
	SDL_BlitSurface(gEnemy[ENEMY_TYPE_C], NULL, gScreen, &rect);
      }
    }
    // printf("%2d: %d\n", i, enemyData[i].state);
  }
}

void initEnemyShot()
{
  int i;

  for ( i = 0; i < ENEMY_SHOT_MAX; i++ ) {
    enemyShotData[i].w = ENEMY_SHOT_WIDTH;
    enemyShotData[i].h = ENEMY_SHOT_HEIGHT;
    enemyShotData[i].x = 0.0;
    enemyShotData[i].y = 0.0;
    enemyShotData[i].vx = 0;
    enemyShotData[i].vy = 0.0;
    enemyShotData[i].state = DEAD;
    enemyShotData[i].frame = 0;
    enemyShotData[i].movePattern = NULL;
  }
}

void createEnemyShot(double x, double y)
{
  int i;
  
  // 配列から使っていない要素を探して
  // そこへ新しく作られた敵ショットデータを入れる
  for ( i = 0; i < ENEMY_SHOT_MAX; i++ ) {
    if ( enemyShotData[i].state == DEAD ) {
      enemyShotData[i].x = x;
      enemyShotData[i].y = y;
      enemyShotData[i].state = ALIVE;
      
      // ショットの移動方向を決定
      getVXVY(&enemyShotData[i], &playerData);
      
      break;
    }
  }
}

void updateEnemyShot()
{
  int i;

  // 配列を順に調べ、ALIVEの場合は更新する
  for ( i = 0; i < ENEMY_SHOT_MAX; i++ ) {
    if ( enemyShotData[i].state == ALIVE ) {
      // 移動する
      enemyShotData[i].x += enemyShotData[i].vx;
      enemyShotData[i].y += enemyShotData[i].vy;

      // 画面外へ出た場合は殺す
      if ( enemyShotData[i].x > SCREEN_WIDTH      ||
	   enemyShotData[i].x <= -(gEnemyShot->w) ||
	   enemyShotData[i].y > SCREEN_HEIGHT     ||
	   enemyShotData[i].y <= -(gEnemyShot->h)    ){
	enemyShotData[i].state = DEAD;
      }
      
      // drawEnemyShot  
      SDL_Rect rect;
      rect.x = enemyShotData[i].x;
      rect.y = enemyShotData[i].y;
      SDL_BlitSurface( gEnemyShot, NULL, gScreen, &rect );
    }
  }
}


/* 移動距離、敵の移動パターンなど */
// 自機に向かってくるショットの移動距離
void getVXVY(OBJECT_DATA *obj01, OBJECT_DATA *obj02)
{
  double x, y, theta;
  
  // obj01->x と (*obj).x は同じ意味
  x = (obj02->x + (obj02->w / 2)) - (obj01->x + (obj01->w / 2));
  y = (obj02->y + (obj02->h / 2)) - (obj01->y + (obj01->h / 2));
  theta = atan2(x ,y);
  
  obj01->vx = sin(theta) * ENEMY_SHOT_SPEED;
  obj01->vy = cos(theta) * ENEMY_SHOT_SPEED;
}

// 移動パターン straight
void mPatStraight(OBJECT_DATA *obj)
{
  if (obj->frame == 1) {
    obj->vx = -ENEMY_SPEED;
  }
}

// 移動パターン sin
void mPatSin(OBJECT_DATA *obj)
{
  obj->vy = cos(PI * ((double)obj->frame/40.0)) * 5.0;
  obj->vx = -3.0;
}

// 移動パターン z
void mPatZ(OBJECT_DATA *obj)
{
  if (obj->frame == 1) {
    obj->vx = -ENEMY_SPEED;
  } else if (obj->frame == SCREEN_WIDTH/ENEMY_SPEED) {
    obj->vx = ENEMY_SPEED;
    if (obj->y < (SCREEN_HEIGHT/2)) {
      obj->vy = 0.75 * ENEMY_SPEED;
    } else {
      obj->vy = 0.75 * -ENEMY_SPEED;
    }
  } else if (obj->y > playerData.y && (obj->y + 32) < (playerData.y + 48)
	     && obj->x > playerData.x) {
    obj->vx = -ENEMY_SPEED;
    obj->vy = 0.0;
  }
}
