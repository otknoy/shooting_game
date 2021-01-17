#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string.h>
#include <ctype.h>
#include "printText.h"

SDL_Surface *Font;

void initPrintText(void)
{
  Font = IMG_Load(FONTFILE);

  if (Font == NULL) {
    printf("%s is not found.\n", FONTFILE);
  }
}

void endPrintText(void)
{
  SDL_FreeSurface(Font);
}

void printText(SDL_Surface *screen, int x, int y, char *str)
{
  char *p;
  SDL_Rect src, dst;

  dst.x = x;
  dst.y = y;
  
  src.w = FONTWIDTH;
  src.h = FONTHEIGHT;

  for (p = str; *p != '\0'; p++) {
    if (isdigit(*p)) {
      src.x = FONTWIDTH * (*p - '0');
      src.y = FONTHEIGHT * 0;
      SDL_BlitSurface(Font, &src, screen, &dst);
    } else if (isupper(*p)) {
      src.x = FONTWIDTH * ((*p - 'A') % 10);
      src.y = FONTHEIGHT * (1 + ((*p - 'A') / 10));
      SDL_BlitSurface(Font, &src, screen, &dst);
    }
    dst.x += FONTWIDTH;
  }
}
