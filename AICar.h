//
//  AICar.h
//  SDL_Prac_1
//
//  AI-controlled racing car
//

#ifndef AICar_h
#define AICar_h
#include "Const.h"
#include "SDL_Plotter.h"
#include "BaseObject.h"

enum AILane {
    LEFT_LANE,
    CENTER_LANE,
    RIGHT_LANE
};

class AICar : public Base{
private:
    point _loc, _prvLoc;
    color _color;
    int   _size;
    int   _speed;

    // AI behavior variables
    AILane targetLane;
    int laneChangeTimer;
    int laneChangeDelay;
    bool changingLane;

    // Lane positions
    int leftLaneX;
    int centerLaneX;
    int rightLaneX;

    void initializeLanes();
    int getLaneXPosition(AILane lane);
    void updateLaneChange();
    AILane selectRandomLane();

public:
    AICar(int startX, int startY, color carColor, int speed = 3);

	void Start(Engine*,SDL_Plotter*) override;
	void Update() override;
	void FixedUpdate() override;

    void updateAI();
    void draw(SDL_Plotter& g);

    // Getters for collision detection
    point getLocation() const { return _loc; }
    int getSize() const { return _size; }
    int getSpeed() const { return _speed; }

    // Check if AI car is off screen (for respawning)
    bool isOffScreen();
    void respawn();
};

#endif /* AICar_h */
