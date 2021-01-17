#ifndef PRINTTEXT_H_
#define PRINTTEXT_H_

void initPrintText(void);
void endPrintText(void);
void printText(SDL_Surface *screen, int x, int y, char *str);

#define FONTFILE "img/font.png"
#define FONTWIDTH  16
#define FONTHEIGHT 32

#endif
