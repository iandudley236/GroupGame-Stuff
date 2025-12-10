/*
 * GameManager.h
 *
 *  Created on: Dec 6, 2025
 *      Author: iandu
 */

#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_
/* 	TO MAKE:
 * ai cars, player, background, obstacles, lapcounter
 *
 */


#include "BaseObject.h"
#include "Const.h"
#include "Car.h"
#include "LapCounter.h"
#include "Engine.h"
#include "AICar.h"
#include "Obstacle.h"
#include "Background.h"
#include "Screen.h"
#include "Points.h"

class GameManager: public Base{
private:
	Screen* currentScreen;
	PointsManager* pointManager;
	int score = 0;

public:
	GameManager();
	void Start(Engine*,SDL_Plotter*) override;
	void Update() override;
	void FixedUpdate() override;

	void SetScreenToPlay();
	void SwitchScreen(char);
};

GameManager::GameManager():currentScreen(),pointManager(){

}

void GameManager::Start(Engine* eng, SDL_Plotter* plot){
	Base::Start(eng, plot);

	currentScreen = new StartScreen();
	engine->CreateObject<Background>();
	engine->CreateObject<Car>();
	engine->CreateObject<LapCounter>();

}
void GameManager::Update() {
	if (currentScreen != nullptr){
		currentScreen->update();
		currentScreen->draw(*sdlPlot);
	}
}
void GameManager::FixedUpdate() {
	// if pass car,
}

void GameManager::SetScreenToPlay(){
	delete currentScreen;
	currentScreen = nullptr;
}
void GameManager::SwitchScreen(char c){
	if (currentScreen != nullptr){
		delete currentScreen;
		currentScreen = nullptr;
	}
	switch (c){
	case 'I': currentScreen = new InstructionsScreen(); break;
	case 'S': currentScreen = new StartScreen(); break;
	case 'P': currentScreen = new PauseScreen();break;
	case 'O': currentScreen = new GameOverScreen();break;
	case 'W': currentScreen = new WinScreen();break;
	}

}

void Play(){

}
/*
    int frameCount = 0;
    bool collisionDetected = false;
    int collisionCooldown = 0;
    int score = 0;
 */



#endif /* GAMEMANAGER_H_ */
