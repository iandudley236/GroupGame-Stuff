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

#endif /* Car_h */
