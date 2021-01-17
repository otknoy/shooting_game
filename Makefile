# Makefile

# マクロ定義
program	= shooting
objs	= main.o input.o title.o object.o checkHitRect.o stage.o score.o printText.o
CC	= gcc
option  = -Wall -g -lm
sdl	= `sdl-config --libs --cflags` -lSDL_image -lSDL_mixer
sdl	= `sdl-config --libs --cflags` -lSDL_image -lSDL_mixer


# プライマリターゲット
$(program): $(objs)
	$(CC) -o $@ $(objs) $(option) $(sdl)

# サフィックスルール
.c.o:
	$(CC) -c $< $(sdl)

# ヘッダーファイルの依存関係
main.o: def.h title.h stage.h object.h checkHitRect.h score.h input.h printText.h
input.o: input.h
title.o: title.h def.h input.h printText.h
object.o: object.h def.h  input.h
checkHitRect.o: checkHitRect.h object.h score.h
stage.o: stage.h def.h object.h
score.o: score.h printText.h


# ファイル削除用ターゲット
.PHONY: clean
clean:
	$(RM) $(program) $(objs)
