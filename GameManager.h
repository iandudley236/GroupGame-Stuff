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
#include "CollisionManager.h"

#include <iostream>

class GameManager: public Base{
private:
	Screen* currentScreen;
	PointsManager* pointManager;
	CollisionManager collisionManager;

	int score = 0;
	bool hitAI = false, hitObstacle = false, collide = true;
	double aicarTimer = 0, obstacleTimer = 0,
			nextAITime, nextObstacleTime, collisionCooldown = 0;

	Car* player = nullptr;
	vector<AICar*> AICars;
	vector<Obstacle*> obstacles;

	// Helper Functions for screen management
	template<typename T>
	void SwitchScreen(Screen*&);
	void PrepCurrentScreen();

	void SwitchScreenFromPlay(char);
	void SwitchCheck(char);

	// Helper Functions for Play
	void PrepPlay();
	void Play();
	void Pause();
	void Unpause();

public:
	GameManager();
	void Start(Engine*,SDL_Plotter*) override;
	void Update() override;
	void FixedUpdate() override;

	vector<AICar*> GetAICars(){ return AICars; }
	vector<Obstacle*> GetObstacles(){ return obstacles; }
};

GameManager::GameManager()
	:currentScreen(),
	 pointManager(),
	 collisionManager(),
	 nextAITime(1 + (rand()%20)/ 10.0),
	 nextObstacleTime( 1 + (rand()%10)/ 10.0){}

void GameManager::Start(Engine* eng, SDL_Plotter* plot){
	Base::Start(eng, plot);

	currentScreen = new StartScreen();
}
void GameManager::Update() {
	if (currentScreen != nullptr){
		currentScreen->update();
		currentScreen->draw(*sdlPlot);
	}
	else {
		Play();
		if (collide){
			collisionManager.checkAllCollisions(player, AICars, obstacles, hitAI, hitObstacle);
			if (hitAI or hitObstacle) SwitchScreenFromPlay('L');
		}
	}
	// manage key presses
	if (sdlPlot->kbhit()) {
		SwitchCheck(toupper(sdlPlot->getKey()));
	}
}
void GameManager::FixedUpdate() {
	aicarTimer += FIXEDUPDATESPEED;
	obstacleTimer += FIXEDUPDATESPEED;
	if (collisionCooldown > BASECOLLISIONCOOLDOWN){
		collide = true;
	}
	else {
		collisionCooldown++;
	}
}

template <typename T>
void GameManager::SwitchScreen(Screen*& screen){
	delete screen;
	screen = new T();
}

void GameManager::SwitchScreenFromPlay(char c){
	engine->ClearEngine(false, this);
	switch (c) {
	case 'L': SwitchScreen<GameOverScreen>(currentScreen);
		static_cast<GameOverScreen*>(currentScreen)->setGameOver(score, hitAI, hitObstacle);
		break;
	case 'W': SwitchScreen<WinScreen>(currentScreen);
		static_cast<WinScreen*>(currentScreen)->setWin(score);
		break;
	}
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
	}
	else if(dynamic_cast<GameOverScreen*>(currentScreen)){
		if (c == 'C') PrepPlay();
	}
	else if(dynamic_cast<WinScreen*>(currentScreen)){
		if (c == 'C') PrepPlay();
	}

}

// Pause and Unpause functions for handling pausing while ingame
void GameManager::Pause(){
	for (auto* obj: engine->GameObjects){
		obj->SetPaused(true);
	}
	this->SetPaused(false);
}
void GameManager::Unpause(){
	for (auto* obj: engine->GameObjects){
		obj->SetPaused(false);
	}
}

void GameManager::PrepPlay(){
	delete currentScreen;
	currentScreen = nullptr;

	collide = false;
	collisionCooldown = 0;

	engine->CreateObject<LapCounter>();
	engine->CreateObject<Background>();
	player = engine->CreateObject<Car>();
}

void GameManager::Play(){
	if (aicarTimer >= nextAITime - player->getSpeed()/10.0){
		AICars.push_back(engine->CreateObject<AICar>(0, 0, color(rand()%255, rand()%255, rand()%255), rand()%5 + 2));
		aicarTimer = 0;
		nextAITime = 1 + (rand()%20)/ 10.0;
	}
	if (obstacleTimer >= nextObstacleTime - player->getSpeed()/10.0){
		obstacles.push_back(engine->CreateObject<Obstacle>());
		obstacleTimer = 0;
		nextObstacleTime = 1 + (rand()%10)/ 10.0;
	}

	for (AICar* ai: AICars){
		if (ai->isOffScreen()){
			delete ai;
			//add 10 points
		}
	}
	for (Obstacle* obs: obstacles){
		if (obs->isOffScreen()){
			delete obs;
			//add 5 points
		}
	}
}
/*
    int frameCount = 0;
    bool collisionDetected = false;
    int collisionCooldown = 0;
    int score = 0;
 */



#endif /* GAMEMANAGER_H_ */
