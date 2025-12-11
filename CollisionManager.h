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

class CollisionManager{

public:
	CollisionManager(){}

	static bool checkAICarCollision(const AICar*, const Car*);
	static bool checkObstacleCollision(const Obstacle*, const Car*);

    // Check all collisions and return what was hit
    static void checkAllCollisions(const Car* player,
                                   std::vector<AICar*>& aiCars,
                                   std::vector<Obstacle*>& obstacles,
                                   bool& hitAI, bool& hitObstacle) {
        hitAI = false;
        hitObstacle = false;

        // Check AI car collisions
        for(auto& ai : aiCars) {
            if(checkAICarCollision(ai, player)) {
                hitAI = true;
                break;
            }
        }

        // Check obstacle collisions
        for(auto& obs : obstacles) {
            if(checkObstacleCollision(obs, player)) {
                hitObstacle = true;
                break;
            }
        }
    }
};

bool CollisionManager::checkAICarCollision(const AICar* aiCar, const Car* player) {
	point playerLoc = player->getLoc();
	int playerSize = player->getSize();

	point aiLoc = aiCar->getLocation();
	int aiSize = aiCar->getSize();

	int playerLeft = playerLoc.y - playerSize / 2;
	int playerRight = playerLoc.y + playerSize / 2;
	int playerTop = playerLoc.x - playerSize / 2;
	int playerBottom = playerLoc.x + playerSize / 2;

	int aiLeft = aiLoc.y - aiSize / 2;
	int aiRight = aiLoc.y + aiSize / 2;
	int aiTop = aiLoc.x - aiSize / 2;
	int aiBottom = aiLoc.x + aiSize / 2;

	return(playerRight > aiLeft &&
			playerLeft < aiRight &&
			playerBottom > aiTop &&
			playerTop < aiBottom);
}

bool CollisionManager::checkObstacleCollision(const Obstacle* obst, const Car* car) {

    point carLoc = car->getLoc();
    int carSize = car->getSize();

    point obstLoc = obst->getLocation();
    int obstSize = obst->getSize();

    // FIXED: Corrected coordinate system (x is horizontal, y is vertical)
    // Car boundaries
    int carLeft = carLoc.x - carSize/2;
    int carRight = carLoc.x + carSize/2;
    int carTop = carLoc.y - carSize/2;
    int carBottom = carLoc.y + carSize/2;

    // Obstacle boundaries
    int obsLeft = obstLoc.x - obstSize/2;
    int obsRight = obstLoc.x + obstSize/2;
    int obsTop = obstLoc.y - obstSize/2;
    int obsBottom = obstLoc.y + obstSize/2;

    // AABB (Axis-Aligned Bounding Box) collision detection
    return (carRight > obsLeft &&
            carLeft < obsRight &&
            carBottom > obsTop &&
            carTop < obsBottom);
}

#endif /* CollisionManager_h */
