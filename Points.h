#ifndef POINTS_H_
#define POINTS_H_
#include "Const.h"

class PointsManager {
private:
    int score;
    int baseSpeed;
    float speedMultiplier;
    int carsPassed;
    int obstaclesAvoided;
    int frameCounter;

public:
    PointsManager();
    void reset();
    void update();
    void addCarPass();
    void addObstacleAvoided();
    void updateSpeed(int playerSpeed);

    int getScore() const { return score; }
    int getCarsPassed() const { return carsPassed; }
    int getObstaclesAvoided() const { return obstaclesAvoided; }
    float getSpeedMultiplier() const { return speedMultiplier; }
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

PointsManager::PointsManager() : score(0), baseSpeed(0), speedMultiplier(SPEED_MULTIPLIER_BASE), carsPassed(0), obstaclesAvoided(0), frameCounter(0) {}

void PointsManager::reset() {
    score = 0;
    baseSpeed = 0;
    speedMultiplier = SPEED_MULTIPLIER_BASE;
    carsPassed = 0;
    obstaclesAvoided = 0;
    frameCounter = 0;
}

void PointsManager::updateSpeed(int playerSpeed) {
    baseSpeed = playerSpeed;
    speedMultiplier = SPEED_MULTIPLIER_BASE + (playerSpeed * SPEED_MULTIPLIER_INCREMENT);
}

void PointsManager::update() {
    frameCounter++;
    float basePointsPerFrame = POINTS_PER_FRAME_BASE + (speedMultiplier * POINTS_PER_FRAME_MULTIPLIER);
    int timePoints = static_cast<int>(basePointsPerFrame);

    if(timePoints > 0) {
        score += timePoints;
    }
}

void PointsManager::addCarPass() {
    int points = static_cast<int>(POINTS_CAR_PASS * speedMultiplier);
    score += points;
    carsPassed++;
}

void PointsManager::addObstacleAvoided() {
    int points = static_cast<int>(POINTS_OBSTACLE * speedMultiplier);
    score += points;
    obstaclesAvoided++;
}


#endif
