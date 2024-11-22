#ifndef KEY.H
#define KEY .H
#include <Windows.h>
#include <ctime>

#include "../TETRIODEP/Grid.h"
class Key {
  private:
    // key states
    enum class State {
        CLICKED, // when first clicked
        PRESSED, // pressed
        INACTIVE // not being clicked
    };
    State currState = State::INACTIVE;
    State prevState = State::INACTIVE;

    // the type of key
    int key;

    //time it takes until key is repeted rapidly in miliseconds
    unsigned int debounce;

    unsigned int debounceEnd;

    // VK_LEFT 	0x25 	LEFT ARROW key
    // VK_UP 	0x26 	UP ARROW key
    // VK_RIGHT 	0x27 	RIGHT ARROW key
    // VK_DOWN 	0x28 	DOWN ARROW keys
  public:
    Key(int k, unsigned int debounceMS);
    void update();
    bool onClick();
    bool triggered();
    bool onRelease();

    //chrono related functions
    auto getTimeMS();
};
#endif