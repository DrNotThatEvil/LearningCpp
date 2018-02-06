#include "BarnHutMulti.h"
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


        wilvin::VPoint *vpoint
            = new wilvin::VPoint( 200.0f, 500.0f, 200.0f, 500.0f );
        wilvin::VPoint *vpoint2
            = new wilvin::VPoint( 400.0f, 500.0f, 400.0f, 500.0f );

        std::vector<wilvin::VPoint *> points;
        points.push_back( vpoint );
        points.push_back( vpoint2 );

        wilvin::BarnHutMulti barnmulti( 0, 0, wilvin::Screen::SCREEN_WIDTH,
                                        wilvin::Screen::SCREEN_HEIGHT, 1,
                                        points );

        if ( screen.init() )
        {
            // Do normal stuff here.

            screen.clear();

            // wilvin::VPoint vpoint( 200.0f, 500.0f, 200.0f, 500.0f );

            barnmulti.startSolve();
            for ( int i = 0; i < 10; i++ )
            {
                screen.clear();

                vpoint->render( screen );
                vpoint2->render( screen );
                barnmulti.render( &screen );

                screen.update();
                std::cout << "Learning cpp" << std::endl;
            }


            SDL_Delay( 2000 );
        }

        std::cout << "Quiting..." << std::endl;

        delete vpoint;
        delete vpoint2;
        // Screen init failed we need to let it go screen out of scope
        // And call SDL_Quit.
    }

    SDL_Quit();
    return 0;
}
