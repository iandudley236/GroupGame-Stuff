/*
 * Collision.h
 *
 *  Created on: Dec 6, 2025
 *      Author: Haileyp
 */

#ifndef SRC_COLLISION_H_
#define SRC_COLLISION_H_

#include "Car.h"
#include "Const.h"
#include "SDL_Plotter.h"
#include "AICar.h"
#include "Obstacle.h"
#include <iostream>

class Collision {
private:
	int roadStart;
	int roadEnd;

public:
	Collision(int rs, int re);

	bool checkWallCollision(const Car& car);
	bool checkAICarCollision(const AICar&, const Car&);
	bool checkObstacleCollision(const Obstacle&, const Car&);
	bool hasCollision(const Car& car, AICar* aiCars, int numAICars);
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Collision::Collision(int rs, int re) : roadStart(rs), roadEnd(re) {}

bool Collision::checkWallCollision(const Car& car) {
	point carLoc = car.getLoc();
	int carSize = car.getSize();

	if ((carLoc.y - carSize / 2 <= roadStart) || (carLoc.y + carSize / 2 >= roadEnd)) {
		return true;
	}

	return false;
}

bool Collision::checkAICarCollision(const AICar& aiCar, const Car& player) {
	point playerLoc = player.getLoc();
	int playerSize = player.getSize();

	point aiLoc = aiCar.getLocation();
	int aiSize = aiCar.getSize();

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

bool Collision::checkObstacleCollision(const Obstacle& obst, const Car& car) const {

    point carLoc = car.getLoc();
    int carSize = car.getSize();

    // FIXED: Corrected coordinate system (x is horizontal, y is vertical)
    // Car boundaries
    int carLeft = carLoc.x - carSize/2;
    int carRight = carLoc.x + carSize/2;
    int carTop = carLoc.y - carSize/2;
    int carBottom = carLoc.y + carSize/2;

    // Obstacle boundaries
    int obsLeft = obst._loc.x - obst._size/2;
    int obsRight = obst._loc.x + obst._size/2;
    int obsTop = obst._loc.y - obst._size/2;
    int obsBottom = obst._loc.y + obst._size/2;

    // AABB (Axis-Aligned Bounding Box) collision detection
    return (carRight > obsLeft &&
            carLeft < obsRight &&
            carBottom > obsTop &&
            carTop < obsBottom);
}



#endif /* SRC_COLLISION_H_ */
