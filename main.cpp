//============================================================================
// Name        : SDL.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <chrono>
#include <cmath>

#include "SDL_Plotter.h"
//#include "Car.h"
#include "Const.h"
//#include "Background.h"
#include "BaseObject.h"
#include "Engine.h"
#include "testobj.h"

using namespace std;

// This is here to manage the objects in the game, aka
// the thing that holds all the game object pointers and
// also helps make them

int main(int argc, char ** argv)
{
	Engine engine;
	bool quit = false;
	using clock = chrono::steady_clock;
	auto currentTime = clock::now();
	auto fixedTime = clock::now();

	engine.CreateObject<Background>();

	while(!quit){
		currentTime = clock::now();

		for (auto* obj: engine.GameObjects){
			obj->Update();
		}

		if (currentTime >= fixedTime){
			for (auto* obj: engine.GameObjects){
				obj->FixedUpdate();
			}
			fixedTime += std::chrono::duration_cast<clock::duration>
				(std::chrono::duration<double>(FIXEDUPDATESPEED));
		}
	}

	engine.ClearEngine();

	return 0;
}





	/*
    SDL_Plotter g(ROW,COL);
    point p;
    color c;
    int size;
    Uint32 RGB;

    Car car;
    Background bg;

    bg.draw(g);
    car.draw(g);

    while (!g.getQuit()) {
        if(g.kbhit()){
            char c = toupper(g.getKey());
                    cout << int(c) << endl;
            switch(c){
                case 'C': g.clear(); break;
                case RIGHT_ARROW: car.move(RIGHT_ARROW); break;
                case LEFT_ARROW: car.move(LEFT_ARROW); break;
            }
            car.draw(g);
        }

        if(g.mouseClick()){}

        bg.update();
        bg.draw(g);
        car.draw(g);

        g.Sleep(30);
        g.update();
    }
    */

