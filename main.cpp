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
#include <vector>
#include <cstdlib>
#include <ctime>
#include "SDL_Plotter.h"
#include "Car.h"
#include "AICar.h"
#include "Obstacle.h"
#include "CollisionManager.h"
#include "Const.h"
#include "Background.h"

#include "SDL_Plotter.h"
//#include "Car.h"
#include "Const.h"
//#include "Background.h"
#include "BaseObject.h"
#include "Engine.h"
#include "testobj.h"
#include "GameManager.h"

using namespace std;

// This is here to manage the objects in the game, aka
// the thing that holds all the game object pointers and
// also helps make them

int main(int argc, char ** argv)
{


	// Initialize random seed ONCE at program start
	srand(static_cast<unsigned>(time(0)));

	SDL_Plotter g(ROW, COL);
	Engine engine(&g);
	bool quit = false;
	using clock = chrono::steady_clock;
	auto currentTime = clock::now();
	auto lastTime = currentTime;
	double time = 0;

	while(!quit){
		currentTime = clock::now();
		std::chrono::duration<double> frameTime = currentTime - lastTime;
		lastTime = currentTime;

		time += frameTime.count();

		for (auto* obj: engine.GameObjects){
			obj->Update();
		}

		if (time >= FIXEDUPDATESPEED){
			for (auto* obj: engine.GameObjects){
				obj->FixedUpdate();
			}
			time -= FIXEDUPDATESPEED;
		}
	}

	engine.ClearEngine();

	return 0;
}





	/*
   #include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "SDL_Plotter.h"
#include "Car.h"
#include "AICar.h"
#include "Obstacle.h"
#include "CollisionManager.h"
#include "Const.h"
#include "Background.h"
using namespace std;

int main(int argc, char ** argv)
{
    // Initialize random seed ONCE at program start
    srand(static_cast<unsigned>(time(0)));

    SDL_Plotter g(ROW, COL);

    Car playerCar;
    Background bg;

    // Create AI opponents with different colors and speeds
    vector<AICar> aiCars;
    aiCars.push_back(AICar(ROW/2 - 100, -50, color(0, 100, 255), 4));    // Blue
    aiCars.push_back(AICar(ROW/2 + 100, -150, color(0, 255, 0), 3));     // Green
    aiCars.push_back(AICar(ROW/2, -250, color(255, 255, 0), 5));         // Yellow

    // Create obstacles (traffic cones)
    vector<Obstacle> obstacles;
    obstacles.push_back(Obstacle(ROW/2 - 50, -100, color(255, 140, 0), 25, 3));
    obstacles.push_back(Obstacle(ROW/2 + 80, -300, color(255, 140, 0), 25, 3));
    obstacles.push_back(Obstacle(ROW/2 - 120, -500, color(255, 140, 0), 25, 3));

    int frameCount = 0;
    bool collisionDetected = false;
    int collisionCooldown = 0;
    int score = 0;

    while (!g.getQuit()) {
        // Handle keyboard input
        if(g.kbhit()) {
            char c = toupper(g.getKey());

            switch(c) {
                case 'C': g.clear(); break;
                case RIGHT_ARROW: playerCar.move(RIGHT_ARROW); break;
                case LEFT_ARROW: playerCar.move(LEFT_ARROW); break;
                case UP_ARROW: playerCar.move(UP_ARROW); break;
                case DOWN_ARROW: playerCar.move(DOWN_ARROW); break;
            }
        }

        if(g.mouseClick()) {
            g.getMouseClick(); // Clear the click queue
        }

        // Update background animation
        bg.update();

        // Update AI cars
        for(auto& aiCar : aiCars) {
            aiCar.updateAI(bg.offset);

            // Respawn AI cars when they go off screen
            if(aiCar.isOffScreen()) {
                aiCar.respawn();
                score += 10; // Points for passing AI car
            }
        }

        // Update obstacles
        for(auto& obs : obstacles) {
            obs.update();

            // Respawn obstacles when off screen
            if(obs.isOffScreen()) {
                obs.respawn();
                score += 5; // Points for passing obstacle
            }
        }

        // COLLISION DETECTION
        if(collisionCooldown <= 0) {
            bool hitAI = false;
            bool hitObstacle = false;

            CollisionManager::checkAllCollisions(playerCar, aiCars, obstacles,
                                                hitAI, hitObstacle);

            if(hitAI || hitObstacle) {
                collisionDetected = true;
                collisionCooldown = 60; // 2 second cooldown at 30fps

                // Slow down player on collision
                playerCar.setSpeed(max(2, playerCar.getSpeed() - 3));

                // Penalty
                score = max(0, score - 20);

                cout << "COLLISION! ";
                if(hitAI) cout << "Hit AI car! ";
                if(hitObstacle) cout << "Hit obstacle! ";
                cout << "Score: " << score << endl;
            }
        } else {
            collisionCooldown--;
            collisionDetected = false;
        }

        // DRAW EVERYTHING
        bg.draw(g);           // Draw background first

        // Draw obstacles
        for(auto& obs : obstacles) {
            obs.draw(g);
        }

        // Draw all AI cars
        for(auto& aiCar : aiCars) {
            aiCar.draw(g);
        }

        playerCar.draw(g);    // Draw player on top

        // Draw collision warning (flash red border)
        if(collisionDetected && (frameCount % 10 < 5)) {
            color red(255, 0, 0);
            // Draw red border around screen
            for(int i = 0; i < 5; i++) {
                for(int x = 0; x < ROW; x++) {
                    g.plotPixel(x, i, red);
                    g.plotPixel(x, COL-1-i, red);
                }
                for(int y = 0; y < COL; y++) {
                    g.plotPixel(i, y, red);
                    g.plotPixel(ROW-1-i, y, red);
                }
            }
        }

        g.Sleep(30);          // ~30 FPS
        g.update();

        frameCount++;

        // Display score every 5 seconds
        if(frameCount % 150 == 0) {
            cout << "Current Score: " << score << " | Speed: "
                 << playerCar.getSpeed() << endl;
        }
    }

    cout << "\n=== GAME OVER ===" << endl;
    cout << "Final Score: " << score << endl;

    return 0;
}
    }
    */

