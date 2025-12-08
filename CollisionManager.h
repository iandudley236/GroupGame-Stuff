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
#include <vector>
#include <cmath>

class CollisionManager {
public:
    // Check collision between player and AI cars
    static bool checkCarCollision(const Car& player, const AICar& ai) {
        point playerLoc = player.getLoc();
        point aiLoc = ai.getLocation();
        int playerSize = player.getSize();
        int aiSize = ai.getSize();

        // Calculate distance between centers
        int dx = playerLoc.x - aiLoc.x;
        int dy = playerLoc.y - aiLoc.y;
        float distance = sqrt(dx*dx + dy*dy);

        // Collision if distance < sum of radii
        return distance < (playerSize/2 + aiSize/2);
    }

    // Check collision between player and obstacles
    static bool checkObstacleCollision(const Car& player, const Obstacle& obstacle) {
        return obstacle.collidesWith(player);
    }

    // Check all collisions and return what was hit
    static void checkAllCollisions(const Car& player,
                                   std::vector<AICar>& aiCars,
                                   std::vector<Obstacle>& obstacles,
                                   bool& hitAI, bool& hitObstacle) {
        hitAI = false;
        hitObstacle = false;

        // Check AI car collisions
        for(auto& ai : aiCars) {
            if(checkCarCollision(player, ai)) {
                hitAI = true;
                break;
            }
        }

        // Check obstacle collisions
        for(auto& obs : obstacles) {
            if(checkObstacleCollision(player, obs)) {
                hitObstacle = true;
                break;
            }
        }
    }
};

#endif /* CollisionManager_h */
