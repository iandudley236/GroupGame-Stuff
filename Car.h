//
//  Car.h
//  SDL_Prac_1
//
//  Created by Jody Spikes on 11/13/25.
//

#ifndef Car_h
#define Car_h

#include "Const.h"
#include "SDL_Plotter.h"
#include "BaseObject.h"
#include "Utils.h"
#include <algorithm>

class Car: public Base{
private:
    point _loc, _prvLoc;
    color _color;
    int   _size;
    int   _speed;

public:
    Car() : _loc{point(ROW / 2, COL - SIZE - 50)},
            _prvLoc{ROW / 2, COL - SIZE - 50},
            _color{color{255, 30, 30}},
            _size{SIZE},
            _speed{5} {}

    void Start(Engine*,SDL_Plotter*) override;
    void Update() override;
    void FixedUpdate() override;

    void move(char direction);
    void draw(SDL_Plotter& g);

    // Speed control
    void setSpeed(int speed);

    // Getters for collision detection
    point getLoc() const { return _loc; }
    int getSize() const { return _size; }
    int getSpeed() const { return _speed; }
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void Car::Start(Engine* eng, SDL_Plotter* plot){
	Base::Start(eng, plot);


}
void Car::Update(){

}
void Car::FixedUpdate(){
	if(sdlPlot->kbhit()) {
		char c = toupper(sdlPlot->getKey());

	    switch(c) {
	    	case 'C': sdlPlot->clear(); break;
	        case RIGHT_ARROW: move(RIGHT_ARROW); break;
	        case LEFT_ARROW: move(LEFT_ARROW); break;
	        case UP_ARROW: move(UP_ARROW); break;
	        case DOWN_ARROW: move(DOWN_ARROW); break;
	    }
	}
	draw(*sdlPlot);
}

void Car::move(char direction){
    _prvLoc.x = _loc.x;
    _prvLoc.y = _loc.y;

    switch(direction){
        //Right Move, with road constraint
        case RIGHT_ARROW:
            if(_loc.x < (ROW * 3 / 4) - _size/2 - 10) {
                _loc.x += _speed;
            }
            break;

        //Left Move, with road constraint
        case LEFT_ARROW:
            if(_loc.x > (ROW / 4) + _size/2 + 10) {
                _loc.x -= _speed;
            }
            break;

        //Increase Speed (UP arrow)
        case UP_ARROW:
            _speed = std::min(_speed + 1, 15);
            break;

        //Decrease Speed (DOWN arrow)
        case DOWN_ARROW:
            _speed = std::max(_speed - 1, 2);
            break;
    }
}

void Car::draw(SDL_Plotter& g){
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

void Car::setSpeed(int speed) {
    _speed = speed;
}


#endif /* Car_h */
