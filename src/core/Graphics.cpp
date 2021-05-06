/*
 *  Graphics.cpp
 *  roborobo
 *
 *  Created by Nicolas on 16/01/09.
 *  Copyright 2009. All rights reserved.
 *
 */

#include "RoboroboMain/roborobo.h"
#include "Utilities/Graphics.h"
#include "Utilities/Misc.h"
#include "WorldModels/RobotWorldModel.h"
#include "Agents/Robot.h"

int gSnapshotIndex = 0;
int gRenderScreenshotIndex = 0; // numbering screenshots
int gFullLoggerScreenshotIndex = 0; // number calls to full logger
int gEnvironmentScreenshotIndex = 0;
int gFootprintScreenshotIndex = 0;
int gTrajectoryFileIndex = 0; // numbering trajectory images (used by saveTrajectoryImage(...))

void renderSnapshot();

void saveImage(SDL_Surface *image, const std::string &prefix, const std::string &comment) // comment is optional
{
    std::string sLog = gLogDirectoryname + "/" + prefix + "_" + gStartTime + "_" + getpidAsReadableString();

    if (!comment.empty())
        sLog += "_" + comment;

    if (gOutputImageFormat)
    {
        sLog += ".bmp";
        SDL_SaveBMP(image, sLog.c_str()); // dependance: SDL only
    }
    else
    {
        sLog += ".png";
        IMG_SavePNG(image, sLog.c_str()); // dependance: SDL+SDL_image
    }
}

void saveCustomScreenshot(const std::string &_comment)
{
    // preparing

    std::string snapshotIndexStr = convertToString(gSnapshotIndex);

    while (snapshotIndexStr.length() < 6)
    {
        snapshotIndexStr = "0" + snapshotIndexStr;
    }
    renderSnapshot();

    // saving

    saveImage(gSnapshot, "screenshot_custom", snapshotIndexStr + "_" + _comment);

    gSnapshotIndex++;
}

void renderSnapshot()
{
    // rendering

    SDL_FillRect(gSnapshot, &gSnapshot->clip_rect,
                 SDL_MapRGBA(gSnapshot->format, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE)); // clear screen

    if (gCustomSnapshot_niceRendering)
    {
        // nice snapshot
        apply_surface(0, 0, gFootprintImage, gSnapshot, &gCamera);
        apply_surface(0, 0, gForegroundImage, gSnapshot, &gCamera);
    }
    else
    {
        // true snapshot
        apply_surface(0, 0, gEnvironmentImage, gSnapshot, &gCamera);
        apply_surface(0, 0, gForegroundImage, gSnapshot, &gCamera);
    }

    if (gCustomSnapshot_showLandmarks)
    {
        for (int i = 0; i != gNbOfLandmarks; i++)
        {
            if (gLandmarks[i]->isVisible())
                gLandmarks[i]->show(gSnapshot);
        }
    }

    if (gCustomSnapshot_showObjects)
    {
        for (int i = 0; i != gNbOfPhysicalObjects; i++)
        {
            if (gPhysicalObjects[i]->isVisible())
                gPhysicalObjects[i]->show(gSnapshot);
        }
    }

    if (gCustomSnapshot_showRobots)
    {
        int backupDisplaySensorsValue = gDisplaySensors;
        if (gCustomSnapshot_showSensorRays)
            gDisplaySensors = 2;
        else
            gDisplaySensors = 0;
        for (int i = 0; i != gNbOfRobots; i++)
        {
            // Show agent(s) on the screen
            gRobots[i]->show(gSnapshot);
        }
        gDisplaySensors = backupDisplaySensorsValue;
    }
}

void saveTrajectoryImage(const std::string &_comment)
{

    if (gTrajectoryMonitor)
    {
        std::string trajectoryFileIndexStr = convertToString(gTrajectoryFileIndex);
        while (trajectoryFileIndexStr.length() < 6)
        {
            trajectoryFileIndexStr = "0" + trajectoryFileIndexStr;
        }

        std::string timestamp = convertToString(gTrajectoryMonitorIt);
        //while( timestamp.length() < 10 )
        //{
        //    timestamp =  "0" + timestamp;
        //}
        timestamp = "_it" + timestamp;

        std::string s = trajectoryFileIndexStr;

        if (gTrajectoryMonitorMode == 0)
            s += timestamp + "_all";
        else
            s += timestamp + "_single";

        if (!_comment.empty())
            s += "_" + _comment;

        saveImage(gTrajectoryMonitorImage, "trajectory", s);

        SDL_FreeSurface(gTrajectoryMonitorImage);
        gTrajectoryMonitor = false;

        gTrajectoryFileIndex++;

    }
    else
    {
        std::cout << "[WARNING] Cannot save trajectories. Monitor is not in use.\n";
    }
}

void saveRenderScreenshot(const std::string &_comment) // parameter is optional
{
    std::string screenShotIndexStr = convertToString(gRenderScreenshotIndex);

    while (screenShotIndexStr.length() < 6)
    {
        screenShotIndexStr = "0" + screenShotIndexStr;
    }

    saveImage(gArena, "screenshot_render", screenShotIndexStr + "_" + _comment);

    gRenderScreenshotIndex++;
}

void saveFullLoggerScreenshot(const std::string &_comment) // parameter is optional
{
    std::string screenShotIndexStr = convertToString(gFullLoggerScreenshotIndex);

    while (screenShotIndexStr.length() < 9)
    {
        screenShotIndexStr = "0" + screenShotIndexStr;
    }

    std::string comment = "";
    if (!_comment.empty())
        comment += "_" + _comment;

    if (gDisplayMode != 2)
        saveImage(gArena, "fullLogger_gArena", screenShotIndexStr + comment);

    saveImage(gEnvironmentImage, "fullLogger_gEnvironmentImage", screenShotIndexStr + comment);
    saveImage(gFootprintImage, "fullLogger_gFootprintImage", screenShotIndexStr + comment);

    std::string filename =
            gLogDirectoryname + "/fullLogger_" + gStartTime + "_" + getpidAsReadableString() + "_" + screenShotIndexStr
            + comment + ".txt";

    std::ofstream file;
    file.open(filename.c_str());

    if (!file)
    {
        std::cout << "[error] Cannot open Full Logger text file " << std::endl;
        exit(-1);
    }

    std::string s = "### ### ###\n### Full logger\n\n### ### ###\n";
    
    s += "#\n#\n# Robots\n";
    s += "#\n# id, x, y, orientation, groupId, LED_redValue, LED_greenValue, LED_blueValue, energyLevel, isAlive, isRegistered\n";
    s += "#\n#\n";
   
    for ( int i = 0 ; i < gNbOfRobots ; i++ )
    {
        int x,y;
        gRobots[i]->getCoord(x, y);
        
        std::stringstream out;
        out << gRobots[i]->getWorldModel()->getId();
        out << ",";
        out << x;
        out << ",";
        out << y;
        out << ",";
        out << gRobots[i]->getWorldModel()->_agentAbsoluteOrientation;
        out << ",";
        out << gRobots[i]->getWorldModel()->getGroupId();
        out << ",";
        out << gRobots[i]->getWorldModel()->getRobotLED_redValue();
        out << ",";
        out << gRobots[i]->getWorldModel()->getRobotLED_greenValue();
        out << ",";
        out << gRobots[i]->getWorldModel()->getRobotLED_blueValue();
        out << ",";
        out << gRobots[i]->getWorldModel()->getEnergyLevel();
        out << ",";
        out << gRobots[i]->getWorldModel()->isAlive();
        out << ",";
        out << gRobots[i]->isRegistered();
        out << "\n";
        s += out.str();
    }
    
    s += "### ### ###\n#\n# Physical Objects\n";
    s += "#\n# id, x, y, isVisible\n";
    s += "#\n#\n";
    
    for ( int i = 0 ; i < gNbOfPhysicalObjects ; i++ )
    {
        std::stringstream out;
        out << i;
        out << ",";
        out << gPhysicalObjects[i]->getXCenterPixel();
        out << ",";
        out << gPhysicalObjects[i]->getYCenterPixel();
        out << ",";
        out << gPhysicalObjects[i]->isVisible();
        out << "\n";
        s += out.str();
    }

    s += "### ### ###\n#\n# Landmarks\n";
    s += "#\n# id, x, y\n";
    s += "#\n#\n";

    for ( int i = 0 ; i < gNbOfLandmarks ; i++ )
    {
        Point2d pos = gLandmarks[i]->getCoordinates();
        std::stringstream out;
        out << i;
        out << ",";
        out << pos.x;
        out << ",";
        out << pos.y;
        out << "\n";
        s += out.str();
    }
    
    file << s;

    file.close();

    gFullLoggerScreenshotIndex++;
}


void saveEnvironmentScreenshot(const std::string &_comment) // parameter is optional
{
    std::string str = convertToString(gEnvironmentScreenshotIndex);

    while (str.length() < 6)
    {
        str = "0" + str;
    }

    saveImage(gEnvironmentImage, "screenshot_environment", str + "_" + _comment);

    gEnvironmentScreenshotIndex++;
}

void saveFootprintScreenshot(const std::string &_comment) // parameter is optional
{
    std::string str = convertToString(gFootprintScreenshotIndex);

    while (str.length() < 6)
    {
        str = "0" + str;
    }

    saveImage(gFootprintImage, "screenshot_footprint", str + "_" + _comment);

    gFootprintScreenshotIndex++;
}


bool initSDL(Uint32 flags) // parameter is optional (default: SDL_HWSURFACE | SDL_DOUBLEBUF)
{
    
    if ( gBatchMode )
    {
            gDisplayMode = 2;
    }
	
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        return false;
    }

    if ( !gBatchMode )
    {
        gArenaWindow = SDL_CreateWindow("Roborobo",
                                     //SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                     gDisplayScreenWidth, gDisplayScreenHeight,
                                     flags);
    }

    gArena = SDL_CreateRGBSurface(
            0, // flags (unused)
            gArenaWidth,
            gArenaHeight,
            32,
            0x00FF0000,
            0x0000FF00,
            0x000000FF,
            0xFF000000);

    if (gArena == nullptr) // error?
    {
        std::cerr << "[CRITICAL] Failed to create screen surface (gArena). Stop.\n";
        return false;
    }

    gSnapshot = SDL_CreateRGBSurface(
            0, // flags (unused)
            gArenaWidth,
            gArenaHeight,
            32,
            0x00FF0000,
            0x0000FF00,
            0x000000FF,
            0xFF000000);

    if (gArena == nullptr) // error?
    {
        std::cerr << "[CRITICAL] Failed to create snapshot surface (gSnapshot). Stop.\n";
        return false;
    }

    if (!gBatchMode)
    {
        gArenaRenderer = SDL_CreateRenderer(gArenaWindow, -1, SDL_RENDERER_ACCELERATED);

        gArenaTexture = SDL_CreateTexture(gArenaRenderer,
                                           SDL_PIXELFORMAT_ARGB8888,
                                           SDL_TEXTUREACCESS_STREAMING,
                                           gArenaWidth, gArenaHeight);
    }

    return true;
}

void apply_surface( int _x, int _y, SDL_Surface* source, SDL_Surface* destination , SDL_Rect* clip ) // last argument is optional (cf. function header)
{
    // get offsets and blit
    SDL_Rect offset;
    offset.x = _x;
    offset.y = _y;
    SDL_BlitSurface( source, clip, destination, &offset );
}

// same as previous, but assume periodic boundary conditions (ie. toroidal world). Used to display robots, objects and landmarks. benchmarking 2021-04-24: same performance as previous function (using BlitSurface)
void apply_surface_pbc( int _x, int _y, SDL_Surface* source, SDL_Surface* destination , SDL_Rect* clip ) // last argument is optional (cf. function header)
{
    for (int x = 0; x != source->w; x++)
    {
        for (int y = 0; y != source->h; y++) {
            Uint32 pixel = getPixel32_pbc(source, x, y);


            if (pixel != SDL_MapRGBA(destination->format, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE)) {
                //Uint32 color = SDL_MapRGBA(destination->format, ((pixel & 0xFF0000) >> 16), ((pixel & 0xFF00) >> 8), (pixel & 0xFF), SDL_ALPHA_OPAQUE);  // loaded images follow SDL_PIXELFORMAT_ARGB8888
                Uint32 r = (pixel & 0xFF0000) >> 16;
                Uint32 g = (pixel & 0xFF00) >> 8;
                Uint32 b = (pixel & 0xFF);
                Uint32 color = SDL_MapRGBA(destination->format, r, g, b, SDL_ALPHA_OPAQUE);
                putPixel32_pbc(destination, _x + x, _y + y, color);
            }
        }
    }
}

void register_surface(int _x, int _y, SDL_Surface *source, SDL_Surface *destination,
                      int _id) // last argument is optional (cf. function header)
{
    for (int x = 0; x != source->w; x++)
    {
        for (int y = 0; y != source->h; y++)
        {
            Uint32 pixel = getPixel32(source, x, y);
            if (pixel != SDL_MapRGBA(destination->format, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE))
                //putPixel32( destination, __x+x, __y+y, __id );
                putPixel32(destination, _x + x, _y + y,
                           SDL_MapRGBA(destination->format, ((_id & 0xFF0000) >> 16), ((_id & 0xFF00) >> 8),
                                       (_id & 0xFF), SDL_ALPHA_OPAQUE));
        }
    }
}

void clean_surface(int _x, int _y, SDL_Surface *source,
                   SDL_Surface *destination) // last argument is optional (cf. function header)
{

    for (int x = 0; x != source->w; x++)
    {
        for (int y = 0; y != source->h; y++)
        {
            Uint32 pixel = getPixel32(source, x, y);
            if (pixel != SDL_MapRGBA(destination->format, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE))
                putPixel32(destination, _x + x, _y + y,
                           SDL_MapRGBA(destination->format, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE));
        }
    }
}

// used to register a robot into the environment (used since 2012-6-6)
void register_robotMask(int _x, int _y, SDL_Surface *destination,
                        int _id) // last argument is mandatory to track objects (in particular: agents)
{
    for (int i = 0; (size_t) i != gRobotMaskData.size(); i++)
    {
        int x = _x + gRobotMaskData[i][0];
        int y = _y + gRobotMaskData[i][1];
        putPixel32_pbc(destination, x, y, // 2021-04-23
                   SDL_MapRGBA(destination->format, ((_id & 0xFF0000) >> 16), ((_id & 0xFF00) >> 8), (_id & 0xFF),
                               SDL_ALPHA_OPAQUE));
    }
}

// used to unregister a robot from the environment (used since 2012-6-6)
void clean_robotMask(int _x, int _y, SDL_Surface *destination) // last argument is optional (cf. function header)
{
    //std::cout << "gRobotMaskData.size() => " << gRobotMaskData.size() << std::endl;

    for (unsigned int i = 0; i != gRobotMaskData.size(); i++)
    {
        int x = _x + gRobotMaskData[i][0];
        int y = _y + gRobotMaskData[i][1];

        //std::cout << "coordinates: " << x << " , " << y << std::endl;

        putPixel32_pbc(destination, x, y, SDL_MapRGBA(destination->format, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE));
    }
}


/* **************** */
/* * SIMULATOR WINDOW * */
/* **************** */



void toggle_fullscreen()
{
	std::cout << "[critical] Fullscreen mode is not implemented." << std::endl;

	/*
	clean_up();

	gFullScreenMode= !gFullScreenMode;
	
	if( initSDL(SDL_HWSURFACE | SDL_DOUBLEBUF | (gFullScreenMode?SDL_FULLSCREEN:0) ) == false )
    {
		std::cerr << "fullscreen error 1 (toggling fullscreen) \n";
		exit(-2);
	}
    
    if( gWorld->loadFiles() == false ) // note: if this block is removed, computer may hang. + gWorld is not in the scope
    {
		std::cerr << "fullscreeen error 2 (re-loading files) \n";
		exit(-2);
	}
 
	//if (SDL_WM_ToggleFullScreen(gArena) == 0)
	*/
}


SDL_Surface *load_image(const std::string &filename)
{
    SDL_Surface *loadedImage = nullptr;
    SDL_Surface *optimizedImage = nullptr;

    //loadedImage = IMG_Load( filename.c_str() );

    loadedImage = SDL_LoadBMP(filename.c_str());

    if (loadedImage != nullptr)
    {
        //If the image was successfully loaded, then convert color scheme to match 32-bits-ARGB (if needed)

        if (loadedImage->format->format == SDL_PIXELFORMAT_ARGB8888)
            return loadedImage;
        else
        {
            std::cout << "[INFO] file \"" << filename << "\" not in 32-bits-ARGB format. Converting." << std::endl;

            optimizedImage = SDL_ConvertSurfaceFormat(loadedImage, SDL_PIXELFORMAT_ARGB8888,
                                                      0); // SDL_PIXELFORMAT_ARGB8888
            SDL_FreeSurface(loadedImage);

            return optimizedImage;
        }
    
    }
    else
    {
        std::cerr << "[CRITICAL] cannot load image from file \"" << filename << "\". EXITING.";
        exit(-1);
    }

    return nullptr;
}

// draw a line from (x1,y1) to (x2,y2)
// algorithm: Bresenham
// adapted from: http://www.roguebasin.com/index.php?title=Bresenham%27s_Line_Algorithm

void drawLine(SDL_Surface * image,
               int x1,
               int y1,
               int const x2,
               int const y2,
               uint8_t r, uint8_t g, uint8_t b )
{
    uint32_t color = SDL_MapRGBA( image->format, r, g, b, SDL_ALPHA_OPAQUE );
    
    int delta_x(x2 - x1);
    // if x1 == x2, then it does not matter what we set here
    signed char const ix((delta_x > 0) - (delta_x < 0));
    delta_x = std::abs(delta_x) << 1;
    
    int delta_y(y2 - y1);
    // if y1 == y2, then it does not matter what we set here
    signed char const iy((delta_y > 0) - (delta_y < 0));
    delta_y = std::abs(delta_y) << 1;
    
    putPixel32_pbc( image, x1, y1 , color );
    
    if (delta_x >= delta_y)
    {
        // error may go below zero
        int error(delta_y - (delta_x >> 1));
        
        while (x1 != x2)
        {
            if ((error >= 0) && (error || (ix > 0)))
            {
                error -= delta_x;
                y1 += iy;
            }
            // else do nothing
            
            error += delta_y;
            x1 += ix;
            
            putPixel32_pbc( image, x1, y1 , color );
        }
    }
    else
    {
        // error may go below zero
        int error(delta_x - (delta_y >> 1));
        
        while (y1 != y2)
        {
            if ((error >= 0) && (error || (iy > 0)))
            {
                error -= delta_y;
                x1 += ix;
            }
            // else do nothing
            
            error += delta_x;
            y1 += iy;
            
            putPixel32_pbc( image, x1, y1 , color );
        }
    }
}

// cast a line from (x1,y1) to (x2,y2), without tracing it, and stopping whenever a non-blank pixel is met. Returns: updated x2 and y2 values (passed as pointers), and collision (true|false).
// algorithm: Bresenham
// adapted from: http://www.roguebasin.com/index.php?title=Bresenham%27s_Line_Algorithm

bool castLine(SDL_Surface * image,
              int x1,
              int y1,
              int *x2pt,
              int *y2pt,
              int maxLength,
              int ignoreValue)
{
    int x2 = *x2pt;
    int y2 = *y2pt;

    uint32_t colorDefault = SDL_MapRGBA( image->format, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE );
    uint32_t colorIgnore = colorDefault;
    if ( ignoreValue != -1 )
        colorIgnore = SDL_MapRGBA(image->format, ((ignoreValue & 0xFF0000) >> 16), ((ignoreValue & 0xFF00) >> 8), (ignoreValue & 0xFF),
    SDL_ALPHA_OPAQUE);

    int delta_x(x2 - x1);
    // if x1 == x2, then it does not matter what we set here
    signed char const ix((delta_x > 0) - (delta_x < 0));
    delta_x = std::abs(delta_x) << 1;

    int delta_y(y2 - y1);
    // if y1 == y2, then it does not matter what we set here
    signed char const iy((delta_y > 0) - (delta_y < 0));
    delta_y = std::abs(delta_y) << 1;

    int dist = 0; // distance to obstacle (or to max_length)

    if ( getPixel32_pbc( image, x1, y1 ) != colorDefault && getPixel32_pbc( image, x1, y1 ) != colorIgnore)
    {
        *x2pt = x1;
        *y2pt = y1;
        return true;
    }

    if (delta_x >= delta_y)
    {
        // error may go below zero
        int error(delta_y - (delta_x >> 1));

        while (x1 != x2)
        {
            if ((error >= 0) && (error || (ix > 0)))
            {
                error -= delta_x;
                y1 += iy;
            }
            // else do nothing

            error += delta_y;
            x1 += ix;

            dist++;

            if ( getPixel32_pbc( image, x1, y1 ) != colorDefault && getPixel32_pbc( image, x1, y1 ) != colorIgnore )
            {
                *x2pt = x1;
                *y2pt = y1;
                return true;
            }

        }
    }
    else
    {
        // error may go below zero
        int error(delta_x - (delta_y >> 1));

        while (y1 != y2)
        {
            if ((error >= 0) && (error || (iy > 0)))
            {
                error -= delta_y;
                x1 += ix;
            }
            // else do nothing

            error += delta_x;
            y1 += iy;

            dist++;

            if ( getPixel32_pbc( image, x1, y1 ) != colorDefault && getPixel32_pbc( image, x1, y1 ) != colorIgnore )
            {
                *x2pt = x1;
                *y2pt = y1;
                return true;
            }
        }
    }

    return false; // no collision
}
