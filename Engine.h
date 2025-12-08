/*
 * Engine.h
 *
 *  Created on: Dec 2, 2025
 *      Author: iandu
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include "BaseObject.h"
#include "SDL_Plotter.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Engine{
public:
	vector<Base*> GameObjects;
	SDL_Plotter* sdlPlot;
	bool quitting;

	Engine(SDL_Plotter *plot):GameObjects(),sdlPlot(plot),quitting(false){}
	// Creates an object with given parameters needed for constructor (args),
	// puts it into the list of objects, and returns pointer in case you
	// want to edit it right after creation for some reason.
	template<typename T, typename... Args>
	T* CreateObject(Args... arguements){
		T* newObj = new T(forward<Args>(arguements)...);
		newObj->Start(this, sdlPlot);
		GameObjects.push_back(newObj);
		return newObj;
	}
	//takes in a reference to a specifiv object
	//returns nothing, and deletes the object and removes it from vector
	void DeleteObject(Base* object){
		auto objectToDestroy = std::find(GameObjects.begin(),GameObjects.end(), object);
		if (objectToDestroy != GameObjects.end()){
			delete *objectToDestroy;
			GameObjects.erase(objectToDestroy);
		}
	}

	Base* Find(Base* object){
		auto obj = std::find(GameObjects.begin(),GameObjects.end(), object);
		return *obj;
	}

	void ClearEngine(){
		for (auto object: GameObjects){
			delete object;
		}
	}

	SDL_Plotter* GetPlotter(){
		return sdlPlot;
	}

	bool GetQuit(){
		return quitting;
	}
	void SetQuit(bool quit){
		quitting = quit;
	}
};



#endif /* ENGINE_H_ */
