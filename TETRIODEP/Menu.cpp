#include "Menu.h"
#include "Button.h"
#include "Switch.h"

#include "Input.h"
#include <FEHImages.h>
#include <FEHLCD.h>
#include <FEHRandom.h>
#include <iostream>
#include <mmsystem.h>
#include <string>
#include <windows.h>

Menu::Menu()
    : start(0 + buttonoffset, "Start", BLUE, DARKBLUE), stats(30 + buttonoffset, "Stats", BLUE, DARKBLUE),
      settings(60 + buttonoffset, "Settings", BLUE, DARKBLUE),
      instructions(90 + buttonoffset, "Instructions", BLUE, DARKBLUE),
      credits(120 + buttonoffset, "Credits", BLUE, DARKBLUE), back(10, 0, "Exit", BLUE, DARKBLUE),
      board1(board1Loc[0], board1Loc[1], set.p1Settings, playerStats),
      board2(board2Loc[0], board2Loc[1], set.p2Settings, playerStats), optionsPage(set) {
    // initialize button instances
    onStartclicked = false;
    // start playing background music
    // this will error im not sure why but it compiles so who cares
    //   mciSendString(TEXT("play \"TETRIODEP/TetrisBackground.mp3\""),NULL,0,0);

    // Tetris song from internet archive: https://ia902905.us.archive.org/11/items/TetrisThemeMusic/Tetris.mp3
    mciSendString(TEXT("open \"TETRIODEP/TetrisBackground.mp3\" type mpegvideo alias Background"), NULL, 0, NULL);
    mciSendString(TEXT("play Background repeat"), NULL, 0, 0);
    gameEnded = false;
};

void Menu::disable(Button &b) { b.disable(); }

void Menu::update() {

    if (currOption == Option::Back) {
        currOption = Option::None;
    }
    bool menuActive = currOption == Option::None; // if in subpage

    if (menuActive) {
        // draws background
        // background was made by me in blender hence why its so ugly lol
        FEHImage background;
        background.Open("TETRIODEP/TetrioBackground-2.png");
        background.Draw(0, 0);
        background.Close();

        start.updateButtonState();
        settings.updateButtonState();
        stats.updateButtonState();
        instructions.updateButtonState();
        credits.updateButtonState();

        // update current option selected if a button triggers
        if ((renderSubPage(start))) {

            if (currOption != Option::Start) {
                currOption = Option::Start;
                onStartclicked = true;
            } else {
                onStartclicked = false;
            }
        }
        if (renderSubPage(settings)) {
            currOption = Option::Settings;
        }
        if (renderSubPage(stats)) {
            currOption = Option::Stats;
        }
        if (renderSubPage(instructions)) {
            currOption = Option::Instructions;
        }
        if (renderSubPage(credits)) {
            currOption = Option::Credits;
        }
    } else {
        // removes menu buttons and draws back button
        remove();
        back.updateButtonState();

        if (renderSubPage(back)) {
            currOption = Option::Back;
            back.remove();
            // back to menu
        }
    }
}

// returns true when its time to render a subpage for a given button
bool Menu::renderSubPage(Button &b) { return b.onButtonReleased(); }

bool Menu::isPageActive(Option page) { return currOption == page; }

void Menu::renderBackButton() { back.updateButtonState(); }

void Menu::removeBack() { back.remove(); }

void Menu::remove() {
    // clears all menu buttons
    start.remove();
    settings.remove();
    stats.remove();
    instructions.remove();
    credits.remove();
}

void Menu::returnToMenu() {
    currOption = Option::Back;
    back.remove();
    // back to menu
}

// moved logic from main to here
void Menu::run() {
    update();

    if (isPageActive(Menu::Option::Start)) {

        // while game has not ended run game
        if (!(board1.gameEnded() || board2.gameEnded())) {
            FEHImage background2;
            background2.Open("TETRIODEP/TetrioGameBackground.png");
            background2.Draw(0, 0);
            background2.Close();
            

            if (onStartclicked) {
                // creates new boards with updated settings
                board1 = TetrisBoard(board1Loc[0], board1Loc[1], set.p1Settings, playerStats);
                board2 = TetrisBoard(board2Loc[0], board2Loc[1], set.p2Settings, playerStats);
                // needs to add a clear method
                board1.clear();
                board2.clear();
                onStartclicked = false;
                gameEnded = false;
            }

            

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
            FEHImage confetti;
            confetti.Open("TETRIODEP/TetrisConfetti.png");
            confetti.Draw(0, 0);
            confetti.Close();

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
            // play confetti noise yey you won
            PlaySound(TEXT("TETRIODEP/TetrioWin.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_NOSTOP);
        }
        //render back button on top
            back.drawButton();
    }
    if (isPageActive(Menu::Option::Settings)) {
        optionsPage.update();
    }

    if (isPageActive(Menu::Option::Stats)) {

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
    }
    if (isPageActive(Menu::Option::Credits)) {

        LCD.SetFontColor(BLUE);
        LCD.WriteAt("Tetrio++ Written by:", 0, 20);
        LCD.WriteAt("Nathan Cheng", 0, 50);
        LCD.WriteAt("Ojas Landge", 0, 90);
    }

    if (isPageActive(Menu::Option::Instructions)) {

        LCD.SetFontColor(BLUE);
        LCD.WriteAt("How to play Tetrio++", 0, 20);
        LCD.WriteAt("The goal is to clear lines", 0, 50);
        LCD.WriteAt("faster than your opponent.", 0, 90);
        LCD.WriteAt("First to stack to the", 0, 120);
        LCD.WriteAt("top loses", 0, 150);
    }
}