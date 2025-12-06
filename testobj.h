/*
 * testobj.h
 *
 *  Created on: Nov 28, 2025
 *      Author: iandu
 */

#ifndef TESTOBJ_H_
#define TESTOBJ_H_

#include "BaseObject.h"
#include "Const.h"
#include "SDL_Plotter.h"

class Background: public Base{
private:
    SDL_Plotter Plot;

public:
	Background();
	void Start(Engine*) override;
	void Update() override;
	void FixedUpdate() override;
};

void drawCircle(point loc, int size, color c, SDL_Plotter& g){
	for(double i = -size; i <= size;i+=0.1){
		for(double j = -size; j <= size; j+=0.1){
			if(i*i + j*j <= size*size){
				g.plotPixel(round(loc.x+i),round(loc.y+j),c);
			}
		}
	}
}

Background::Background(){
	scaleX = ROW;
	scaleY = COL;
	Plot = SDL_Plotter(scaleX,scaleY);
}

void Background::Start(Engine* eng){
	Base::Start(eng);


}
void Background::Update(){

}
void Background::FixedUpdate(){

}


/*
 * class this{
 * 		private:
 * 			int i;
 * 	}
 */



#endif /* TESTOBJ_H_ */
