#include "particle.h"
#include "screen.h"
#include "svector.h"
#include <math.h>
#include <stdlib.h>

namespace caveofprogramming
{
    Particle::Particle()
    {
        float xcalc = ( ( ( 2.0f * rand() ) / RAND_MAX ) )
                      * ( caveofprogramming::Screen::SCREEN_WIDTH / 2 );
        float ycalc = ( ( ( 2.0f * rand() ) / RAND_MAX ) )
                      * ( caveofprogramming::Screen::SCREEN_HEIGHT / 2 );


        m_pos = new SVector( xcalc, ycalc );
        m_vel = new SVector( 0.0f, 0.0f );
        m_disabled = false;
        m_mass = 1.0f;
        m_radius = 5.0f;
    }

    Particle::~Particle()
    {
    }

    float Particle::angleTo( const Particle *p2 )
    {
        return atan2( p2->m_pos->getY() - this->m_pos->getY(),
                      p2->m_pos->getX() - this->m_pos->getX() );
    }

    float Particle::distanceTo( const Particle *p2 )
    {
        float distX = p2->m_pos->getX() - this->m_pos->getX();
        float distY = p2->m_pos->getY() - this->m_pos->getY();

        return sqrt( distX * distX + distY * distY );
    }

    void Particle::gravitateTo( const Particle *p2 )
    {
        SVector *grav = new SVector( 0.0f, 0.0f );
        float dist = this->distanceTo( p2 );

        grav->setLength( p2->m_mass / ( dist * dist ) );
        grav->setAngle( this->angleTo( p2 ) );

        *this->m_vel += *grav;
        delete grav;
    }

    void Particle::setMass( float mass )
    {
        m_mass = mass;
    }

    float Particle::getMass()
    {
        return m_mass;
    }

    bool Particle::checkColl( Particle *colObj )
    {
        if ( this == colObj ) return false;
        SVector n = *colObj->m_pos - *m_pos;
        float dist = n.getLength();
        if ( dist >= m_radius + colObj->m_radius ) return false;
        n.normalize();
        coll.normal = n;
        coll.depth = m_radius + colObj->m_radius - dist;
        coll.bod = colObj;
        return true;
    }

    bool Particle::checkColl( Particle *colObj, const float dist )
    {
        SVector n = *colObj->m_pos - *m_pos;
        if ( dist >= m_radius + colObj->m_radius ) return false;
        n.normalize( dist );
        coll.normal = n;
        coll.depth = m_radius + colObj->m_radius - dist;
        coll.bod = colObj;
        return true;
    }

    void Particle::processColl()
    {
        SVector movement = coll.normal * coll.depth * .5f;
    }

    void Particle::update()
    {
        if ( m_disabled ) return;

        SVector newPos = *m_pos + *m_vel;
        if ( ( newPos.getX() + m_mass ) < 0 )
        {
            m_pos->setX( caveofprogramming::Screen::SCREEN_WIDTH - m_mass );
        }

        if ( ( newPos.getX() - m_mass ) > caveofprogramming::Screen::SCREEN_WIDTH )
        {
            m_pos->setX( 0 + m_mass );
        }

        if ( ( newPos.getY() + m_mass ) < 0 )
        {
            m_pos->setY( caveofprogramming::Screen::SCREEN_HEIGHT - m_mass );
        }

        if ( ( newPos.getY() - m_mass ) > caveofprogramming::Screen::SCREEN_HEIGHT )
        {
            m_pos->setY( 0 + m_mass );
        }

        if ( m_vel->getLength() > 100 )
        {
            m_vel->setLength( 100 );
        }

        if ( m_vel->getLength() < -100 )
        {
            m_vel->setLength( -100 );
        }

        *m_pos += *m_vel;
    }
}
