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
#include "Utils.h"
#include <cstdlib>

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

    // Check if obstacle is off screen
    bool isOffScreen() const;
    void respawn();
    void deactivate() { _active = false; }
    bool isActive() const { return _active; }

    // Getters
    point getLocation() const { return _loc; }
    int getSize() const { return _size; }
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/*
 * obstacles.push_back(Obstacle(ROW/2 - 50, -100, color(255, 140, 0), 25, 3));
    obstacles.push_back(Obstacle(ROW/2 + 80, -300, color(255, 140, 0), 25, 3));
    obstacles.push_back(Obstacle(ROW/2 - 120, -500, color(255, 140, 0), 25, 3));
 */

Obstacle::Obstacle()
	:_loc(point(rand()%600, 0)),
	 _color(color(255,140,0)),
	 _size(30),
	 _speed(3),
	 _active(true){
}

Obstacle::Obstacle(int x, int y, color c, int size, int speed)
    : _loc{point(x, y)},
      _color{c},
      _size{size},
      _speed{speed},
      _active{true}
{}

void Obstacle::Start(Engine* eng,SDL_Plotter* plot){
	Base::Start(eng, plot);

	respawn();
}

void Obstacle::Update(){

}

void Obstacle::FixedUpdate(){
	moveDown();
	draw(*sdlPlot);
	if (isOffScreen()){
		delete this;
	}
}


void Obstacle::moveDown() {
    // Move obstacle down the screen
    _loc.y += _speed;
    if (isOffScreen()){
    	delete this;
    }
}

void Obstacle::draw(SDL_Plotter& g) {
    if (!_active) return;

    // Draw a triangle obstacle (cone/barrier)
    color orange(255, 140, 0);
    color white(255, 255, 255);

    // Draw triangle shape
    for(int y = 0; y < _size; y++) {
        int width = (y * _size) / _size;
        for(int x = -width/2; x <= width/2; x++) {
            int drawX = _loc.x + x;
            int drawY = _loc.y - _size/2 + y;

            if(drawX >= 0 && drawX < ROW && drawY >= 0 && drawY < COL) {
                // Alternating stripes for traffic cone look
                if(y / 5 % 2 == 0) {
                    g.plotPixel(drawX, drawY, orange);
                } else {
                    g.plotPixel(drawX, drawY, white);
                }
            }
        }
    }
}

bool Obstacle::isOffScreen() const {
    return _loc.y > COL + _size;
}

void Obstacle::respawn() {
    // Respawn at top of screen in a random lane
    int rdStrt = ROW / 4;
    int rdEnd = ROW * 3 / 4;
    int roadWidth = rdEnd - rdStrt;

    // Pick random x position within road
    _loc.x = rdStrt + 50 + (rand() % (roadWidth - 100));
    _loc.y = -_size - (rand() % 300);  // Random spacing
    _active = true;
}


#endif /* Obstacle_h */
