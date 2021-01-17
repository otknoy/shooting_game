#ifndef OBJECT_H_
#define OBJECT_H_

// image file path
#define PLAYER_IMAGE      "img/player.png"
#define PLAYERSHOT_IMAGE  "img/player_shot.png"
#define ENEMY_A_IMAGE     "img/enemyA.png"
#define ENEMY_B_IMAGE     "img/enemyB.png"
#define ENEMY_C_IMAGE     "img/enemyC.png"
#define ENEMYSHOT_IMAGE   "img/enemy_shot.png"
// sound effect file path
#define PLAYERSHOT_SE     "sounds/se_pyuun.wav"

// 敵の種類
enum enemyType{
  ENEMY_TYPE_A,
  ENEMY_TYPE_B,
  ENEMY_TYPE_C,
  ENEMY_TYPE_MAX
};

// プレイヤーのデータ
#define PLAYER_WIDTH       48
#define PLAYER_HEIGHT      48
#define PLAYER_SPEED        6
// プレイヤーショットのデータ
#define PLAYER_SHOT_WIDTH  12
#define PLAYER_SHOT_HEIGHT 12
#define PLAYER_SHOT_SPEED  20
#define PLAYER_SHOT_MAX     2
// 敵のデータ
#define ENEMY_WIDTH        32
#define ENEMY_HEIGHT       32
#define ENEMY_SPEED         5
#define ENEMY_MAX          16
// 敵ショットのデータ
#define ENEMY_SHOT_WIDTH   12
#define ENEMY_SHOT_HEIGHT  12
#define ENEMY_SHOT_SPEED    6
#define ENEMY_SHOT_MAX     32

// オブジェクトデータの構造体
typedef struct objData OBJECT_DATA;
struct objData {
  int w, h; // image size
  double x, y; // position
  double vx, vy;
  int state;
  int frame;
  SDL_Rect *hitrect;
  void (*movePattern)(OBJECT_DATA *obj);
};

// オブジェクト(player etc)の状態
enum {
  DEAD,
  ALIVE
};

// load
void loadObject(); // 画像、効果音の読み込み

// free
void freeObject(); // 開放

// プレイヤー
void initPlayer();
void endPlayer();
void updatePlayer();

// プレイヤーショット
void initPlayerShot();
void createPlayerShot(double x, double y);
void updatePlayerShot();

// 敵
void initEnemy();
void createEnemy(double x, double y, void (*movePattern)(OBJECT_DATA *obj));
void updateEnemy();

// 敵ショット
void initEnemyShot();
void createEnemyShot(double x, double y);
void updateEnemyShot();

// 自機に向かってくるショットの移動距離
void getVXVY(OBJECT_DATA *obj01, OBJECT_DATA *obj02);

// 敵の移動パターン
void mPatStraight(OBJECT_DATA *obj);
void mPatSin(OBJECT_DATA *obj);
void mPatZ(OBJECT_DATA *obj);

#endif
