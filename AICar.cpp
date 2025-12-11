//
//  AICar.cpp
//  SDL_Prac_1
//
//  AI-controlled racing car implementation
//

#include "AICar.h"
#include "Utils.h"
#include <cstdlib>

AICar::AICar(int startX, int startY, color carColor, int speed)
    : _loc{point(startX, startY)},
      _prvLoc{startX, startY},
      _color{carColor},
      _size{SIZE},
      _speed{speed},
      laneChangeTimer{0},
      laneChangeDelay{120},  // Change lanes every ~4 seconds at 30fps
      changingLane{false}
{
    // REMOVED srand() - should only be called once in main()
    initializeLanes();

    // Start in a random lane
    targetLane = selectRandomLane();
    _loc.x = getLaneXPosition(targetLane);
}

void AICar::Start(Engine* eng, SDL_Plotter* plot){
	Base::Start(eng,plot);

	respawn();
}
void AICar::Update(){
	draw(*sdlPlot);
	updateAI();
}
void AICar::FixedUpdate(){

}

void AICar::initializeLanes() {
    int rdStrt = ROW / 4;
    int rdEnd = ROW * 3 / 4;
    int roadWidth = rdEnd - rdStrt;

    // Define three lanes within the road
    leftLaneX = rdStrt + roadWidth / 6;
    centerLaneX = ROW / 2;
    rightLaneX = rdEnd - roadWidth / 6;
}

int AICar::getLaneXPosition(AILane lane) {
    switch(lane) {
        case LEFT_LANE:   return leftLaneX;
        case CENTER_LANE: return centerLaneX;
        case RIGHT_LANE:  return rightLaneX;
        default:          return centerLaneX;
    }
}

AILane AICar::selectRandomLane() {
    int random = rand() % 3;
    return static_cast<AILane>(random);
}

void AICar::updateLaneChange() {
    int targetX = getLaneXPosition(targetLane);

    // Smoothly move toward target lane
    if(_loc.x < targetX - 2) {
        _loc.x += 2;  // Move right
        changingLane = true;
    }
    else if(_loc.x > targetX + 2) {
        _loc.x -= 2;  // Move left
        changingLane = true;
    }
    else {
        _loc.x = targetX;  // Snap to lane
        changingLane = false;
    }
}

void AICar::updateAI() {
    _prvLoc.x = _loc.x;
    _prvLoc.y = _loc.y;

    // Move forward (down the screen relative to player)
    _loc.y += _speed;

    // Lane change logic
    laneChangeTimer++;

    if(!changingLane && laneChangeTimer >= laneChangeDelay) {
        // Time to consider changing lanes
        int decision = rand() % 100;

        if(decision < 30) {  // 30% chance to change lanes
            AILane newLane = selectRandomLane();

            // Don't select the same lane we're already in
            if(newLane == targetLane) {
                newLane = static_cast<AILane>((newLane + 1) % 3);
            }

            targetLane = newLane;
        }

        laneChangeTimer = 0;
    }

    // Smooth lane changing
    updateLaneChange();
}

void AICar::draw(SDL_Plotter& g) {
    int whlSize = _size / 5 + 2;
    color black(0, 0, 0);

    // Car base
    drawRect(_loc.x - _size/2, _loc.y - _size/2, _size, _size, _color, g);

    // Wheels
    drawRect(_loc.x - _size/2, _loc.y - _size/2, whlSize, whlSize, black, g);
    drawRect(_loc.x + _size/2 - whlSize, _loc.y - _size/2, whlSize, whlSize, black, g);
    drawRect(_loc.x - _size/2, _loc.y + _size/2 - whlSize, whlSize, whlSize, black, g);
    drawRect(_loc.x + _size/2 - whlSize, _loc.y + _size/2 - whlSize, whlSize, whlSize, black, g);
}

bool AICar::isOffScreen() {
    return _loc.y > COL + _size;
}

void AICar::respawn() {
    // Respawn at top of screen in a random lane
    targetLane = selectRandomLane();
    _loc.x = getLaneXPosition(targetLane);
    _loc.y = -_size - (rand() % 200);  // Random spacing
    _prvLoc = _loc;
    laneChangeTimer = 0;
}
