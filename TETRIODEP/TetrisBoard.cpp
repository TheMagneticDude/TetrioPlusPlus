#include <iostream>
#include <optional>

#include "FEHRandom.h"
#include "Grid.h"
#include "Input.h"
#include "Settings.h"
#include "Sound.h"
#include "TetrisBoard.h"
#include "Tetromino.h"
#include <FEHLCD.h>

#include <iomanip>

// Author: Ojas
// initialize tetrisboard with a coordinate (top left corner)
TetrisBoard::TetrisBoard(int _boardX, int _boardY, PlayerSettings &_settings, Statistics &playerStats,
                         TetrisBoard *opponent)
    : grid(10, 22), fallingGrid(3, 3), holdGrid(3, 3), input(_settings), opponent(opponent) {
    settings = &_settings;
    // these are where the board is built around in world coords (top left corner)
    boardX = _boardX;
    boardY = _boardY;

    for (int i = 0; i < 5; i++) {
        auto mino = getNextFromBag();
        queue.push_back(mino);
        queueGrids.push_back(createGrid(mino, TetrominoOrientation::H));
    }

    lastGravity = std::chrono::high_resolution_clock::now();
    timeStart = std::chrono::high_resolution_clock::now();
    startNewFalling();
    ended = false;
    linesCleared = 0;
    fourtyLineTime = 0;
}

// Author: Nathan
// draws the entire tetrisboard
void TetrisBoard::draw() {
    drawBorder();
    grid.draw(boardX, boardY);
    holdGrid.draw(boardX - (holdGrid.width + 1 + getSpawnOffset(hold.value_or(Tetromino::E))) * SCALE,
                  boardY - 17 * SCALE);

    int shadowY = fallingY;
    while (!checkCollision(fallingGrid, fallingX, shadowY - 1)) {
        shadowY--;
    }
    fallingGrid.draw(boardX + fallingX * SCALE, boardY - shadowY * SCALE, true);

    fallingGrid.draw(boardX + fallingX * SCALE, boardY - fallingY * SCALE);
    for (int i = 0; i < queue.size(); i++) {
        queueGrids[i].draw(boardX + (12 + getSpawnOffset(queue[i])) * SCALE, boardY - 19 * SCALE + i * 3 * SCALE);
    }
}

// Author: Nathan
// draws border around board excluding top
void TetrisBoard::drawBorder() {
    int borderScale = 4;
    // draws boarder around grid
    int pos_x = boardX;
    int pos_y = boardY;
    // bottom boarders
    LCD.SetFontColor(WHITE);

    // bottom boarder
    LCD.FillRectangle(pos_x - borderScale, pos_y, SCALE * (grid.width) + 2 * borderScale, borderScale);

    // left and right boarders

    // Left boarder
    // LCD.FillRectangle(pos_x - SCALE, pos_y - SCALE*2, SCALE, SCALE * (grid.height + 2));
    LCD.FillRectangle(pos_x - borderScale, pos_y - grid.height * SCALE, borderScale,
                      SCALE * (grid.height) + borderScale);
    // right boarder
    // LCD.FillRectangle(pos_x + SCALE * grid.width, pos_y - SCALE*2, SCALE, SCALE * (grid.height + 2));
    LCD.FillRectangle(pos_x - borderScale + SCALE * grid.width + borderScale, pos_y - grid.height * SCALE, borderScale,
                      SCALE * (grid.height) + borderScale);
}

// Author: Nathan
// Draw the time and number of lines cleared next to the tetris board
void TetrisBoard::drawStats() {
    LCD.SetFontColor(WHITE);
    // display time
    LCD.WriteAt(timeDisplay, boardX - (timeDisplay.length() * LCD.getCharWidth()) - 10,
                (boardY + (SCALE * grid.height)) + 10);
    std::string linesClearedText = "LC: " + std::to_string(linesCleared);
    LCD.WriteAt(linesClearedText, boardX - (linesClearedText.length() * LCD.getCharWidth()) - 10,
                (boardY + (SCALE * grid.height)) + 30);
}

// Author: Nathan
// Play a blip sound
void *TetrisBoard::playSound(void *vargp) {
    PlayAudioFile("assets/TetrisBlip.wav");
    return NULL;
}

// Author: Ojas
// Handle the main game logic for the tetris board
void TetrisBoard::update() {
    auto currentTime = std::chrono::high_resolution_clock::now();
    float elapsedTime = std::chrono::duration<float>(currentTime - timeStart).count();
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << elapsedTime;
    // to display time
    timeDisplay = stream.str();

    

    drawStats();

    input.update();

    // Handle Left/Right movement keys
    bool pressedLeft = input.keyLeft.newPress();
    bool pressedRight = input.keyRight.newPress();
    // pthread_t soundThreadID;

    if (pressedLeft && !pressedRight) {
        if (!checkCollision(fallingGrid, fallingX - 1, fallingY)) {
            // play sound
            // pthread_create(&soundThreadID, NULL, TetrisBoard::playSound, NULL);
            // pthread_join(soundThreadID, NULL);
            PlayAudioFile("assets/TetrisBlip.wav");
            fallingX--;
            // Reset lock delay
            onGround = false;
        }
    } else if (pressedRight && !pressedLeft) {
        if (!checkCollision(fallingGrid, fallingX + 1, fallingY)) {
            // play sound TODO: NEEDS TO SHORTEN WAV FILE BUT I DONT HAVE DAVINCHI RESOLVE HERE SO I CANT
            // pthread_create(&soundThreadID, NULL, TetrisBoard::playSound, NULL);
            // pthread_join(soundThreadID, NULL);
            PlayAudioFile("assets/TetrisBlip.wav");
            fallingX++;
            // Reset lock delay
            onGround = false;
        }
    }

    updateRotation();

    // Get the time since gravity was last applied
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> lastGravityDuration = now - lastGravity;
    float lastGravitySecs = lastGravityDuration.count();

    // The soft drop key applies the Soft Drop Facter (SDF) to gravity
    float effectiveGravityRate = gravityRate;
    if (input.softDrop.pressed()) {
        effectiveGravityRate /= settings->handling.sdf;
        // pthread_create(&soundThreadID, NULL, TetrisBoard::playSound, NULL);
        // pthread_join(soundThreadID, NULL);
        PlayAudioFile("assets/TetrisBlip.wav");
    }

    // Gravity
    if (lastGravitySecs >= effectiveGravityRate) {
        lastGravity = now;
        if (!checkCollision(fallingGrid, fallingX, fallingY - 1)) {
            fallingY--;
        } else if (!onGround) {
            onGround = true;
            startedOnGround = now;
        }
    }

    // Lock delay
    if (onGround) {
        std::chrono::duration<float> durationOnGround = now - startedOnGround;
        float secsOnGround = durationOnGround.count();
        if (secsOnGround >= 1.0) {
            settleGrid(fallingGrid, fallingX, fallingY);
            startNewFalling();
            return;
        }
    }

    // Handle hard drops by moving the falling mino as far down as possible and settling it there
    if (input.hardDrop.newPress()) {
        int y = fallingY;
        while (!checkCollision(fallingGrid, fallingX, y - 1)) {
            y--;
        }
        PlayAudioFile("assets/TetrisBlip.wav");
        settleGrid(fallingGrid, fallingX, y);
        startNewFalling();
        return;
    }

    if (input.swapHold.newPress() && !didHold) {
        std::optional<Tetromino> oldHold = hold;
        hold = fallingMino;
        holdGrid = createGrid(fallingMino, TetrominoOrientation::H);
        startNewFalling(oldHold);
        didHold = true;
        // pthread_create(&soundThreadID, NULL, TetrisBoard::playSound, NULL);
        // pthread_join(soundThreadID, NULL);
        PlayAudioFile("assets/TetrisBlip.wav");
    }
}

// Author: Ojas
// Handle rotating a tetromino (one of the most complex parts of the game logic)
void TetrisBoard::updateRotation() {
    TetrominoOrientation rotTable[3][4] = {
        // Clockwise rotation
        {TetrominoOrientation::R, TetrominoOrientation::U, TetrominoOrientation::H, TetrominoOrientation::L},
        // Counterclockwise rotation
        {TetrominoOrientation::L, TetrominoOrientation::H, TetrominoOrientation::U, TetrominoOrientation::R},
        // 180 rotation
        {TetrominoOrientation::U, TetrominoOrientation::L, TetrominoOrientation::R, TetrominoOrientation::H}};

    bool didRotate = false;
    TetrominoOrientation newRot = fallingRotation;
    pthread_t soundThreadID;

    // Check to see if the different rotation keys were pressed
    if (input.rotateCW.newPress()) {
        newRot = rotTable[0][static_cast<int>(newRot)];
        didRotate = true;
        // pthread_create(&soundThreadID, NULL, TetrisBoard::playSound, NULL);
        // pthread_join(soundThreadID, NULL);
        PlayAudioFile("assets/TetrisBlip.wav");
    }
    if (input.rotateCCW.newPress()) {
        newRot = rotTable[1][static_cast<int>(newRot)];
        didRotate = true;
        // pthread_create(&soundThreadID, NULL, TetrisBoard::playSound, NULL);
        // pthread_join(soundThreadID, NULL);
        PlayAudioFile("assets/TetrisBlip.wav");
    }
    if (input.rotate180.newPress()) {
        newRot = rotTable[2][static_cast<int>(newRot)];
        didRotate = true;
        // pthread_create(&soundThreadID, NULL, TetrisBoard::playSound, NULL);
        // pthread_join(soundThreadID, NULL);
        PlayAudioFile("assets/TetrisBlip.wav");
    }

    if (!didRotate)
        return;

    // Reset lock delay
    onGround = false;

    typedef std::vector<std::pair<int, int>> offsetTableTy[4];

    // Tables were derived from Harddrop Wiki
    // https://harddrop.com/wiki/SRS#:~:text=the%20player%20rotates.-,How%20Guideline%20SRS%20Really%20Works,-The%20internal%20true
    offsetTableTy jlstzOffset = {
        // 0
        {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
        // R
        {{0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}},
        // L
        {{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}},
        // 2
        {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}},
    };
    offsetTableTy iOffset = {
        // 0
        {{0, 0}, {-1, 0}, {+2, 0}, {-1, 0}, {+2, 0}},
        // R
        {{-1, 0}, {0, 0}, {0, 0}, {0, +1}, {0, -2}},
        // L
        {{0, +1}, {0, +1}, {0, +1}, {0, -1}, {0, +2}},
        // 2
        {{-1, +1}, {+1, +1}, {-2, +1}, {+1, 0}, {-2, 0}},
    };
    offsetTableTy oOffset = {
        // 0
        {{0, 0}},
        // R
        {{0, -1}},
        // L
        {{-1, 0}},
        // 2
        {{-1, -1}},
    };

    offsetTableTy *offsetTablePtr;
    switch (fallingMino) {
    case Tetromino::J:
    case Tetromino::L:
    case Tetromino::S:
    case Tetromino::T:
    case Tetromino::Z:
        offsetTablePtr = &jlstzOffset;
        break;
    case Tetromino::I:
        offsetTablePtr = &iOffset;
        break;
    case Tetromino::O:
        offsetTablePtr = &oOffset;
        break;
    default:
        break;
    }
    offsetTableTy &offsetTable = *offsetTablePtr;

    Grid newGrid = createGrid(fallingMino, newRot);

    int offsetX;
    int offsetY;
    bool foundOffset = false;
    for (int offsetNum = 0; offsetNum < offsetTable[0].size(); offsetNum++) {
        auto startOffset = offsetTable[static_cast<int>(fallingRotation)][offsetNum];
        auto endOffset = offsetTable[static_cast<int>(newRot)][offsetNum];
        offsetX = endOffset.first - startOffset.first;
        offsetY = endOffset.second - startOffset.second;
        bool collides = checkCollision(newGrid, fallingX - offsetX, fallingY - offsetY);
        if (!collides) {
            foundOffset = true;
            break;
        }
    }

    if (foundOffset) {
        fallingGrid = newGrid;
        fallingX -= offsetX;
        fallingY -= offsetY;
        fallingRotation = newRot;
    }
}

// Author: Ojas
// Pick a new tetromino to start falling and then start it falling
void TetrisBoard::startNewFalling(std::optional<Tetromino> mino) {
    int garbageHole = Random.RandInt() % 10;
    for (int i = 0; i < pendingGarbage; i++) {
        for (int y = grid.height - 1; y > 0; y--) {
            for (int x = 0; x < 10; x++) {
                auto mino = grid.getAtPos(x, y - 1);
                grid.setAtPos(mino, x, y);
            }
        }
        for (int x = 0; x < 10; x++) {
            if (x == garbageHole) {
                grid.setAtPos(Tetromino::E, x, 0);
            } else {
                grid.setAtPos(Tetromino::G, x, 0);
            }
        }
    }
    pendingGarbage = 0;

    if (!mino.has_value()) {
        mino = getNextFromQueue();
    }
    fallingMino = *mino;
    fallingGrid = createGrid(*mino, TetrominoOrientation::H);
    fallingRotation = TetrominoOrientation::H;
    fallingX = 3 + getSpawnOffset(fallingMino);
    fallingY = 19;
    lastGravity = std::chrono::high_resolution_clock::now();
    didHold = false;
    onGround = false;
    if (checkCollision(fallingGrid, fallingX, fallingY)) {
        // TODO: game over
        std::cout << "Game Over!" << std::endl;
        ended = true;
        // std::exit(0);
    }
}

// Author: Ojas
// Check to see if the falling tetromino is colliding with the settled peices on the board.
bool TetrisBoard::checkCollision(Grid with, int withX, int withY) {
    for (int x = 0; x < with.width; x++) {
        for (int y = 0; y < with.height; y++) {
            Tetromino withMino = with.getAtPos(x, y);
            Tetromino gridMino;
            if (withX + x < 0 || withX + x >= 10 || withY + y < 0) {
                gridMino = Tetromino::G;
            } else {
                gridMino = grid.getAtPos(withX + x, withY + y);
            }
            if (withMino != Tetromino::E && gridMino != Tetromino::E) {
                return true;
            }
        }
    }
    return false;
}

// Author: Ojas
// Create the smaller grid used to hold a single tetromino
Grid TetrisBoard::createGrid(Tetromino type, TetrominoOrientation orientation) {
    int gridWidth = type == Tetromino::I ? 5 : 3;
    Grid newGrid(gridWidth, gridWidth);
    std::vector<int> newData;
    switch (type) {
    case Tetromino::I:
        newData = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        break;
    case Tetromino::J:
        newData = {0, 0, 0, 2, 2, 2, 2, 0, 0};
        break;
    case Tetromino::L:
        newData = {0, 0, 0, 3, 3, 3, 0, 0, 3};
        break;
    case Tetromino::O:
        newData = {0, 0, 0, 0, 4, 4, 0, 4, 4};
        break;
    case Tetromino::S:
        newData = {0, 0, 0, 5, 5, 0, 0, 5, 5};
        break;
    case Tetromino::T:
        newData = {0, 0, 0, 6, 6, 6, 0, 6, 0};
        break;
    case Tetromino::Z:
        newData = {0, 0, 0, 0, 7, 7, 7, 7, 0};
        break;
    default:
        std::cerr << "Tried to create grid with invalid tetromino type: " << static_cast<int>(type) << std::endl;
    }

    for (int i = 0; i < newData.size(); i++) {
        newGrid.data[i] = static_cast<Tetromino>(newData[i]);
    }

    // These cases intentionally fall through. This means that L creates 3 rotations, U rotates twice, and R rotates
    // once.
    switch (orientation) {
    case TetrominoOrientation::L:
        newGrid = newGrid.rotate90();
    case TetrominoOrientation::U:
        newGrid = newGrid.rotate90();
    case TetrominoOrientation::R:
        newGrid = newGrid.rotate90();
    default:
        break;
    }

    return newGrid;
}

// Author: Ojas
// Move the tetromino from the small falling grid to the larger settled grid
void TetrisBoard::settleGrid(Grid from, int fromX, int fromY) {
    for (int x = 0; x < from.width; x++) {
        for (int y = 0; y < from.height; y++) {
            Tetromino mino = from.getAtPos(x, y);
            if (mino == Tetromino::E)
                continue;
            grid.setAtPos(mino, fromX + x, fromY + y);
        }
    }

    int linesClearedNow = 0;

    // Check to see if any new lines can be cleared
    for (int y = 0; y < 20; y++) {
        bool hasSpace = false;
        for (int x = 0; x < 10; x++) {
            if (grid.getAtPos(x, y) == Tetromino::E) {
                hasSpace = true;
            }
        }

        if (!hasSpace) {
            clearLine(y);
            linesClearedNow++;
            y--;
        }
    }

    // increase linesCleared stat for this board
    linesCleared += linesClearedNow;

    // TODO: t-spins
    int attack;
    switch (linesClearedNow) {
    case 2:
        attack = 1;
        break;
    case 3:
        attack = 2;
        break;
    case 4:
        attack = 4;
        break;
    default:
        attack = 0;
    }
    attackOpponent(attack);

    bool isPC = true;
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 10; x++) {
            if (grid.getAtPos(x, y) != Tetromino::E) {
                isPC = false;
            }
        }
    }

    if (isPC) {
        attackOpponent(10);
    }
}

// Author: Ojas
// Clear out one line on the board and then shift all lines above it down
void TetrisBoard::clearLine(int startY) {
    for (int y = startY; y < grid.height - 1; y++) {
        for (int x = 0; x < 10; x++) {
            auto mino = grid.getAtPos(x, y + 1);
            grid.setAtPos(mino, x, y);
        }
    }

    // Make sure to clear out the top most row
    for (int x = 0; x < 10; x++) {
        grid.setAtPos(Tetromino::E, x, grid.height - 1);
    }
}

// Author: Ojas
// Pick a new tetromino from the 7 bag
Tetromino TetrisBoard::getNextFromBag() {
    if (bag.size() == 0) {
        bag = {Tetromino::I, Tetromino::J, Tetromino::L, Tetromino::O, Tetromino::S, Tetromino::T, Tetromino::Z};
    }

    int idx = Random.RandInt() % bag.size();
    auto mino = bag[idx];
    bag.erase(bag.begin() + idx);
    return mino;
}

// Author: Ojas
// Pick a new tetromino from already displayed queue
Tetromino TetrisBoard::getNextFromQueue() {
    auto mino = queue[0];
    queue.erase(queue.begin());
    queueGrids.erase(queueGrids.begin());

    auto next = getNextFromBag();
    queue.push_back(next);
    queueGrids.push_back(createGrid(next, TetrominoOrientation::H));
    return mino;
}

// Author: Nathan
// Get the number of lines cleared
int TetrisBoard::getLinesCleared() { return linesCleared; }

// Author: Nathan
// Check to see if the game has ended
bool TetrisBoard::gameEnded() { return ended; }

// Author: Nathan
// Check to see if the win condition for 40 lines has ended
bool TetrisBoard::fourtyLinesEnded() { 
    if (linesCleared >= 40) {
        fourtyLineTime = std::stof(timeDisplay);
    }
    return linesCleared >= 40 ;
    }

// Author: Nathan
// Get the time taken to clear 40 lines
float TetrisBoard::getFourtyLinesClearedTime() { return fourtyLineTime; }

// Author: Ojas
// Add lines that are pending to become garbage after the player
void TetrisBoard::receiveLines(int numLines) { pendingGarbage += numLines; }

// Author: Ojas
// Send lines to the other opponent if there's no more to cancel
void TetrisBoard::attackOpponent(int numLines) {
    if (!opponent)
        return;
    if (pendingGarbage >= numLines) {
        pendingGarbage -= numLines;
    } else {
        opponent->receiveLines(numLines - pendingGarbage);
        pendingGarbage = 0;
    }
}
