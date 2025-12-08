/*
 * AIRacer.h
 *
 *  Created on: Dec 6, 2025
 *      Author: iandu
 */

#ifndef AIRACER_H_
#define AIRACER_H_

#include "BaseObject.h"
#include "Const.h"

/* for knowing where its going, probably the best way is to have
 * each road section have a point that it gives the racers. that
 * point being what the ai tries to drive towards
 *
 */

class AIRacer: public Base{
private:
	// the racer eeds to know where it needs to go, how fast its going, and how it gets animated
	double pointX = 0, pointY = 0;
	double speed;
public:
	AIRacer();
	void Start(Engine*) override;
	void Update() override;
	void FixedUpdate() override;
	void SetPoint(double x, double y);
};

AIRacer::AIRacer():speed(SPEED){}

void AIRacer::Start(Engine* eng){
	Base::Start(eng);
}

void AIRacer::Update(){

}

void AIRacer::FixedUpdate(){

}

void AIRacer::SetPoint(double x, double y){
	pointX = x;
	pointY = y;
}




#endif /* AIRACER_H_ */
