#include "BarnHut.h"
#include "screen.h"
#include <algorithm>

namespace caveofprogramming
{

    BarnHut::BarnHut( VerletPoint *particles, int psize, int width, int height )
    : m_screenW( width )
    , m_screenH( height )
    , m_pParticles( particles )
    , m_totalP( psize )
    {
        m_drawRects = nullptr;
        m_maxDepth = 0;
    }

    BarnHut::~BarnHut()
    {
    }

    void BarnHut::solve()
    {
        std::vector<Rectangle> rects;
        std::vector<VerletPoint *> *particles = new std::vector<VerletPoint *>;
        Rectangle rect;
        rect.w = m_screenW;
        rect.h = m_screenH;
        rect.x = 0;
        rect.y = 0;
        rect.psize = m_totalP;
        rect.p_parent = nullptr;
        rect.depth = 0;

        float masstimesposx = 0.0f;
        float masstimesposy = 0.0f;
        float totalmass = 0.0f;
        for ( int i = 0; i < m_totalP; i++ )
        {
            masstimesposx += m_pParticles[i].getMass() * m_pParticles[i].getX();
            masstimesposy += m_pParticles[i].getMass() * m_pParticles[i].getY();
            totalmass += m_pParticles[i].getMass();
            particles->push_back( &m_pParticles[i] );
        }

        rect.particles = particles;
        rect.p_centermass = new SVector( masstimesposx / totalmass, masstimesposy / totalmass );
        rect.mass = totalmass;

        rects.push_back( rect );
        this->solve( rects );
    }

    bool isparticleinrect( VerletPoint &p, Rectangle r )
    {
        return ( p.getX() > r.x && p.getX() < ( r.x + r.w ) && p.getY() > r.y
                 && p.getY() < ( r.y + r.h ) );
    }

    void BarnHut::solve( std::vector<Rectangle> rects )
    {
        std::vector<Rectangle> *new_rects = new std::vector<Rectangle>;
        bool run_again = false;

        for ( int i = 0; i < rects.size(); i++ )
        {
            if ( rects[i].psize > 1 && !rects[i].done )
            {
                rects[i].done = true;
                new_rects->push_back( rects[i] );

                run_again = true;
                // amount of particles in this Rectangle > 1
                // split this rect in multiple rects
                int xoffset = 0;
                int yoffset = 0;
                for ( int j = 0; j < 4; j++ )
                {
                    // create one of the 4 rects
                    std::vector<VerletPoint *> *particles = new std::vector<VerletPoint *>;

                    Rectangle rect;

                    rect.w = ( rects[i].w / 2 );
                    rect.h = ( rects[i].h / 2 );
                    rect.x = rects[i].x + xoffset;
                    rect.y = rects[i].y + yoffset;
                    rect.p_parent = &rects[i];
                    rect.depth = ( rects[i].depth + 1 );

                    m_maxDepth = std::max( rect.depth, m_maxDepth );

                    xoffset += ( rects[i].w / 2 );
                    if ( xoffset >= rects[i].w )
                    {
                        xoffset = 0;
                        yoffset += rects[i].h / 2;
                    }

                    // find the points in the rect.
                    int psize = 0;
                    float masstimesposx = 0.0f;
                    float masstimesposy = 0.0f;
                    float totalmass = 0.0f;
                    for ( int k = 0; k < m_totalP; k++ )
                    {
                        // put all the particles in the rect.
                        if ( isparticleinrect( m_pParticles[k], rect ) )
                        {
                            psize++;
                            masstimesposx += m_pParticles[k].getMass() * m_pParticles[k].getX();
                            masstimesposy += m_pParticles[k].getMass() * m_pParticles[k].getY();
                            totalmass += m_pParticles[k].getMass();
                            particles->push_back( &m_pParticles[k] );
                        }
                    }

                    rect.p_centermass
                        = new SVector( masstimesposx / totalmass, masstimesposy / totalmass );
                    rect.mass = totalmass;
                    rect.particles = particles;

                    // add the points in the rect to the rect.
                    rect.psize = psize;
                    new_rects->push_back( rect );
                }
            }
            else
            {
                rects[i].done = true;
                new_rects->push_back( rects[i] );
            }
        }

        m_drawRects = new_rects;

        if ( run_again )
        {
            this->solve( *new_rects );
        }
    }

    void BarnHut::findPointForce( VerletPoint &point )
    {
        Rectangle rect;
        int deepestDepth = -1;
        for ( int i = 0; i < m_drawRects->size(); i++ )
        {
            for ( int j = 0; j < m_drawRects->at( i ).particles->size(); j++ )
            {
                if ( m_drawRects->at( i ).particles->at( j ) == &point )
                {
                    if ( m_drawRects->at( i ).depth > deepestDepth )
                    {
                        deepestDepth = m_drawRects->at( i ).depth;
                        rect = m_drawRects->at( i );
                    }
                }
            }
        }

        // Calculate if node is faw away enough
        for ( int i = 0; i < m_drawRects->size(); i++ )
        {
            if ( &m_drawRects->at( i ) == &rect || m_drawRects->at( i ).mass == 0 ) continue;

            float x = point.getX() - m_drawRects->at( i ).p_centermass->getX();
            float y = point.getY() - m_drawRects->at( i ).p_centermass->getY();
            float dist = sqrt( x * x + y * y );

            if ( dist == 0 || dist != dist ) continue;


            float distanceMass = Screen::SCREEN_WIDTH / dist;
            if ( rect.p_parent != nullptr )
            {
                distanceMass = rect.p_parent->w / dist;
            }

            if ( distanceMass < 0.5 )
            {
                point.gravitateTo( m_drawRects->at( i ).p_centermass, m_drawRects->at( i ).mass );
            }
            else
            {
                for ( int j = 0; j < m_drawRects->at( i ).particles->size(); j++ )
                {
                    if ( m_drawRects->at( i ).particles->at( j ) == &point ) continue;

                    point.gravitateTo( m_drawRects->at( i ).particles->at( j ) );
                }
            }
        }
    }

    void BarnHut::render( Screen *screen )
    {
        if ( m_drawRects == nullptr ) return;


        for ( int i = 0; i < m_drawRects->size(); i++ )
        {
            int red = 255 * ( m_drawRects->at( i ).depth / (float)m_maxDepth );
            int green = 0xFF - red;

            if ( m_drawRects->at( i ).mass > 0 )
            {
                int cy = m_drawRects->at( i ).p_centermass->getY();
                int cx = m_drawRects->at( i ).p_centermass->getX();
                for ( int y = cy - 5; y < ( cy + 5 ); y++ )
                {
                    screen->setPixel( cx, y, red, green, 0, 0xff );
                }

                for ( int x = cx - 5; x < ( cx + 5 ); x++ )
                {
                    screen->setPixel( x, cy, red, green, 0, 0xff );
                }
            }


            for ( int y = 0; y < m_drawRects->at( i ).h; y++ )
            {
                if ( y < m_drawRects->at( i ).h - 1 )
                {
                    screen->setPixel( m_drawRects->at( i ).x + m_drawRects->at( i ).w,
                                      m_drawRects->at( i ).y + y, red, green, 0, 0xff );
                }
                else
                {
                    for ( int x = 0; x < m_drawRects->at( i ).w; x++ )
                    {
                        screen->setPixel( m_drawRects->at( i ).x + x, m_drawRects->at( i ).y + y,
                                          red, green, 0, 0xff );
                    }
                }
            }
        }
    }
}
