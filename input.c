#define INPUT_C_

#include <SDL/SDL.h>
#include "input.h"

int pressKey[PRESS_KEY_MAX];
int edgeKey[PRESS_KEY_MAX];

static SDL_Joystick *gJoyStick;

// 入力初期化処理
void initInput()
{
  // ジョイスティックの初期化
  if ( SDL_NumJoysticks() > 0 ) {
    gJoyStick = SDL_JoystickOpen( 0 );
  }
}

// 入力終了処理
void endInput()
{
  if ( gJoyStick ) {
    SDL_JoystickClose( gJoyStick );
  }
}

// 入力処理
void updateInput()
{
  int newPressKey[PRESS_KEY_MAX];
  int i;

  for ( i = 0; i < PRESS_KEY_MAX; i++ ) {
    newPressKey[i] = 0;
  }

  if ( gJoyStick ) { // ジョイスティックがある時
    SDL_JoystickUpdate();
    if ( SDL_JoystickGetButton( gJoyStick, 0 )  == SDL_PRESSED ) newPressKey[PRESS_KEY_BUTTON_0] = 1;
    if ( SDL_JoystickGetButton( gJoyStick, 1 )  == SDL_PRESSED ) newPressKey[PRESS_KEY_BUTTON_1] = 1;
    if ( SDL_JoystickGetAxis( gJoyStick, 1 ) < -256 ) newPressKey[PRESS_KEY_UP] = 1;
    if ( SDL_JoystickGetAxis( gJoyStick, 1 ) >  256 ) newPressKey[PRESS_KEY_DOWN] = 1;
    if ( SDL_JoystickGetAxis( gJoyStick, 0 ) < -256 ) newPressKey[PRESS_KEY_LEFT] = 1;
    if ( SDL_JoystickGetAxis( gJoyStick, 0 ) >  256 ) newPressKey[PRESS_KEY_RIGHT] = 1;
  }

  // キーボード
  Uint8 *keys=SDL_GetKeyState(NULL);
  if ( keys[SDLK_UP] == SDL_PRESSED ) newPressKey[PRESS_KEY_UP] = 1;
  if ( keys[SDLK_DOWN] == SDL_PRESSED ) newPressKey[PRESS_KEY_DOWN] = 1;
  if ( keys[SDLK_LEFT] == SDL_PRESSED ) newPressKey[PRESS_KEY_LEFT] = 1;
  if ( keys[SDLK_RIGHT] == SDL_PRESSED ) newPressKey[PRESS_KEY_RIGHT] = 1;
  if ( keys['z'] == SDL_PRESSED ) newPressKey[PRESS_KEY_BUTTON_0] = 1;
  if ( keys['x'] == SDL_PRESSED ) newPressKey[PRESS_KEY_BUTTON_1] = 1;

  for( i = 0 ; i < PRESS_KEY_MAX; i++ ){
    edgeKey[i] = 0;
    if ( !pressKey[i] && newPressKey[i] ) { edgeKey[i] = 1; }
    pressKey[i] = newPressKey[i];
  }
}
