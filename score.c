#include <SDL/SDL.h>
#include "score.h"
#include "printText.h"

extern SDL_Surface *gScreen;

// static int score;
int score;
char str[5]; // scoreの最大桁数は5

// 得点を加える
void addScore(void)
{
  score += 10;

  // scoreが上限に達したら0に戻す
  if ( score >= MAX_SCORE ) {
    score = 0;
  }
  sprintf(str, "%05d", score);
}

void initScore(void)
{
  score = 0;
  sprintf(str, "%05d", score);
}

void updateScore(void)
{
  printText(gScreen, 0, 0, str);
}

int getScore(void)
{
  return score;
}
