#include "Screen.h"
#include <string>

StartScreen::StartScreen() : flashTimer(0) {}
InstructionsScreen::InstructionsScreen() : scrollOffset(0) {}
PauseScreen::PauseScreen() : flashTimer(0) {}
GameOverScreen::GameOverScreen() : finalScore(0), hitAI(false), hitObstacle(false), flashTimer(0) {}

void GameOverScreen::setGameOver(int score, bool aiHit, bool obstacleHit) {
    finalScore = score;
    hitAI = aiHit;
    hitObstacle = obstacleHit;
}

void StartScreen::update() { flashTimer++; }
void StartScreen::draw(SDL_Plotter& g) {
    color bg(20, 40, 80);
    for(int x = 0; x < ROW; x++) for(int y = 0; y < COL; y++) g.plotPixel(x, y, bg);

    color yellow(255, 255, 0), white(255, 255, 255);
    FontRenderer::drawLarge(g, 110, COL/2 - 80, yellow, "PIXEL RACERS", 0);
    FontRenderer::drawSmall(g, 100, COL/2 - 15, white, "Press I for Instructions", this->flashTimer);
    FontRenderer::drawSmall(g, 155, COL/2 + 15, white, "Press S to START", this->flashTimer);
}

bool StartScreen::handleInput(char key) { return (toupper(key) == 'S'); }

void InstructionsScreen::update() { scrollOffset++; if(scrollOffset > 300) scrollOffset = 0; }
void InstructionsScreen::draw(SDL_Plotter& g) {
    color bg(30, 30, 50);
    for(int x = 0; x < ROW; x++) for(int y = 0; y < COL; y++) g.plotPixel(x, y, bg);

    color cyan(0,255,255), white(255,255,255);
    FontRenderer::drawLarge(g, 30, 40, cyan, "CONTROLS", 0);
    FontRenderer::drawSmall(g, 30, 90, white, "UP: Accelerate", 0);
    FontRenderer::drawSmall(g, 30, 130, white, "DOWN: Brake", 0);
    FontRenderer::drawSmall(g, 30, 170, white, "LEFT/RIGHT: Steer", 0);
    FontRenderer::drawSmall(g, 30, 210, white, "Pass cars = 10pts", 0);
    FontRenderer::drawSmall(g, 30, 250, white, "Obstacles = CRASH", 0);
    FontRenderer::drawSmall(g, 30, COL-90, cyan, "Press S to START", 0);
    FontRenderer::drawSmall(g, 30, COL-130, cyan, "Press B to go BACK", 0);
}

bool InstructionsScreen::handleInput(char key) { return (toupper(key) == 'I'); }

void PauseScreen::update() { flashTimer++; }
void PauseScreen::draw(SDL_Plotter& g) {
    for(int x = 0; x < ROW; x++) for(int y = 0; y < COL; y++) g.plotPixel(x, y, 80, 80, 80);

    color yellow(255, 255, 0), cyan(0,255,255);
    FontRenderer::drawLarge(g, 200, COL/2 - 30, yellow, "PAUSED", 0);
    FontRenderer::drawSmall(g, 150, COL/2 + 20, yellow, "Press P to Resume", this->flashTimer);
    FontRenderer::drawSmall(g, 140, COL/2 + 50, cyan, "Press B to go BACK", 0);
}

bool PauseScreen::handleInput(char key) { return (toupper(key) == 'P'); }

void GameOverScreen::update() { flashTimer++; }
void GameOverScreen::draw(SDL_Plotter& g) {
    for(int x = 0; x < ROW; x++) for(int y = 0; y < COL; y++) g.plotPixel(x, y, 20, 20, 20);

    color red(255,0,0), white(255,255,255), blue(0,100,255), orange(255,140,0);
    FontRenderer::drawLarge(g, 150, COL/2 - 70, red, "GAME OVER", 0);
    FontRenderer::drawSmall(g, 160, COL/2 - 20, white, "Final Score: ", 0);

    string scoreStr = std::to_string(finalScore);
    FontRenderer::drawSmall(g, 360, COL/2 - 20, white, scoreStr, 0);

    int yPos = COL/2 + 10;
    if(hitAI) {
        FontRenderer::drawSmall(g, 190, yPos, blue, "Hit AI Car!", this->flashTimer);
        yPos += 35;
    }
    if(hitObstacle) {
        FontRenderer::drawSmall(g, 180, yPos, orange, "Hit Obstacle!", this->flashTimer);
    }
    FontRenderer::drawSmall(g, 140, COL - 90, white, "Press C to Restart", this->flashTimer);
}

bool GameOverScreen::handleInput(char key) { return (toupper(key) == 'C'); }

WinScreen::WinScreen()
    : finalScore(0), hitAI(false), hitObstacle(false), flashTimer(0) {}

void WinScreen::setWin(int score) {
    finalScore = score;
    hitAI      = false;
    hitObstacle = false;
}

void WinScreen::update() { flashTimer++; }

void WinScreen::draw(SDL_Plotter& g) {
    // Dark green-ish background
    for(int x = 0; x < ROW; x++) {
        for(int y = 0; y < COL; y++) {
            g.plotPixel(x, y, 10, 30, 10);
        }
    }

    color green(0,255,0), white(255,255,255), cyan(0,255,255);

    FontRenderer::drawLarge(g, 150, COL/2 - 70, green, "YOU WIN!", 0);
    FontRenderer::drawSmall(g, 160, COL/2 - 20, white, "Final Score: ", 0);

    std::string scoreStr = std::to_string(finalScore);
    FontRenderer::drawSmall(g, 360, COL/2 - 20, white, scoreStr, 0);

    FontRenderer::drawSmall(g, 140, COL - 90, cyan,
                            "Press C to Restart", this->flashTimer);
}

bool WinScreen::handleInput(char key) {
    return (toupper(key) == 'C');
}


