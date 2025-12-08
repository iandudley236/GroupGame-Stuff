//
//  Utils.h
//  SDL_Prac_1
//
//  Shared utility functions
//

#ifndef Utils_h
#define Utils_h
#include "SDL_Plotter.h"
#include "Const.h"

// Shared rectangle drawing function
inline void drawRect(int x, int y, int width, int height, color c, SDL_Plotter& g){
    for(int row = y; row < y + height; row++){
        for(int col = x; col < x + width; col++){
            if(col >= 0 && col < ROW && row >= 0 && row < COL) {
                g.plotPixel(col, row, c);
            }
        }
    }
}

#endif /* Utils_h */
