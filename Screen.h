#ifndef SRC_SCREEN_H_
#define SRC_SCREEN_H_

#include "SDL_Plotter.h"
#include "Const.h"
#include "Font.h"
#include <string>

class Screen{
public:
    virtual void update() = 0;
    virtual void draw(SDL_Plotter& g) = 0;
    //virtual bool handleInput(char key) = 0;
    virtual ~Screen() {}
};

class StartScreen : public Screen {
private:
    int flashTimer;
public:
    StartScreen();
    void update() override;
    void draw(SDL_Plotter& g) override;
    //bool handleInput(char key) override;
};

class InstructionsScreen : public Screen {
private:
    int scrollOffset;
public:
    InstructionsScreen();
    void update() override;
    void draw(SDL_Plotter& g) override;
    //bool handleInput(char key) override;
};

class PauseScreen : public Screen {
private:
    int flashTimer;
public:
    PauseScreen();
    void update() override;
    void draw(SDL_Plotter& g) override;
    //bool handleInput(char key) override;
};

class GameOverScreen : public Screen {
private:
    int finalScore;
    bool hitAI, hitObstacle;
    int flashTimer;
public:
    GameOverScreen();
    void setGameOver(int score, bool aiHit, bool obstacleHit);
    void update() override;
    void draw(SDL_Plotter& g) override;
    //bool handleInput(char key) override;
};

class WinScreen : public Screen {
private:
    int finalScore;
    bool hitAI, hitObstacle;
    int flashTimer;
public:
    WinScreen();
    void setWin(int score);
    void update() override;
    void draw(SDL_Plotter& g) override;
    //bool handleInput(char key) override;
};


#endif
