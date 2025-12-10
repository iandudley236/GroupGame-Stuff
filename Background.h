#ifndef Background_h
#define Background_h

#include "SDL_Plotter.h"
#include "Const.h"
#include "BaseObject.h"
#include <stdio.h>

class Background: public Base{
private:
    int offset;
    Car* carPointer;

public:
    Background();
    void update(int playerSpeed);
    void draw(SDL_Plotter&);

	void Start(Engine*,SDL_Plotter*) override;
	void Update() override;
	void FixedUpdate() override;

};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Background::Background(): offset(0), carPointer(engine->Find<Car>()) {}

void Background::Start(Engine* eng,SDL_Plotter* plot){
	Base::Start(eng, plot);
}
void Background::Update(){

}
void Background::FixedUpdate(){
	draw(*sdlPlot);
	update(carPointer->getSpeed());
}

void Background::draw(SDL_Plotter& g){
    //Grass
    color _grass(34,139, 34);
    for(int y = 0; y < COL; y++){
        for(int x = 0; x < ROW; x++){
            g.plotPixel(x, y, _grass);
        }
    }

    //Road
    color _road(60,60,60);
    int rdStrt = ROW / 4;
    int rdEnd  = ROW * 3 /4;
    for(int y = 0; y < COL; y++){
        for(int x = rdStrt; x < rdEnd; x++){
            g.plotPixel(x,y,_road);
        }
    }

    //Lines
    color _yellow(255,255,0);
    int centerX    = ROW / 2;
    int dashLength = 30;
    int gapLength  = 20;

    for(int y = 0; y < COL; y++){

        int adjustedY = (y + offset) % (dashLength + gapLength);
        if(adjustedY < dashLength){
            for(int i = -2; i <= 2; i++){
                g.plotPixel(centerX + i, y, _yellow);
            }
        }
    }

    // Draw white lane markers on sides (dashed)
    color white(255, 255, 255);
    int leftLane = rdStrt + 50;
    int rightLane = rdEnd - 50;

    for(int y = 0; y < COL; y++){
        int adjustedY = (y + offset) % (dashLength + gapLength);
        if(adjustedY < dashLength){
            for(int i = -1; i <= 1; i++){
                g.plotPixel(leftLane + i, y, white);
            }
            for(int i = -1; i <= 1; i++){
                g.plotPixel(rightLane + i, y, white);
            }
        }
    }
    for(int y = 0; y < COL; y++){
        for(int i = -2; i <= 2; i++){
            g.plotPixel(rdStrt + i, y, white);
            g.plotPixel(rdEnd + i, y, white);
        }
    }
}



void Background::update(int playerSpeed){
    offset -= playerSpeed;
    if(offset <= -50) offset = 0;
}

#endif /* Background_h */
