#include "../TETRIODEP/Key.h"
#include <FEHLCD.h>
#include <chrono>
#include <ctime>
#include <iostream>

Key::Key(int k, unsigned int debounceMS) {
    key = k;
    debounce = debounceMS;
    debounceEnded = false;
}

void Key::update() {
    prevState = currState;

    unsigned long long currentTime = getTimeMS();

    bool keyPressed = GetAsyncKeyState(key);
    if (keyPressed && currState == State::INACTIVE) {
        // first press
        currState = State::CLICKED;
        // start debounce timer
        debounceEnd = currentTime + debounce;
        // reset debounce flag
        debounceEnded = false;

        std::cout << "CLICKED";
        std::cout << "Current Time : " << currentTime << std::endl;
        std::cout << "debounce end: " << debounceEnd << std::endl;
        // std::cout << "debounceEnded: " << debounceEnded << std::endl;
        //  std::cout<<"CLICKED";
    } else if (keyPressed && currState == State::CLICKED) {
        // if debounce hasent ended yet then dont switch stat
        std::cout << "debounceEnded: " << debounceEnded << std::endl;
        // after first press so switch to pressed state
        currState = State::PRESSED;

        // std::cout<<"PRESSED";
    } else if (currState == State::PRESSED && currentTime >= debounceEnd) {
        debounceEnded = true;
    }
    if (!keyPressed && currState != State::INACTIVE) {
        currState = State::INACTIVE;
        debounceEnded = false;
        // std::cout<<"INACTIVE";
    }
}

// returns true breifly when first clicked
bool Key::onClick() { return currState == State::CLICKED; }
// returns true while button is held
bool Key::triggered() { return currState == State::PRESSED; }
bool Key::onRelease() { return currState == State::INACTIVE && prevState == State::PRESSED; }

unsigned long long Key::getTimeMS() {
    // get the current time from the system clock
    auto now = std::chrono::system_clock::now();

    // convert the current time to time since epoch
    auto duration = now.time_since_epoch();

    // convert duration to milliseconds
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

    return milliseconds;
}

bool Key::onDebounceEnd() { return debounceEnded; }