#ifndef INPUT_H_
#define INPUT_H_

enum {
  PRESS_KEY_UP,
  PRESS_KEY_DOWN,
  PRESS_KEY_LEFT,
  PRESS_KEY_RIGHT,
  PRESS_KEY_BUTTON_0,
  PRESS_KEY_BUTTON_1,
  PRESS_KEY_MAX
};

void initInput();
void updateInput();
void endInput();

#ifndef INPUT_C_
extern int pressKey[PRESS_KEY_MAX];
extern int edgeKey[PRESS_KEY_MAX];
#endif

#endif
