//
//  Obstacle.h
//  SDL_Prac_1
//
//  Obstacles for collision detection
//

#ifndef Obstacle_h
#define Obstacle_h
#include "Const.h"
#include "SDL_Plotter.h"
#include "BaseObject.h"
#include "Car.h"
#include "Engine.h"

class Obstacle : public Base{
private:
    point _loc;
    color _color;
    int _size;
    int _speed;
    bool _active;
public:
    Obstacle();
    Obstacle(int x, int y, color c, int size = 30, int speed = 3);

	void Start(Engine*,SDL_Plotter*) override;
	void Update() override;
	void FixedUpdate() override;

    void moveDown();
    void draw(SDL_Plotter& g);

    // Collision detection
    bool collidesWith(const Car& car) const;

    // Check if obstacle is off screen
    bool isOffScreen() const;
    void respawn();
    void deactivate() { _active = false; }
    bool isActive() const { return _active; }

    // Getters
    point getLocation() const { return _loc; }
    int getSize() const { return _size; }
};

#endif /* Obstacle_h */
