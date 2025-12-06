/*
 * BaseObject.h
 *
 *  Created on: Nov 28, 2025
 *      Author: iandu
 */

#ifndef BASEOBJECT_H_
#define BASEOBJECT_H_

class Engine;

class Base{
protected:
	Engine* engine;
	double positionX = 0, positionY = 0;
	double scaleX = 0, scaleY = 0;

public:
	virtual void Start(Engine* eng){
		engine = eng;
	}
	virtual void Update() = 0;
	virtual void FixedUpdate() = 0;
	virtual ~Base();
};




#endif /* BASEOBJECT_H_ */
