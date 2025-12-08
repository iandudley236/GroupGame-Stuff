//
//  Func.h
//  SDL_Prac_1
//
//  Created by Jody Spikes on 11/13/25.
//

#ifndef Func_h
#define Func_h

void drawCircle(point loc, int size, color c, SDL_Plotter& g){
    for(double i = -size; i <= size;i+=0.1){
        for(double j = -size; j <= size; j+=0.1){
            if(i*i + j*j <= size*size){
                g.plotPixel(round(loc.x+i),round(loc.y+j),c);
            }
        }
    }

}

#endif /* Func_h */
