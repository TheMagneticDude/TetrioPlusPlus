#include "Menu.h"
#include "Button.h"
#include "Sound.h"

#include <FEHImages.h>
#include <FEHLCD.h>
#include <FEHRandom.h>
#include <chrono>
#include <iomanip>
#include <string>

Menu::Menu()
    : start(0 + buttonoffset, "1 v 1", BLUE, DARKBLUE),
      singleplayer(30 + buttonoffset, "40 Line Clear", BLUE, DARKBLUE),
      stats(60 + buttonoffset, "Stats", BLUE, DARKBLUE), settings(90 + buttonoffset, "Settings", BLUE, DARKBLUE),
      instructions(120 + buttonoffset, "Instructions", BLUE, DARKBLUE),
      credits(150 + buttonoffset, "Credits", BLUE, DARKBLUE), back(10, 0, "Exit", BLUE, DARKBLUE),
      board1(board1Loc[0], board1Loc[1], set.p1Settings, playerStats, &board2),
      board2(board2Loc[0], board2Loc[1], set.p2Settings, playerStats, &board1),
      singleBoard(singleBoardLoc[0], singleBoardLoc[1], set.p1Settings, playerStats, NULL), optionsPage(set) {
    // initialize button instances
    onStartclicked = false;
    // start playing background music
    // this will error im not sure why but it compiles so who cares
    mciSendString(TEXT("play \"assets/TetrisBackground.mp3\""), NULL, 0, 0);
    PlayBackgroundMusic();

    gameEnded = false;
    std::string extension = ".png";
    std::string frame = "2";
    // Tetrio Text generated using : https://erikdemaine.org/fonts/tetris/?text=%2B%2B&speed=10
    //  menuBackground.Open("assets/TetrioBackgroundTetrio.png");
    menuBackground.Open("assets/TetrioBackground.png");
    menuPlusPlus.Open("assets/TetrioPlusSign.png");
    playBackground.Open("assets/TetrioGameBackground-2.png");
    singleBackground.Open("assets/TetrioGameBackground.png");
    confetti.Open("assets/TetrisConfetti.png");
    creditsImage.Open("assets/CreditsPage.png");
    howToPlay.Open("assets/TetrioHowToPlay.png");

    std::string fileName = "assets/TitleFrames/frame_";
    std::string fileType = ".png";
    std::string fileNumber = to_string(currFrame);
    std::string filePath = fileName + fileNumber + fileType;
    animatedText.Open(filePath.c_str());

    timeStart = std::chrono::high_resolution_clock::now();
    currFrame = 1;
};

// disables a button
// Author: Nathan
void Menu::disable(Button &b) { b.disable(); }

// updates menu pages
// Author: Nathan
void Menu::update() {

    currTime = std::chrono::high_resolution_clock::now();

    if (currOption == MenuOption::Back) {
        currOption = MenuOption::None_;
    }
    bool menuActive = currOption == MenuOption::None_; // if in subpage

    if (menuActive) {
        // draws background
        // background was made by me in blender hence why its so ugly lol
        // FEHImage background;
        // background.Open("assets/TetrioBackground-2.png");

        auto timeToNextFrame = std::chrono::duration_cast<std::chrono::milliseconds>(currTime - nextFrame);
        if (timeToNextFrame.count() >= frameTime && currFrame < maxFrames) {
            animatedText.Close();
            nextFrame = currTime + std::chrono::milliseconds(frameTime);
            currFrame++;
            // update text
            std::string fileName = "assets/TitleFrames/frame_";
            std::string fileType = ".png";
            std::string fileNumber = to_string(currFrame);
            std::string filePath = fileName + fileNumber + fileType;
            animatedText.Open(filePath.c_str());
        }
        menuBackground.Draw(0, 0);
        menuPlusPlus.Draw(0,0);
        animatedText.Draw(60,-30);

        start.updateButtonState();
        singleplayer.updateButtonState();
        settings.updateButtonState();
        stats.updateButtonState();
        instructions.updateButtonState();
        credits.updateButtonState();

        // update current option selected if a button triggers
        if ((renderSubPage(start))) {

            if (currOption != MenuOption::Start) {
                currOption = MenuOption::Start;
                onStartclicked = true;
            }
        }
        if (renderSubPage(singleplayer)) {
            if (currOption != MenuOption::Single) {
                currOption = MenuOption::Single;
                onSingleClicked = true;
            }
        }
        if (renderSubPage(settings)) {
            currOption = MenuOption::Settings;
        }
        if (renderSubPage(stats)) {
            currOption = MenuOption::Stats;
        }
        if (renderSubPage(instructions)) {
            currOption = MenuOption::Instructions;
        }
        if (renderSubPage(credits)) {
            currOption = MenuOption::Credits;
        }
    } else {
        // removes menu buttons and draws back button
        remove();
        back.updateButtonState();

        if (renderSubPage(back)) {
            currOption = MenuOption::Back;
            back.remove();
            currFrame = 1;
            // back to menu
        }
    }
}

// returns true when its time to render a subpage for a given button
// Author: Nathan
bool Menu::renderSubPage(Button &b) { return b.onButtonReleased(); }

// returns true if page should be active
// Author: Nathan
bool Menu::isPageActive(MenuOption page) { return currOption == page; }

// renders back
// Author: Nathan
void Menu::renderBackButton() { back.updateButtonState(); }

// remmoves back
// Author: Nathan
void Menu::removeBack() { back.remove(); }

// removes all menu buttons
// Author: Nathan
void Menu::remove() {
    // clears all menu buttons
    start.remove();
    singleplayer.remove();
    settings.remove();
    stats.remove();
    instructions.remove();
    credits.remove();
}

// removes back and sets up return to menu
// Author: Nathan
void Menu::returnToMenu() {
    currOption = MenuOption::Back;
    back.remove();
    // back to menu
}

// moved logic from main to here
// Author: Nathan
// Author: Ojas Landge
void Menu::run() {
    update();

    if (isPageActive(Menu::MenuOption::Start)) {
        if (onStartclicked) {
            // creates new boards with updated settings
            board1 = TetrisBoard(board1Loc[0], board1Loc[1], set.p1Settings, playerStats, &board2);
            board2 = TetrisBoard(board2Loc[0], board2Loc[1], set.p2Settings, playerStats, &board1);
            onStartclicked = false;
            gameEnded = false;
        }

        // while game has not ended run game
        if (!(board1.gameEnded() || board2.gameEnded())) {
            playBackground.Draw(0, 0);

            LCD.SetFontColor(BLUE);
            std::string pageTitle = "P1 VS P2";
            LCD.WriteAt(pageTitle, (screenWidth / 2.0) - ((pageTitle.length() * LCD.getCharWidth()) / 2.0), 25);
            remove();

            board1.update();
            board2.update();

            // update score
            playerStats.p1Stats.linesCleared = board1.getLinesCleared();
            playerStats.p2Stats.linesCleared = board2.getLinesCleared();

            board1.draw();
            board2.draw();
        } else {
            confetti.Draw(0, 0);

            if (!gameEnded) {
                // play confetti noise yey you won
                PlayAudioFile("assets/TetrioWin.wav");
            }

            std::string playerWon = "";
            // p2 won
            if (board1.gameEnded()) {
                if (!gameEnded) {
                    playerStats.p2Stats.gamesWon++;
                    gameEnded = true;
                }

                playerWon += "P2 Won!";
            } else {
                // player1 won
                if (!gameEnded) {
                    playerStats.p1Stats.gamesWon++;
                    gameEnded = true;
                }

                playerWon += "P1 Won!";
            }
            // color array for funy colors
            unsigned int colors[] = {BLACK, AQUA, BLUE, ORANGE, YELLOW, GREEN, PURPLE, RED};
            // display won page
            int r = Random.RandInt() % 7;
            // draws wintext with funy colors
            Button winText = Button(40, playerWon, colors[r]);
            winText.updateButtonState();
        }
        // render back button on top
        back.drawButton();
    }

    // singleplayer 30 line clear
    if (isPageActive(MenuOption::Single)) {
        remove();

        if (!singleBoard.gameEnded() && !singleBoard.fourtyLinesEnded()) {
            singleBackground.Draw(0, 0);

            LCD.SetFontColor(BLUE);
            std::string pageTitle = "40 Line Clear";
            LCD.WriteAt(pageTitle, (screenWidth / 2.0) - ((pageTitle.length() * LCD.getCharWidth()) / 2.0), 25);

            singleBoard.update();
            // update score
            playerStats.singleplayerStats.linesCleared = singleBoard.getLinesCleared();
            singleBoard.draw();
        } else if (singleBoard.gameEnded()) {
            // sad horn sound effect from youtube: https://www.youtube.com/watch?v=CQeezCdF4mk
            if (gameEnded)
                PlayAudioFile("assets/wompwomp.wav");
            Button lossText = Button(40, "Womp Womp you lost :[ Try again next game", RED);
            lossText.updateButtonState();

        } else if (singleBoard.fourtyLinesEnded()) {
            // update stats
            playerStats.singleplayerStats.lineTime = singleBoard.getFourtyLinesClearedTime();

            // play confetti noise yey you won
            // Confetti noise: https://www.youtube.com/watch?v=7ZpXg0_gx6s
            if (gameEnded)
                PlayAudioFile("assets/TetrioWin.wav");

            // color array for funy colors
            unsigned int colors[] = {BLACK, AQUA, BLUE, ORANGE, YELLOW, GREEN, PURPLE, RED};

            // display won page
            int r = Random.RandInt() % 7;
            // draws wintext with funy colors
            Button singleWin = Button(40, "You cleared fourty lines! Check your stats page!", colors[r]);
            singleWin.updateButtonState();
        }

        if (onSingleClicked) {
            singleBoard = TetrisBoard(singleBoardLoc[0], singleBoardLoc[1], set.p1Settings, playerStats, NULL);
            onSingleClicked = false;
            gameEnded = false;
        }

        // render back button on top
        back.drawButton();
    }

    if (isPageActive(Menu::MenuOption::Settings)) {
        optionsPage.update();
    }

    if (isPageActive(Menu::MenuOption::Stats)) {

        LCD.SetFontColor(BLUE);

        Button p1BannerButton = Button(10, "P1 Stats", BLUE);
        p1BannerButton.updateButtonState();

        //"high score"
        std::string P1highScore;
        if (playerStats.p1Stats.linesCleared < 10) {
            P1highScore = "\"High\" score: " + std::to_string(playerStats.p1Stats.linesCleared);
        } else {
            P1highScore = "High score: " + std::to_string(playerStats.p1Stats.linesCleared);
        }
        // using button bc it is set up already and looks decent
        Button P1hsButton = Button(40, P1highScore, BLUE);
        P1hsButton.updateButtonState();

        // LCD.WriteAt("Best 40 line time: 3:42", 0, 70);

        std::string P1GamesWon = "Games won: " + std::to_string(playerStats.p1Stats.gamesWon);
        Button P1gwButton = Button(60, P1GamesWon, BLUE);
        P1gwButton.updateButtonState();

        Button p2BannerButton = Button(100, "P2 Stats", BLUE);
        p2BannerButton.updateButtonState();
        //"high score"
        std::string P2highScore;
        if (playerStats.p2Stats.linesCleared < 10) {
            P2highScore = "\"High\" score: " + std::to_string(playerStats.p2Stats.linesCleared);
        } else {
            P2highScore = "High score: " + std::to_string(playerStats.p2Stats.linesCleared);
        }
        Button P2hsButton = Button(140, P2highScore, BLUE);
        P2hsButton.updateButtonState();

        std::string P2GamesWon = "Games won: " + std::to_string(playerStats.p2Stats.gamesWon);

        Button P2gwButton = Button(160, P2GamesWon, BLUE);
        P2gwButton.updateButtonState();

        Button singleBannerButton = Button(200, "Singleplayer Stats", BLUE);
        singleBannerButton.updateButtonState();

        std::string fourtyLineClearScore;

        if (playerStats.singleplayerStats.lineTime > 0) {
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2) << playerStats.singleplayerStats.lineTime;
            fourtyLineClearScore = "Best Fourty Line time: " + stream.str();
        } else {
            fourtyLineClearScore = "Best Fourty Line time: N/A";
        }

        Button singleFourtyLineButton = Button(220, fourtyLineClearScore, BLUE);
        singleFourtyLineButton.updateButtonState();
    }
    if (isPageActive(Menu::MenuOption::Credits)) {
        creditsImage.Draw(0, 0);

        // render back button on top
        back.drawButton();

        // LCD.SetFontColor(BLUE);
        // LCD.WriteAt("Tetrio++ Written by:", 0, 20);
        // LCD.WriteAt("Nathan ", 0, 50);
        // LCD.WriteAt("Ojas Landge", 0, 90);
    }

    if (isPageActive(Menu::MenuOption::Instructions)) {
        howToPlay.Draw(0, 0);

        // render back button on top
        back.drawButton();
    }
}