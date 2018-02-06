#include "BarnHutMulti.h"
#include <iostream>

namespace wilvin
{
    BarnHutMulti::BarnHutMulti( const int x,
                                const int y,
                                const int width,
                                const int height,
                                const int numThreads,
                                const std::vector<VPoint *> contained )
    : m_x( x )
    , m_y( y )
    , m_width( width )
    , m_height( height )
    , m_numThreads( numThreads )
    , m_contained( contained )
    {
        m_avilableThreads = m_numThreads;
        m_done = false;
        m_running = false;
        m_wRemaining = 4;
    }

    BarnHutMulti::~BarnHutMulti()
    {
        if ( m_children.size() == 0 ) return;

        for ( unsigned int i = 0; i < m_children.size(); i++ )
        {
            delete m_children.at( i ).get();
        }
    }

    int BarnHutMulti::startThread( void *data )
    {
        BarnHutMulti *self = static_cast<BarnHutMulti *>( data );
        return self->thread();
    }

    std::vector<VPoint *> BarnHutMulti::getContained(
        int x, int y, int width, int height, std::vector<VPoint *> possible )
    {
        std::vector<VPoint *> contained;
        for ( unsigned int i = 0; i < possible.size(); i++ )
        {
            VPoint *point = possible[i];
            if ( point->x() >= x && point->x() < ( x + width )
                 && point->y() >= y && point->y() < ( y + height ) )
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
        if ( m_running ) return;

        m_avilableThreads = m_numThreads;
        m_done = false;
        m_wRemaining = 4;
        this->thread();
    }

    int BarnHutMulti::thread()
    {
        // First we check if this square has more then one VPoint if so we
        // continue. If so we don't really need to continue and need to notify
        // the parent thread we are done.

        if ( m_contained.size() <= 1 || m_width <= 20 || m_height <= 20 )
        {
            // We only contain one point we are done!
            m_done = true;
            return 1;
        }

        m_running = true;

        // This is thread ran either on it's own or by using startThread.
        // The work here does either the solving or waiting on the threads below
        // it to have solved.

        // We can create child threads. We need to watch for them to solve
        // stuff. As soon as a thread finishes and there is still work we start
        // a new thread with this work.

        int dividedThreads = m_numThreads / 4;
        // get the amount of threads to assign to the children

        int sX = m_x;
        int sY = m_y;

        for ( int i = 0; i < 2; i++ )
        {
            for ( int j = 0; j < 2; j++ )
            {
                std::vector<VPoint *> rect_contained
                    = BarnHutMulti::getContained( sX, sY, m_width / 2,
                                                  m_height / 2, m_contained );

                std::unique_ptr<BarnHutMulti> child
                    = std::make_unique<BarnHutMulti>(
                        sX, sY, m_width / 2, m_height / 2, dividedThreads,
                        rect_contained );
                ( *child ).setParentThread(
                    std::shared_ptr<BarnHutMulti>( this ) );
                m_children.push_back( std::move( child ) );

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
                    // There is work remaining and the available threads is
                    // greater then 0 start the child that has not started yet
                    // and decrease wRemaining and decrease the Avaliable
                    // threads
                    if ( !m_children.at( i ).get()->isStarted()
                         && m_wRemaining > 0 && m_avilableThreads > 0 )
                    {
                        // Start that worker
                        SDL_Thread *workerThread;
                        workerThread = SDL_CreateThread(
                            BarnHutMulti::startThread, "Child Sub Thread",
                            (void *)m_children.at( i ).get() );
                        m_pThreads.push_back( workerThread );

                        m_avilableThreads--;
                        m_wRemaining--;
                    }

                    if ( m_children.at( i ).get()->isDone() )
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
                m_children.at( i ).get()->thread();
            }

            m_done = true;
            m_running = false;
        }
        return 1;
    }

    void BarnHutMulti::setParentThread( std::shared_ptr<BarnHutMulti> parent )
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
                        screen->setPixel( m_x + x, m_y + y, red, green, 0xff,
                                          0xff );
                    }

                    screen->setPixel( m_x, m_y + y, red, green, 0xff, 0xff );
                    screen->setPixel( m_x + ( m_width - 1 ), m_y + y, red,
                                      green, 0xff, 0xff );
                }
            }
        }
    }
}
