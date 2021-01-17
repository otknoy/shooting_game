#include "title.h"
#include "def.h"
#include "input.h"
#include "printText.h"
#include "score.h"

SDL_Surface *gTitle;

static int life;

extern SDL_Surface *gScreen;
extern void (*p)(void);

void initScore(void);

void initTitle(void)
{
  p = titleProc;
  gTitle = IMG_Load("img/title.png");
  // life = 3; // 残機の設定
}

void endTitle(void)
{
  SDL_FreeSurface(gTitle);
  initLifeProc();
  // initGameProc();
}

void titleProc(void)
{
  SDL_BlitSurface( gTitle, NULL, gScreen, NULL );

  if ( edgeKey[PRESS_KEY_BUTTON_0] ) {
    endTitle();
  }
}

void initLifeProc(void)
{
  initScore(); // test
  life = 3;
  p = lifeProc;
}

void lifeProc(void)
{
  static int count = 0;
  static int waitFrame = 60;
  char *str;

  if (life == 0) {
    p = gameoverProc;
  }

  sprintf(str, "LIFE X %2d", life);
  printText(gScreen, (SCREEN_WIDTH - (FONTWIDTH * 9)) / 2, (SCREEN_HEIGHT-FONTHEIGHT) / 2, str);
	    
  count++;

  if (count == waitFrame) {
    initGameProc();
    count = 0;
    life--;
  }
}

void gameoverProc(void)
{
  char *str;
  sprintf(str, "SCORE %08d", getScore());
  printText(gScreen, (SCREEN_WIDTH - (FONTWIDTH * 8)) / 2, (SCREEN_HEIGHT-FONTHEIGHT) / 2, "GAMEOVER");
  printText(gScreen, (SCREEN_WIDTH - (FONTWIDTH * 14)) / 2, ((SCREEN_HEIGHT-FONTHEIGHT) / 2) + FONTHEIGHT, str);

  if ( edgeKey[PRESS_KEY_BUTTON_0] ) {
    initTitle();
  }
}
