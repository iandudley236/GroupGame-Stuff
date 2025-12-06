/*
 * Engine.h
 *
 *  Created on: Dec 2, 2025
 *      Author: iandu
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include "BaseObject.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Engine{
public:
	vector<Base*> GameObjects;
	bool quitting;

	// Creates an object with given parameters needed for constructor (args),
	// puts it into the list of objects, and returns pointer in case you
	// want to edit it right after creation for some reason.
	template<typename T, typename... Args>
	T* CreateObject(Args... arguements){
		T* newObj = new T(forward<Args>(arguements)...);
		newObj->Start(this);
		GameObjects.push_back(newObj);
		return newObj;
	}

	void DeleteObject(Base* object){
		auto objectToDestroy = std::find(GameObjects.begin(),GameObjects.end(), object);
		if (objectToDestroy != GameObjects.end()){
			delete *objectToDestroy;
			GameObjects.erase(objectToDestroy);
		}
	}

	void ClearEngine(){
		for (auto object: GameObjects){
			delete object;
		}
	}

	bool GetQuit(){
		return quitting;
	}
	void SetQuit(bool quit){
		quitting = quit;
	}
};



#endif /* ENGINE_H_ */
