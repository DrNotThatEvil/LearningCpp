#include "BarnHutMulti.h"

namespace caveofprogramming
{
    BarnHutMulti::BarnHutMulti( const int x,
                                const int y,
                                const int width,
                                const int height,
                                const int numThreads,
                                const std::vector<VerletPoint *> contained )
    : m_x( x )
    , m_y( y )
    , m_width( width )
    , m_height( height )
    , m_numThreads( numThreads )
    , m_contained( contained )
    {
        m_avilableThreads = m_numThreads;
        m_drawed = false;
        m_done = false;
        m_running = false;
        m_wRemaining = 4;
    }

    BarnHutMulti::~BarnHutMulti()
    {
    }

    int BarnHutMulti::startThread( void *data )
    {
        BarnHutMulti *self = static_cast<BarnHutMulti *>( data );
        return self->thread();
    }

    int BarnHutMulti::thread()
    {
        // First we check if this square has more then one VerletPoint if so we continue.
        // If so we don't really need to continue and need to notify the parent thread we are done.

        if ( m_contained.size() <= 1 )
        {
            // We only contain one point we are done!
            m_done = true;
            return 1;
        }

        m_running = true;

        // This is thread ran either on it's own or by using startThread.
        // The work here does either the solving or waiting on the threads below it to have solved.

        // We can create child threads. We need to watch for them to solve stuff.
        // As soon as a thread finishes and there is still work we start a new thread with this
        // work.
        m_children = (BarnHutMulti **)malloc( 4 * sizeof( BarnHutMulti * ) );

        int dividedThreads = m_numThreads / 4;
        // get the amount of threads to assign to the children

        int sX = m_x;
        int sY = m_y;

        for ( int i = 0; i < 2; i++ )
        {
            for ( int j = 0; j < 2; j++ )
            {
                std::vector<VerletPoint *> rect_contained
                    = this->getContained( sX, sY, m_width / 2, m_height / 2, m_contained );

                m_children[( ( i * 2 ) + j )] = new BarnHutMulti( sX, sY, m_width / 2, m_height / 2,
                                                                  dividedThreads, rect_contained );

                sX += ( m_width / 2 );
            }

            sX = m_x;
            sY += ( m_height / 2 );
        }

        if ( m_numThreads > 1 )
        {
            while ( !m_done )
            {
                // Loop through all the children and get their state
                for ( int i = 0; i < 4; i++ )
                {
                    // There is work remaining and the available threads is greater then 0
                    // start the child that has not started yet and decrease wRemaining and decrease
                    // the Avaliable threads
                    if ( !m_children[i]->isStarted() && m_wRemaining > 0 && m_avilableThreads > 0 )
                    {
                        // Start that worker
                        SDL_Thread *workerThread;
                        workerThread = SDL_CreateThread(
                            BarnHutMulti::startThread, "Child Sub Thread", (void *)m_children[i] );
                        m_pThreads.push_back( workerThread );

                        m_avilableThreads--;
                        m_wRemaining--;
                    }

                    if ( m_children[i]->isDone() )
                    {
                        // Child is done increase the available threads
                        m_avilableThreads++;
                    }
                }

                if ( m_wRemaining == 0 )
                {
                    // There is no work remaining! we are done!
                    m_done = true;
                    return 1;
                }
            }
        }
        else
        {
            // We can't create child threads.
            // So can only start to solve our squares.
            for ( int i = 0; i < 4; i++ )
            {
                m_children[i]->thread();
            }

            m_done = true;
        }
        return 1;
    }

    void BarnHutMulti::setParentThread( BarnHutMulti *parent )
    {
        m_parent = parent;
    }

    bool BarnHutMulti::isDone()
    {
        return m_done;
    }

    bool BarnHutMulti::isStarted()
    {
        return m_running;
    }

    std::vector<VerletPoint *> BarnHutMulti::getContained( int x,
                                                           int y,
                                                           int width,
                                                           int height,
                                                           std::vector<VerletPoint *> possible )
    {
        std::vector<VerletPoint *> contained;
        for ( int i = 0; i < possible.size(); i++ )
        {
            VerletPoint *point = possible[i];
            if ( point->getX() >= x && point->getX() < ( x + width ) && point->getY() >= y
                 && point->getY() < ( y + height ) )
            {
                contained.push_back( point );
            }
        }

        return contained;
    }

    void BarnHutMulti::startSolve()
    {
        // SDL_Thread *thread_1;
        // thread_1 = SDL_CreateThread( BarnHutMulti::startWork, (void *)this );
        m_avilableThreads = m_numThreads;
        m_done = false;
        m_running = false;
        m_wRemaining = 4;
        this->thread();
    }

    void BarnHutMulti::makeThreadAvialable()
    {
    }

    void BarnHutMulti::render( Screen *screen )
    {
        if ( m_done )
        {
            if ( m_contained.size() > 1 )
            {
                for ( int i = 0; i < 4; i++ )
                {
                    m_children[i]->render( screen );
                }
            }

            for ( int y = 0; y < m_height; y++ )
            {
                for ( int x = 0; x < ( m_width - 1 ); x++ )
                {
                    int red = 0xff;
                    int green = 0xff;

                    if ( y == 0 || y == ( m_height - 1 ) )
                    {
                        screen->setPixel( m_x + x, m_y + y, red, green, 0xff, 0xff );
                    }

                    screen->setPixel( m_x, m_y + y, red, green, 0xff, 0xff );
                    screen->setPixel( m_x + ( m_width - 1 ), m_y + y, red, green, 0xff, 0xff );
                }
            }
        }
    }
}
