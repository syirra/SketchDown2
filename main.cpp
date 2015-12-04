#include <SDL/SDL.h>
#include <iostream>

#ifdef USE_GLEE
# include <GL/GLee.h>
#else
# include <GL/glew.h>
#endif

SDL_Surface * init(unsigned width, unsigned height, unsigned color)
{
    SDL_Surface *screen;
    
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        std::cout << "SDL ERROR: Video initialization: " << SDL_GetError() << std::endl;
    else
    {
        SDL_WM_SetCaption("SketchDown", NULL);
        screen = SDL_SetVideoMode(width, height, color, SDL_OPENGL);
        if(screen == NULL)
            std::cout << "SDL ERROR: Window creation: " << SDL_GetError() << std::endl;
        else
        {
            SDL_FillRect(screen, NULL, 0x808080);
            SDL_Flip(screen);
            return screen;
        }
    }
}
 

void mainLoop()
{
    bool active = true; // Window is not minimized

    for(;;)
    {
        SDL_Event event;

        //if(SDL_WaitEvent(&event) == 0) throw SDL_Exception();

        bool redraw = false; // Screen needs redraw
        
        do // Handle events
        {
            switch(event.type)
            {
                case SDL_ACTIVEEVENT : // Stop redraw when minimized
                    if(event.active.state == SDL_APPACTIVE)
                        active = event.active.gain;
                    break;
                case SDL_KEYDOWN :
                    std::cout << "KEY DOWN" << std::endl;
                    break;
                case SDL_KEYUP :
                    std::cout << "KEY UP" << std::endl;
                    break;
                case SDL_MOUSEMOTION :
                    //std::cout << "MOUSE MOTION " << event.motion.x << " + " << event.motion.y << " + " << event.motion.xrel << " + " << event.motion.yrel << " + " << event.motion.state << std::endl;
                    break;
                case SDL_MOUSEBUTTONDOWN :
                    //onMouseDown(event.button.button, event.button.x, event.button.y);
                    break;
                case SDL_MOUSEBUTTONUP :
                    std::cout << "DRAW COMPLETE" << std::endl;
                    break;
                case SDL_QUIT :
                    return; // End main loop
                case SDL_VIDEORESIZE :
                    // onWindowResized(event.resize.w, event.resize.h);
                    break;
                case SDL_VIDEOEXPOSE :
                    redraw = true;
                    break;
                default :
                    break;
            }
        } while(SDL_PollEvent(&event) == 1);

        // Optionally redraw window
        //if(active && redraw) onWindowRedraw();
    }
}    

int main(int argc, char *argv[])
{  
    init(640, 480, 32);
    
    SDL_GL_SetAttribute ( SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute ( SDL_GL_DEPTH_SIZE, 16 );
    
    //mainLoop();
    while(1)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable( GL_TEXTURE_2D );
        glClearColor( 1.0f, 0.0f, 0.0f, 1.0f );
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);


        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_LINES);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.75, 0.75, 0.0);
        glEnd();
    
        SDL_GL_SwapBuffers(); 
    }
    
    atexit(SDL_Quit);
    
    return 0;
    
}
