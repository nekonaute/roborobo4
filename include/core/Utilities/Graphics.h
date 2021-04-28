/*
 *  Graphics.h
 *  roborobo
 *
 *  Created by Nicolas on 16/01/09.
 *
 */

#ifndef GRAPHICS_H
#define GRAPHICS_H

//#include "RoboroboMain/roborobo.h"
#include "RoboroboMain/common.h"

extern int gSnapshotIndex;
extern int gRenderScreenshotIndex;
extern int gFullLoggerScreenshotIndex;
extern int gEnvironmentScreenshotIndex; 
extern int gTrajectoryImageIndex;

bool initSDL(Uint32 flags = 0); // parameter is optional (default: SDL_HWSURFACE | SDL_DOUBLEBUF)

//Uint32 getPixel32( SDL_Surface *surface, int x, int y );
//void putPixel32( SDL_Surface *surface, int x, int y, Uint32 pixel );

inline Uint32 getPixel32( SDL_Surface *surface, int x, int y )
{
    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;
    return pixels[ ( y * surface->w ) + x ];
}

inline Uint32 getPixel32_secured( SDL_Surface *surface, int x, int y )
{
    //Get the requested pixel
	if ( x >= 0 && x < surface->w && y >= 0 && y < surface->h )
        return getPixel32(surface, x, y);
	else
		return -1;
}

inline Uint32 getPixel32_pbc( SDL_Surface *surface, int x, int y ) // pbc = periodic boundary conditions
{
    if ( x < 0 )
    {
        x = x + surface->w;
        if (x < 0) // expected: one iteration
        {
            std::cout << "[ERROR] getpixel is looping over the screen.\n";
            exit(-1);
        }
    }
    else
        if ( x >= surface->w )
        {
            x = x % surface->w; // expected: one iteration
        }
    if ( y < 0 )
    {
        y = y + surface->h;
        if (y < 0) // expected: one iteration
        {
            std::cout << "[ERROR] getpixel is looping over the screen.\n";
            exit(-1);
        }
    }
    else
        if ( y >= surface->h )
        {
            y = y % surface->h; // expected: one iteration
        }
    return getPixel32(surface, x, y);
}

inline void putPixel32( SDL_Surface *surface, int x, int y, Uint32 pixel )
{
    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;

    //Set the pixel
    pixels[(y * (surface->w)) + x] = pixel;
}

inline void putPixel32_secured(SDL_Surface *surface, int x, int y, Uint32 pixel) // check borders (8% slower)
{
    if (x >= 0 && x < surface->w && y >= 0 && y < surface->h)
        putPixel32(surface, x, y, pixel);
}

inline void putPixel32_pbc(SDL_Surface *surface, int x, int y, Uint32 pixel) // pbc = periodic boundary conditions
{
    if ( x < 0 )
    {
        x = x + surface->w;
        if (x < 0) // expected: one iteration
        {
            std::cout << "[ERROR] putpixel is looping over the screen.\n";
            exit(-1);
        }
    }
    else
        if ( x >= surface->w )
        {
            x = x % surface->w; // expected: one iteration
        }
    if ( y < 0 )
    {
        y = y + surface->h;
        if (y < 0) // expected: one iteration
        {
            std::cout << "[ERROR] putpixel is looping over the screen.\n";
            exit(-1);
        }
    }
    else
        if ( y >= surface->h )
        {
            y = y % surface->h; // expected: one iteration
        }
    putPixel32(surface, x, y, pixel);
}

void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip = NULL);
void apply_surface_pbc(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip = NULL);

void register_robotMask(int __x, int __y, SDL_Surface *destination, int __id); // use gRobotMaskData
void clean_robotMask(int __x, int __y, SDL_Surface *destination); // use gRobotMaskData

void register_surface(int __x, int __y, SDL_Surface *source, SDL_Surface *destination, int __id); // unused as of 2014-03-28
void clean_surface(int __x, int __y, SDL_Surface *source, SDL_Surface *destination); // unused as of 2014-03-28

void toggle_fullscreen();

SDL_Surface *load_image(const std::string &filename);

void saveCustomScreenshot(const std::string &__comment = "");

void saveRenderScreenshot(const std::string &__comment = "");

void saveFullLoggerScreenshot(const std::string &__comment = "");

void saveEnvironmentScreenshot(const std::string &__comment = "");

void saveFootprintScreenshot(const std::string &__comment = "");

void saveTrajectoryImage(const std::string &_comment = "");

void saveImage(SDL_Surface image, std::string __prefix, std::string __comment = "");

// Draw a line
// Algorithm: Bresenham
// adapted from: http://www.roguebasin.com/index.php?title=Bresenham%27s_Line_Algorithm
void drawLine(SDL_Surface *image,
              int x1,
              int y1,
              int const x2,
              int const y2,
              uint8_t r, uint8_t g, uint8_t b);

// Cast a line. Do not draw. Stops when no-white pixel hit. return updated x2 and y2 (pointers), and collision (true|false).
// Algorithm: Bresenham
// adapted from: http://www.roguebasin.com/index.php?title=Bresenham%27s_Line_Algorithm
// if ignoreValue != -1, then consider ignoreValue as blank. Usage: _ignoreValue = robot_id + gRobotIndexStartOffset
//  => used to ignore robot self when tracing sensor ray.
bool castLine(SDL_Surface * image,
              int x1,
              int y1,
              int *x2pt,
              int *y2pt,
              int maxLength = -1,
              int ignoreValue = -1
              );

void renderSnapshot();

#endif // GRAPHICS_H

