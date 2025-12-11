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
#include "Const.h"
#include "Background.h"
#include "LapCounter.h"

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

	engine.CreateObject<GameManager>();

	using clock = chrono::steady_clock;
	auto currentTime = clock::now();
	auto lastTime = currentTime;
	double time = 0;

	while (!g.getQuit()){
		currentTime = clock::now();
		std::chrono::duration<double> frameTime = currentTime - lastTime;
		lastTime = currentTime;

		time += frameTime.count();


		for (auto* obj: engine.GameObjects){
			if (!(obj->GetPaused())) obj->Update();
		}

		if (time >= FIXEDUPDATESPEED){
			for (auto* obj: engine.GameObjects){
				if (!(obj->GetPaused())) obj->FixedUpdate();
			}
			time -= FIXEDUPDATESPEED;
		}
	}


	engine.ClearEngine(true);

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

/*
 * //============================================================================
// Name        : SDL.cpp
// Author      :
// Version     :
// Description : Pixel Racers - Top-down racing game with collision detection
//============================================================================

#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include "SDL_Plotter.h"
#include "Car.h"
#include "AICar.h"
#include "Obstacle.h"
#include "CollisionManager.h"
#include "Const.h"
#include "Background.h"
#include "Screen.h"
#include "Points.h"

using namespace std;

enum GameState {
    STATE_START,
    STATE_INSTRUCTIONS,
    STATE_PLAYING,
    STATE_PAUSED,
    STATE_GAME_OVER,
    STATE_WIN
};

int main(int argc, char ** argv)
{
    // Initialize random seed ONCE at program start
    srand(static_cast<unsigned>(time(0)));

    SDL_Plotter g(ROW, COL);

    Car playerCar;
    Background bg;

    // Create AI opponents with different colors and speeds
    vector<AICar> aiCars;
    aiCars.push_back(AICar(ROW/2 - 100, -50, color(0, 100, 255), 4));   // Blue
    aiCars.push_back(AICar(ROW/2 + 100, -150, color(0, 255, 0), 3));    // Green
    aiCars.push_back(AICar(ROW/2, -250, color(255, 255, 0), 5));        // Yellow

    // Create obstacles (traffic cones)
    vector<Obstacle> obstacles;
    obstacles.push_back(Obstacle(ROW/2 - 50,  -100, color(255, 140, 0), 25, 3));
    obstacles.push_back(Obstacle(ROW/2 + 80,  -300, color(255, 140, 0), 25, 3));
    obstacles.push_back(Obstacle(ROW/2 - 120, -500, color(255, 140, 0), 25, 3));

    int frameCount = 0;
    bool collisionDetected = false;
    int collisionCooldown = 0;

    // Lap tracking
    int currentLap = 1;
    const int MAX_LAPS = 3;
    const int POINTS_PER_LAP = 500;

    // Game state, screens, and points
    GameState gameState = STATE_START;
    StartScreen        startScreen;
    InstructionsScreen instructionsScreen;
    PauseScreen        pauseScreen;
    GameOverScreen     gameOverScreen;
    WinScreen          winScreen;
    PointsManager      points;
    points.reset();

    while (!g.getQuit()) {
        // INPUT
        if (g.kbhit()) {
            char c = toupper(g.getKey());

			s
            switch (gameState) {
                case STATE_START:
                    if (startScreen.handleInput(c)) {
                        gameState = STATE_PLAYING;
                    } else if (c == 'I') {
                        gameState = STATE_INSTRUCTIONS;
                    }
                    break;

                case STATE_INSTRUCTIONS:
                    if (c == 'S')       gameState = STATE_PLAYING;
                    else if (c == 'B')  gameState = STATE_START;
                    break;

                case STATE_PLAYING:
                    switch(c) {
                        case 'C': g.clear(); break;
                        case RIGHT_ARROW: playerCar.move(RIGHT_ARROW); break;
                        case LEFT_ARROW:  playerCar.move(LEFT_ARROW);  break;
                        case UP_ARROW:    playerCar.move(UP_ARROW);    break;
                        case DOWN_ARROW:  playerCar.move(DOWN_ARROW);  break;
                        case 'P':         gameState = STATE_PAUSED;    break;
                    }
                    break;

                case STATE_PAUSED:
                    if (pauseScreen.handleInput(c)) {
                        gameState = STATE_PLAYING;
                    } else if (c == 'B') {
                        gameState = STATE_START;
                    }
                    break;

                case STATE_GAME_OVER:
                    if (gameOverScreen.handleInput(c)) {
                        // Restart everything
                        playerCar = Car();
                        bg        = Background();
                        points.reset();
                        collisionDetected = false;
                        collisionCooldown = 0;
                        frameCount = 0;
                        currentLap = 1;

                        for (auto& aiCar : aiCars) {
                            aiCar.respawn();
                        }
                        for (auto& obs : obstacles) {
                            obs.respawn();
                        }

                        gameState = STATE_PLAYING;
                    }
                    break;

                case STATE_WIN:
                    if (winScreen.handleInput(c)) {
                        playerCar = Car();
                        bg        = Background();
                        points.reset();
                        collisionDetected = false;
                        collisionCooldown = 0;
                        frameCount = 0;
                        currentLap = 1;

                        for (auto& aiCar : aiCars) aiCar.respawn();
                        for (auto& obs   : obstacles) obs.respawn();

                        gameState = STATE_PLAYING;
                    }
                    break;
            }
        }

        if (g.mouseClick()) {
            g.getMouseClick(); // Clear the click queue
        }

        g.clear();

        // STATE UPDATE + DRAW
        switch (gameState) {
            case STATE_START:
                startScreen.update();
                startScreen.draw(g);
                break;

            case STATE_INSTRUCTIONS:
                instructionsScreen.update();
                instructionsScreen.draw(g);
                break;

            case STATE_PAUSED:
                pauseScreen.update();
                pauseScreen.draw(g);
                break;

            case STATE_GAME_OVER:
                gameOverScreen.update();
                gameOverScreen.draw(g);
                break;

            case STATE_WIN:
                winScreen.update();
                winScreen.draw(g);
                break;

            case STATE_PLAYING: {
                // BACKGROUND & SPEED-BASED POINTS
                bg.update(playerCar.getSpeed());
                points.updateSpeed(playerCar.getSpeed());
                points.update();

                // Lap progression based on score
                int lapFromScore = points.getScore() / POINTS_PER_LAP + 1;
                if (lapFromScore > currentLap && lapFromScore <= MAX_LAPS) {
                    currentLap = lapFromScore;
                }

                // Win when lap 3 is complete
                if (currentLap == MAX_LAPS &&
                    points.getScore() >= POINTS_PER_LAP * MAX_LAPS) {
                    winScreen.setWin(points.getScore());
                    gameState = STATE_WIN;
                    break;
                }

                // Update AI cars
                for (auto& aiCar : aiCars) {
                    aiCar.updateAI(bg.offset);

                    // Respawn AI cars when they go off screen
                    if (aiCar.isOffScreen()) {
                        aiCar.respawn();
                        points.addCarPass();  // use points system for passing cars
                    }
                }

                // Update obstacles
                for (auto& obs : obstacles) {
                    obs.update(playerCar.getSpeed());

                    // Respawn obstacles when off screen
                    if (obs.isOffScreen()) {
                        obs.respawn();
                        points.addObstacleAvoided(); // reward for surviving past obstacle
                    }
                }

                // COLLISION DETECTION
                if (collisionCooldown <= 0) {
                    bool hitAI = false;
                    bool hitObstacle = false;

                    CollisionManager::checkAllCollisions(playerCar, aiCars, obstacles,
                                                         hitAI, hitObstacle);

                    if (hitAI || hitObstacle) {
                        collisionDetected = true;
                        collisionCooldown = 60; // ~2 seconds at 30fps

                        // Slow down player on collision
                        playerCar.setSpeed(max(2, playerCar.getSpeed() - 3));

                        // Penalty via points manager
                        int newScore = max(0, points.getScore() - 20);
                        gameOverScreen.setGameOver(newScore, hitAI, hitObstacle);
                        gameState = STATE_GAME_OVER;

                        cout << "COLLISION! ";
                        if (hitAI)       cout << "Hit AI car! ";
                        if (hitObstacle) cout << "Hit obstacle! ";
                        cout << "Score: " << newScore << endl;
                    }
                } else {
                    collisionCooldown--;
                    collisionDetected = false;
                }



                // HUD: Score and Lap
                {
                    color white(255, 255, 255);
                    string scoreLabel = "Score:";
                    string scoreValue = to_string(points.getScore());
                    FontRenderer::drawSmall(g, 10, 20, white, scoreLabel, 0);
                    FontRenderer::drawSmall(g, 10, 50, white, scoreValue, 0);

                    string lapText = "Lap: " + to_string(currentLap) + "/" + to_string(MAX_LAPS);
                    FontRenderer::drawSmall(g, 10, 80, white, lapText, 0);
                }

                // Draw collision warning (flash red border)
                if (collisionDetected && (frameCount % 10 < 5)) {
                    color red(255, 0, 0);
                    // Draw red border around screen
                    for (int i = 0; i < 5; i++) {
                        for (int x = 0; x < ROW; x++) {
                            g.plotPixel(x, i, red);
                            g.plotPixel(x, COL-1-i, red);
                        }
                        for (int y = 0; y < COL; y++) {
                            g.plotPixel(i, y, red);
                            g.plotPixel(ROW-1-i, y, red);
                        }
                    }
                }

                frameCount++;

                // Periodic debug print of score and speed
                if (frameCount % 150 == 0) {
                    cout << "Current Score: " << points.getScore()
                         << " | Speed: " << playerCar.getSpeed()
                         << " | Lap: "   << currentLap << "/" << MAX_LAPS << endl;
                }

                break;
            }
        }

        g.Sleep(30);          // ~30 FPS
        g.update();
    }

    cout << "\n=== GAME OVER ===" << endl;
    cout << "Final Score: " << points.getScore() << endl;

    return 0;
}
 */

