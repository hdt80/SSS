#include "render/Renderer.h"

// =================================
// Consctuctor
// =================================
Renderer::Renderer(SDL_Window* window, int height, int width) :
				   _height(height), _width(width) {
	_render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	_font   = TTF_OpenFont("res/Pixel.ttf", 12); // arg2 = font size

	if (_render == nullptr) {
		error("Failed to create renderer: %s\n", SDL_GetError());
	}
	if (_font == nullptr) {
		error("Failed to load font: %s\n", TTF_GetError());
	}

	clear();
}

// =================================
// Deconstructor
// =================================
Renderer::~Renderer() {
	SDL_DestroyRenderer(_render);
	_render = nullptr;
	// Don't close SDL as other objects may still be using SDL
}

// =================================
// Methods
// =================================

// Render the screen
void Renderer::render() {
	SDL_RenderPresent(_render);
}

// Clear everything on the renderer and then clear the screen to black
void Renderer::clear() {
	clear(0x00, 0x00, 0x00, 0x00); // white
}

// Clear everything on the renderer then draw the color in RGBA
// r - Red value to draw
// g - Green value to draw
// b - Blue value to draw
// a - Opacity (Alpha) to draw
void Renderer::clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	SDL_SetRenderDrawColor(_render, r, g, b, a);
	SDL_RenderClear(_render);
}

// Set the color we'll draw shapes to
// r - Red value to draw
// g - Green value to draw
// b - Blue value to draw
void Renderer::setColor(Uint8 r, Uint8 g, Uint8 b) {
	SDL_SetRenderDrawColor(_render, r, g, b, 0xFF);
}

// Set the color we'll draw shapes to with an opacity
// r - Red value to draw
// g - Green value to draw
// b - Blue value to draw
// a - Opacity (Alpha) to draw
void Renderer::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	SDL_SetRenderDrawColor(_render, r, g, b, a);
}

// Draw text at the x and y coords provided
// x - x coord to draw text
// y - y coord to draw text
// w - width of text box
// h - height of text box
// text - Text to draw at x and y
void Renderer::drawText(double x, double y, double w, double h, std::string text) {
	SDL_Color color = {0xFF, 0x00, 0x00}; // Red
	// Surface we'll be rending onto the screen, as we cannot create a texture from ttf
	SDL_Surface* textSurface = TTF_RenderText_Solid(_font, text.c_str(), color);
	// We'll take the surface and convert that into a texture that can be drawn
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(_render, textSurface);
	// Create a rect that'll contain the message so we can store it into our RAM
	SDL_Rect textRect = {calc_w(x), calc_h(y), calc_w(w), calc_h(h)};

	// We'll then copy the contents of the texture into the rect so we can draw it
	SDL_RenderCopy(_render, textTexture, nullptr, &textRect);

	// Deallocate those or else that's a big memory leak
	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textSurface);
	textSurface = nullptr;
	textTexture = nullptr;
}

// Draw text at the x and y coords but calculate the text width at runtime
// x - x coord to begin drawing text
// y - y coord
// fontSize - the height of a single letter, such as 12pt font
// text - Text to draw
void Renderer::drawText(double x, double y, std::string text) {
	SDL_Color color = {0xFF, 0x00, 0x00}; // Red
	SDL_Surface* textSurface = TTF_RenderText_Solid(_font, text.c_str(), color);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(_render, textSurface);
	// 15 is the magic number to remove all streching, idk why
	SDL_Rect textRect = {calc_w(x), calc_h(y), text.size() * 8, 15};

	SDL_RenderCopy(_render, textTexture, nullptr, &textRect);

	// Deallocate those or else that's a big memory leak
	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textSurface);
	textSurface = nullptr;
	textTexture = nullptr;
}

// Draw a single-pixel sized dot
// x - x coord of the point
// y - y coord of the point
void Renderer::drawDot(double x, double y) {
	SDL_RenderDrawPoint(_render, calc_w(x), calc_h(y));
}

// Draw a line between the two coords
// Points should be provided between 0 and 1 as they are converted to
// screen pixels at runtime
void Renderer::drawLine(double x1, double y1, double x2, double y2) {
	//debug("x1: %f | y1: %f | x2: %f | y2: %f\n", x1, y1, x2, y2);
	SDL_RenderDrawLine(_render, calc_w(x1), calc_h(y1), calc_w(x2), calc_h(y2));
}

// Draw a box at the x and y, with and w(idth) and h(eight)
// w and h should be ratios, just like every other number
// A positive h isn't up, it's down. just a little fyi for people like
// me who forgot that and spent 2.5 hours trying to figure that out
void Renderer::drawBox(double x, double y, double w, double h) {
	SDL_Rect box = {calc_w(x), calc_h(y), calc_w(w), calc_h(h)}; // Init list
	SDL_RenderFillRect(_render, &box);
}

void Renderer::drawRect(double x, double y, double w, double h) {
	SDL_Rect rect = {calc_w(x), calc_h(y), calc_w(w), calc_h(h)}; // Init list
	SDL_RenderDrawRect(_render, &rect);
}

int Renderer::calc_w(double w) {
	//debug("Renderer::calc_w> %i * %f -> %i\n", _width, w, int(_width * w));
	return int(_width * w);
}

int Renderer::calc_h(double h) {
	//debug("Renderer::calc_h> %i * %f -> %i\n", _height, h, int(_height * h));
	return int(_height * h);
}