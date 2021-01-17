#ifndef CHECKHITRECT_H_
#define CHECKHITRECT_H_

int checkHitRect(SDL_Rect *r1, SDL_Rect *r2);
void checkHitPlayer();
void checkHitPlayerShot();

#define PLAYER_HITRECT_W 24
#define PLAYER_HITRECT_H 24
#define ENEMY_HITRECT_W 24
#define ENEMY_HITRECT_H 24
#define PLAYER_SHOT_HITRECT_W 10
#define PLAYER_SHOT_HITRECT_H 10
#define ENEMY_SHOT_HITRECT_W 8
#define ENEMY_SHOT_HITRECT_H 8

#endif
