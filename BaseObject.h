/*
 * BaseObject.h
 *
 *  Created on: Nov 28, 2025
 *      Author: iandu
 */

#ifndef BASEOBJECT_H_
#define BASEOBJECT_H_

class Engine;
class SDL_Plotter;

class Base{
protected:
	Engine* engine;
	SDL_Plotter* sdlPlot;
	double positionX = 0, positionY = 0;
	double scaleX = 0, scaleY = 0;

public:
	virtual void Start(Engine* eng,SDL_Plotter* plot){
		engine = eng;
		sdlPlot = plot;
	}
	virtual void Update() = 0;
	virtual void FixedUpdate() = 0;
	virtual ~Base();
};




#endif /* BASEOBJECT_H_ */
