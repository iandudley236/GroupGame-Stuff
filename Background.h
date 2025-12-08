#ifndef Background_h
#define Background_h
#include "SDL_Plotter.h"
#include "Const.h"
#include "BaseObject.h"


class Background: public Base{
    int offset;

    Background();
    void update();
    void draw(SDL_Plotter&);

	void Start(Engine*,SDL_Plotter*) override;
	void Update() override;
	void FixedUpdate() override;

};


#endif /* Background_h */
