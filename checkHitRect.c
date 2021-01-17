#include <SDL/SDL.h>
#include "checkHitRect.h"
#include "object.h"
#include "score.h"

extern OBJECT_DATA playerData;
extern OBJECT_DATA playerShotData[PLAYER_SHOT_MAX];
extern OBJECT_DATA enemyData[ENEMY_MAX];
extern OBJECT_DATA enemyShotData[ENEMY_SHOT_MAX];

// 当たり判定 
int checkHitRect(SDL_Rect *r1, SDL_Rect *r2)
{
  if ( ((r1->x) < (r2->x + r2->w)) &&
       ((r2->x) < (r1->x + r1->w)) &&
       ((r1->y) < (r2->y + r2->h)) &&
       ((r2->y) < (r1->y + r1->h))   ) {
    return 1;
  } else {
    return 0;
  }
}

// プレイヤーとの当たり判定
void checkHitPlayer()
{
  int i;
  SDL_Rect player, enemy, enemyShot;
  
  player.x = playerData.x + ((playerData.w - PLAYER_HITRECT_W) / 2);
  player.y = playerData.y + ((playerData.h - PLAYER_HITRECT_H) / 2);
  player.w = PLAYER_HITRECT_W;
  player.h = PLAYER_HITRECT_H;

  // 敵と
  for ( i = 0; i < ENEMY_MAX; i++ ) {  
    if ( enemyData[i].state == ALIVE ) {
      enemy.x = enemyData[i].x + ((enemyData[i].w - ENEMY_HITRECT_W) / 2);
      enemy.y = enemyData[i].y + ((enemyData[i].h - ENEMY_HITRECT_H) / 2);
      enemy.w = ENEMY_HITRECT_W;
      enemy.h = ENEMY_HITRECT_H;
      
      if ( checkHitRect(&player, &enemy) ) {
        playerData.state = DEAD;
      }
    }
  }

  // 敵ショットと
  for ( i = 0; i < ENEMY_SHOT_MAX; i++ ) {
    if ( enemyShotData[i].state == ALIVE ) {
      enemyShot.x = enemyShotData[i].x + ((enemyShotData[i].w - ENEMY_SHOT_HITRECT_W) / 2);
      enemyShot.y = enemyShotData[i].y + ((enemyShotData[i].h - ENEMY_SHOT_HITRECT_H) / 2);
      enemyShot.w = ENEMY_SHOT_HITRECT_W;
      enemyShot.h = ENEMY_SHOT_HITRECT_H;

      if ( checkHitRect(&player, &enemyShot) ) {
	playerData.state = DEAD;
      }
    }
  }
}

// プレイヤーショットとの当たり判定
void checkHitPlayerShot()
{
  int i, j;
  SDL_Rect playerShot, enemy01;

  for ( i = 0; i < PLAYER_SHOT_MAX; i++ ) {
    if ( playerShotData[i].state == ALIVE ) {
      playerShot.x = playerShotData[i].x + ((playerShotData[i].w - PLAYER_SHOT_HITRECT_W) / 2);
      playerShot.y = playerShotData[i].y + ((playerShotData[i].h - PLAYER_SHOT_HITRECT_H) / 2);
      playerShot.w = PLAYER_SHOT_HITRECT_W;
      playerShot.h = PLAYER_SHOT_HITRECT_H;
      
      for ( j = 0; j < ENEMY_MAX; j++ ) {
	if ( enemyData[j].state == ALIVE ) {
	  enemy01.x = enemyData[j].x + ((enemyData[j].w - ENEMY_HITRECT_W) / 2);
	  enemy01.y = enemyData[j].y + ((enemyData[j].h - ENEMY_HITRECT_H) / 2);
	  enemy01.w = ENEMY_HITRECT_W;
	  enemy01.h = ENEMY_HITRECT_H;
	  
	  if ( checkHitRect(&playerShot, &enemy01) ) {
	    playerShotData[i].state = DEAD;
	    enemyData[j].state = DEAD;
	    // 敵を倒したら得点追加
	    addScore();
	  }
	}
      }
    }
  }
}
