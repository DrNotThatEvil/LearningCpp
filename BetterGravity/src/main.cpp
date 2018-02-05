#include "Screen.h"
#include "VPoint.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>

int main( void )
{
    srand( time( NULL ) );

    {
        wilvin::Screen screen;

        if ( screen.init() )
        {
            // Do normal stuff here.

            screen.clear();

            // wilvin::VPoint vpoint( 200.0f, 500.0f, 200.0f, 500.0f );

            for ( int i = 0; i < 10000; i++ )
            {
                screen.clear();
                vpoint.render( screen );
                screen.update();
            }


            SDL_Delay( 2000 );
        }

        std::cout << "Quiting..." << std::endl;

        // Screen init failed we need to let it go screen out of scope
        // And call SDL_Quit.
    }

    SDL_Quit();
    return 0;
}
