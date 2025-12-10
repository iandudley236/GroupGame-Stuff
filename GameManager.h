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
	bool hitAI = false, hitObstacle = false;


	// Helper Functions for screen management
	template<typename T>
	void SwitchScreen(Screen*&);
	void PrepCurrentScreen();

	void SwitchCheck(char);

	// Helper Functions for Play
	void PrepPlay();
	void Play();
	void Pause();

public:
	GameManager();
	void Start(Engine*,SDL_Plotter*) override;
	void Update() override;
	void FixedUpdate() override;

};

GameManager::GameManager():currentScreen(),pointManager(){

}

void GameManager::Start(Engine* eng, SDL_Plotter* plot){
	Base::Start(eng, plot);

	currentScreen = new StartScreen();
}
void GameManager::Update() {
	if (currentScreen != nullptr){
		currentScreen->update();
		currentScreen->draw(*sdlPlot);
	}
	// manage key presses
	if (sdlPlot->kbhit()) {
		SwitchCheck(toupper(sdlPlot->getKey()));
	}
}
void GameManager::FixedUpdate() {

}

template <typename T>
void GameManager::SwitchScreen(Screen*& screen){
	delete screen;
	screen = new T();
}

// Manages the switches between Screens by input only, not during play
void GameManager::SwitchCheck(char c){
	if (!currentScreen){
		if (c == 'P') Pause();
	}
	else if(dynamic_cast<StartScreen*>(currentScreen)){
		if (c == 'I') SwitchScreen<InstructionsScreen>(currentScreen);
		else if (c == 'S') PrepPlay();
	}
	else if(dynamic_cast<InstructionsScreen*>(currentScreen)){
		if (c == 'B') SwitchScreen<StartScreen>(currentScreen);
		else if (c == 'S') PrepPlay();
	}
	else if(dynamic_cast<PauseScreen*>(currentScreen)){
		if (c == 'B') SwitchScreen<StartScreen>(currentScreen);
		else if (c == 'P') PrepCurrentScreen();
	}
	else if(dynamic_cast<GameOverScreen*>(currentScreen)){
		if (c == 'C') PrepPlay();
	}
	else if(dynamic_cast<WinScreen*>(currentScreen)){
		if (c == 'C') PrepPlay();
	}

}

void GameManager::Pause(){
	for (auto* obj: engine->GameObjects){
		obj->SetPaused(true);
	}
	this->SetPaused(false);
}

void GameManager::PrepPlay(){
	delete currentScreen;
	currentScreen = nullptr;
}

void GameManager::Play(){

}
/*
    int frameCount = 0;
    bool collisionDetected = false;
    int collisionCooldown = 0;
    int score = 0;
 */



#endif /* GAMEMANAGER_H_ */
