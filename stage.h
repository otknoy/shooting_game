#ifndef STAGE_H_
#define STAGE_H

/* このmp3をロードしても音がでなかったのでWAVEにした */
/* 原因不明 */
#define STAGE_BGM "sounds/bgm_stagebgm_09_hq.wav" // BGMファイルのパス
/* 解像度の高い画像をSDL_imageを使って読み込むと */
/* 処理が重くなったのでBMPにした */
#define BACKGROUND_IMG "img/background.bmp" // 背景の画像ファイルのパス

#define BG_SCROLL_SPEED 1 // 背景のスクロールスピード

// ステージ
void initStage();
void endStage();
void drawBG();
void stage();

#endif
