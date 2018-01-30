#include "screen.h"
#include "swarm.h"
#include <algorithm>
#include <limits>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

namespace caveofprogramming
{
    Swarm::Swarm()
    {
        m_pParticles = new VerletPoint[NPARTICLES];
        m_barnhutcount = 0;
        int x = 0;
        int y = 0;

        for ( int i = 0; i < Swarm::NPARTICLES; i++ )
        {
            float x = static_cast<float>( rand() ) / static_cast<float>( RAND_MAX ) - 0.5;
            float y = static_cast<float>( rand() ) / static_cast<float>( RAND_MAX ) - 0.5;

            //            printf( "diffx: %f\n", diffx );
            //            printf( "diffy: %f\n", diffy );

            m_pParticles[i].setX( ( Screen::SCREEN_WIDTH / 2 )
                                  + ( x * ( Screen::PSCREEN_WIDTH ) ) );
            m_pParticles[i].setY( ( Screen::SCREEN_HEIGHT / 2 )
                                  + ( y * ( Screen::PSCREEN_HEIGHT ) ) );

            /*
            m_pParticles[i].setX( ( Screen::SCREEN_WIDTH / 2 ) - ( Screen::PSCREEN_WIDTH / 2 )
                                  + x );
            m_pParticles[i].setY( ( Screen::SCREEN_HEIGHT / 2 ) - ( Screen::PSCREEN_HEIGHT / 2 )
                                  + y );

            x += 30;

            if ( x > ( 30 * 30 ) )
            {
                x = 0;
                y += 30;
            }

            */
            m_pParticles[i].setOldX( m_pParticles[i].getX() );
            m_pParticles[i].setOldY( m_pParticles[i].getY() );
        }


        for ( int x = 0; x < 5; x++ )
        {
            for ( int i = 0; i < Swarm::NPARTICLES; i++ )
            {
                for ( int j = 0; j < Swarm::NPARTICLES; j++ )
                {
                    if ( i == j ) continue;
                    m_pParticles[i].colideNonMove( m_pParticles[j] );
                }
            }
        }

        std::vector<VerletPoint *> points;
        for ( int i = 0; i < Swarm::NPARTICLES; i++ )
        {
            points.push_back( &m_pParticles[i] );
        }

        m_barnhutmulti
            = new BarnHutMulti( 0, 0, Screen::SCREEN_WIDTH, Screen::SCREEN_HEIGHT, 3, points );
        // m_barnhut->solve();
    }

    Swarm::~Swarm()
    {
        delete[] m_pParticles;
    }

    void Swarm::update()
    {
        m_barnhutmulti->startSolve();
        printf( "Started solve\n" );

        for ( int i = 0; i < Swarm::NPARTICLES; i++ )
        {
            m_pParticles[i].update();
            printf( " hash = %d\n", m_pParticles[i].hash() );
        }

        for ( int i = 0; i < Swarm::NPARTICLES; i++ )
        {
            // m_barnhut->findPointForce( m_pParticles[i] );
        }

        for ( int x = 0; x < 3; x++ )
        {
            for ( int i = 0; i < Swarm::NPARTICLES; i++ )
            {
                for ( int j = 0; j < Swarm::NPARTICLES; j++ )
                {
                    if ( i == j ) continue;
                    m_pParticles[i].colide( m_pParticles[j] );
                }
            }
        }
    }

    void Swarm::render( Screen *screen )
    {
        // m_barnhutmulti->render( screen );

        for ( int i = 0; i < caveofprogramming::Swarm::NPARTICLES; i++ )
        {
            VerletPoint verletPoint = m_pParticles[i];
            Uint8 alpha = 0xFF;

            // printf( "draw size: %f\n", particle.m_mass );

            for ( float angle = 0.0; angle < 360; angle++ )
            {
                int x = verletPoint.getX() - verletPoint.getRadius() * cos( angle );
                int y = verletPoint.getY() - verletPoint.getRadius() * sin( angle );
                screen->setPixel( x, y, 0xFF, 0xff, 0xff, alpha );
            }

            // printf( "%f \n", verletPoint.getX() );
            screen->setPixel( verletPoint.getX(), verletPoint.getY(), 0xFF, 0xff, 0xff, alpha );
        }
    }

    const VerletPoint *const Swarm::getParticles()
    {
        return m_pParticles;
    }
}
