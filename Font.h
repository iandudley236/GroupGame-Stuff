/*
 * Font.h - Dual Size Pixel Font Renderer (Upper/Lower Case)
 *  Created on: Dec 7, 2025
 *      Author: Haileyp
 */

#ifndef FONT_H_
#define FONT_H_

#include "SDL_Plotter.h"
#include <string>
#include <cctype>

class FontRenderer {
public:
    static void drawLarge(SDL_Plotter& g, int x, int y, color c, const std::string& text, int flashTimer = 0);
    static void drawSmall(SDL_Plotter& g, int x, int y, color c, const std::string& text, int flashTimer = 0);
};



#endif /* FONT_H_ */
