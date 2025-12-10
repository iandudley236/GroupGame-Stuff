//
//  CollisionManager.h
//  SDL_Prac_1
//
//  Manages all collision detection
//

#ifndef CollisionManager_h
#define CollisionManager_h
#include "Car.h"
#include "AICar.h"
#include "Obstacle.h"
#include "Collision.h"
#include <vector>
#include <cmath>

class CollisionManager: public Base {
public:
    // Check all collisions and return what was hit
    static void checkAllCollisions(const Car& player,
                                   std::vector<AICar>& aiCars,
                                   std::vector<Obstacle>& obstacles,
                                   bool& hitAI, bool& hitObstacle) {
        hitAI = false;
        hitObstacle = false;

        // Check AI car collisions
        for(auto& ai : aiCars) {
            if(checkCollision(ai, player)) {
                hitAI = true;
                break;
            }
        }

        // Check obstacle collisions
        for(auto& obs : obstacles) {
            if(checkCollision(obs, player)) {
                hitObstacle = true;
                break;
            }
        }
    }
};

#endif /* CollisionManager_h */
