#ifndef RENDER_RENDERER_H
#define RENDER_RENDERER_H

class Window; // Create a forward declaration of the Window we're in

#include <cstdint>
#include <string>

#include "SDL.h"
#include "SDL_ttf.h"
#include "util/Logger.h"

// Wrapper for rendering everything in a panel. Coords are from 0 to 1
// with 0 being the smallest, and 1 the largest.
// 0,0 - Top left
// 0,1 - Top right
// 1,0 - Bottom left
// 1,1 - Bottom right
class Renderer {
	public:
		// Height and width will be used to determine how the coords
		// from 0-1 will be translated into pixels
		Renderer(SDL_Window* window, int height, int width);
		~Renderer();

		// Render everything from _render onto the screen
		void render();

		// Create a viewport
		void createViewport(double x, double y, double w, double h);

		// Clear the screen to the default color, black
		void clear();
		// Clear the screen to the RGBA values provided
		void clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

		// Set the color we'll render the screen
		void setColor(Uint8 r, Uint8 g, Uint8 b);
		// Set the color with an opacity
		void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

		// Draw a text message inside a hollow rect
		void drawText(double x, double y, double w, double h, std::string text);
		// Draw text but automatically calculate width
		void drawText(double x, double y, std::string text);

		// Draw a point at the x and y
		void drawDot(double x, double y);
		// Draw a line between the two points. 
		void drawLine(double x1, double y1, double x2, double y2);
		// Draw a box between two points
		void drawBox(double x, double y, double w, double h);
		// Draw a hollow rectangle between two points
		void drawRect(double x, double y, double w, double h);

	private:
		// Convert the point between 0 and 1 to pixels to the screen
		int calc_w(double w); // Convert the width ratio to pixels 
		int calc_h(double h); // Convert the height ratio to pixels

		SDL_Renderer* _render; // Renderer we're rendering to
		TTF_Font*     _font;   // Font we'll use

		int _height; // Height of the Renderer
		int _width;  // ^
};

#endif