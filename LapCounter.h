/*
 * LapCounter.h
 *
 *  Created on: Dec 6, 2025
 *      Author: iandu
 */

#ifndef LAPCOUNTER_H_
#define LAPCOUNTER_H_

#include "BaseObject.h"
#include "Const.h"
#include "Car.h"

class LapCounter: public Base{
private:
	Car* car;
	double distanceTraveled = 0;
public:
	LapCounter();
	void Start(Engine*,SDL_Plotter*) override;
	void Update() override;
	void FixedUpdate() override;
};

void LapCounter::Start(Engine* eng,SDL_Plotter* plot){
	Base::Start(eng, plot);


}
void LapCounter::Update(){

}
void LapCounter::FixedUpdate(){

}



#endif /* LAPCOUNTER_H_ */
