#include "SDL.h"
#include "screen.h"
#include "swarm.h"
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main( void )
{
    srand( time( NULL ) );
    caveofprogramming::Screen screen;

    if ( screen.init() == false )
    {
        printf( "Error initalizing SDL.\n" );
    }

    caveofprogramming::Swarm swarm;

    while ( true )
    {
        int elapsed = SDL_GetTicks();

        screen.clear();
        swarm.update();

        /*
        unsigned char red = ( 1 + sin( elapsed * 0.00015 ) ) * 128;
        unsigned char green = ( 1 + sin( elapsed * 0.00023 ) ) * 128;
        unsigned char blue = ( 1 + sin( elapsed * 0.00031 ) ) * 128;
        */

        swarm.render( &screen );
        screen.update();

        if ( screen.processEvents() == false )
        {
            break;
        }
    }

    screen.close();

    return 0;
}
