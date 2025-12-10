/*
 * LapCounter.h
 *
 *  Created on: Dec 6, 2025
 *      Author: iandu
 */

#ifndef LAPCOUNTER_H_
#define LAPCOUNTER_H_

#include <chrono>
#include <ctime>
#include "BaseObject.h"
#include "Const.h"
#include "Car.h"
#include "Font.h"
#include "SDL_Plotter.h"

using namespace std;

class LapCounter: public Base{
private:
	using clock = std::chrono::steady_clock;
	double distanceTraveled, speed, totalDistance, lapSize;
	double time = 0;
	clock::time_point currentTime = clock::now();
	clock::time_point lastTime = currentTime;
	Car* carPointer = nullptr;

	FontRenderer fontR;

	enum Lap{
		Zero,
		One,
		Two,
	};

	Lap currentLap;

public:
	LapCounter(double);
	void travel();
	void SetSpeed(int);

	void Start(Engine*,SDL_Plotter*) override;
	void Update() override;
	void FixedUpdate() override;

	void win();
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

LapCounter::LapCounter(double spd = SPEED)
		:distanceTraveled(0),
		 speed(spd),
		 totalDistance(RACEDISTANCE),
		 lapSize(totalDistance/3),
		 currentLap(Zero){}

void LapCounter::Start(Engine* eng, SDL_Plotter* plot){
	Base::Start(eng, plot);

	carPointer = engine->Find<Car>();
}
void LapCounter::Update(){

}
void LapCounter::FixedUpdate(){
	speed = carPointer->getSpeed();

	travel();

	switch (currentLap){
	case Zero:
		if (distanceTraveled >= totalDistance / 3){

			currentLap = One;
		}
		break;
	case One:
		if (distanceTraveled >= (totalDistance*2)/3){

			currentLap = Two;
		}
		break;
	case Two:
		if (distanceTraveled >= totalDistance){
			win();
		}
	}
}


void LapCounter::SetSpeed(int spd){
	speed = static_cast<double>(spd);
}

void LapCounter::travel(){

	currentTime = clock::now();
	std::chrono::duration<double> frameTime = currentTime - lastTime;
	lastTime = currentTime;

	distanceTraveled += frameTime.count() * speed;
}

void LapCounter::win(){
	FontRenderer::drawLarge(*sdlPlot, 150, COL/2 - 70, color(255,255,255), "YOU WIN!", 0);
}



#endif /* LAPCOUNTER_H_ */
