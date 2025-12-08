/*
 * BaseObject.cpp
 *
 *  Created on: Dec 2, 2025
 *      Author: iandu
 */


#include "BaseObject.h"
#include "Engine.h"
#include "SDL_Plotter.h"


Base::~Base(){
	if (engine){
		engine->DeleteObject(this);
	}
	delete this;
}
