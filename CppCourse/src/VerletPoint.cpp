#include "VerletPoint.h"
#include "screen.h"

namespace caveofprogramming
{
    const float VerletPoint::GRAVITY = 0.8f;
    const float VerletPoint::BOUNCE = 1.0f;
    const float VerletPoint::FRICTION = 1.0f;

    VerletPoint::VerletPoint( float x, float y, float ox, float oy )
    {
        m_pos = new SVector( x, y );
        m_oldPos = new SVector( ox, oy );
        m_radius = 5.0f;
        m_mass = 5.0f;
    }

    VerletPoint::VerletPoint()
    {
        m_pos = new SVector( 0.0f, 0.0f );
        m_oldPos = new SVector( 0.0f, 0.0f );
        m_radius = 5.0f;
        m_mass = 1.0f;
    }

    VerletPoint::~VerletPoint()
    {
    }

    void VerletPoint::update()
    {
        SVector v = ( *m_pos - *m_oldPos ) * FRICTION;

        *m_oldPos = *m_pos;
        *m_pos += v;

        if ( m_pos->getX() > Screen::SCREEN_WIDTH || m_pos->getX() < 5
             || m_pos->getY() > Screen::SCREEN_HEIGHT || m_pos->getY() < 5 )
        {
            float x = static_cast<float>( rand() ) / static_cast<float>( RAND_MAX ) - 0.5;
            float y = static_cast<float>( rand() ) / static_cast<float>( RAND_MAX ) - 0.5;

            m_pos->setX( ( Screen::SCREEN_WIDTH / 2 ) + ( x * ( Screen::PSCREEN_WIDTH ) ) );
            m_pos->setY( ( Screen::SCREEN_HEIGHT / 2 ) + ( y * ( Screen::PSCREEN_HEIGHT ) ) );
            m_oldPos->setX( m_pos->getX() );
            m_oldPos->setY( m_pos->getY() );
        }

        /*
                if ( m_pos->getX() > Screen::SCREEN_WIDTH - ( 1 + m_radius ) )
                {
                    m_pos->setX( 1 + m_radius );
                    m_oldPos->setX( m_pos->getX() - v.getX() * BOUNCE );
                }
                else if ( m_pos->getX() < ( 1 + m_radius ) )
                {
                    m_pos->setX( Screen::SCREEN_WIDTH - ( 1 + m_radius ) );
                    m_oldPos->setX( m_pos->getX() - v.getX() * BOUNCE );
                }

                if ( m_pos->getY() > Screen::SCREEN_HEIGHT - ( 1 + m_radius ) )
                {
                    m_pos->setY( 1 + m_radius );
                    m_oldPos->setY( m_pos->getY() - v.getY() * BOUNCE );
                }
                else if ( m_pos->getY() < ( 1 + m_radius ) )
                {
                    m_pos->setY( Screen::SCREEN_HEIGHT - ( 1 + m_radius ) );
                    m_oldPos->setY( m_pos->getY() - v.getY() * BOUNCE );
                }
        */
    }

    void VerletPoint::colideNonMove( VerletPoint &p2 )
    {
        float x = m_pos->getX() - p2.getX();
        float y = m_pos->getY() - p2.getY();
        float len = sqrt( x * x + y * y );
        float target = m_radius + p2.getRadius();

        if ( m_radius > 5.0f || p2.getRadius() > 5.0f ) printf( "taget = %f\n", target );

        if ( len < target )
        {
            float factor = ( len - target ) / len / 2;
            *m_pos -= SVector( x * factor, y * factor );
            *m_oldPos -= SVector( x * factor, y * factor );
            p2.setX( p2.getX() + x * factor );
            p2.setY( p2.getY() + y * factor );

            p2.setOldX( p2.getX() + x * factor );
            p2.setOldY( p2.getY() + y * factor );
        }
    }

    void VerletPoint::colide( VerletPoint &p2 )
    {
        float x = m_pos->getX() - p2.getX();
        float y = m_pos->getY() - p2.getY();
        float len = sqrt( x * x + y * y );
        float target = m_radius + p2.getRadius();

        if ( m_radius > 5.0f || p2.getRadius() > 5.0f ) printf( "taget = %f\n", target );

        if ( len < target )
        {
            float factor = ( len - target ) / len / 2;
            *m_pos -= SVector( x * factor, y * factor );

            p2.setX( p2.getX() + x * factor );
            p2.setY( p2.getY() + y * factor );
        }
    }

    void VerletPoint::gravitateTo( const SVector *target, float mass )
    {
        SVector *grav = new SVector( 0.0f, 0.0f );

        float x = m_pos->getX() - target->getX();
        float y = m_pos->getY() - target->getY();
        float dist = sqrt( x * x + y * y );

        grav->setLength( ( mass / ( dist * dist ) ) / m_mass );

        float angle = atan2( target->getY() - m_pos->getY(), target->getX() - m_pos->getX() );

        grav->setAngle( angle );
        *m_pos += *grav;

        delete grav;
    }

    void VerletPoint::gravitateTo( VerletPoint *target )
    {
        SVector *grav = new SVector( 0.0f, 0.0f );
        SVector *grav2 = new SVector( 0.0f, 0.0f );

        float x = m_pos->getX() - target->getX();
        float y = m_pos->getY() - target->getY();
        float dist = sqrt( x * x + y * y );

        grav->setLength( ( target->getMass() / ( dist * dist ) ) / m_mass );
        grav2->setLength( ( m_mass / ( dist * dist ) ) / target->getMass() );

        float angle = atan2( target->getY() - m_pos->getY(), target->getX() - m_pos->getX() );

        grav->setAngle( angle );
        grav2->setAngle( angle );

        *m_pos += *grav;
        target->setX( target->getX() - grav2->getX() );
        target->setY( target->getY() - grav2->getY() );

        delete grav;
        delete grav2;
    }

    float VerletPoint::getX() const
    {
        return m_pos->getX();
    }

    float VerletPoint::getY() const
    {
        return m_pos->getY();
    }

    float VerletPoint::getRadius() const
    {
        return m_radius;
    }

    float VerletPoint::getMass() const
    {
        return m_mass;
    }

    SVector VerletPoint::getPos() const
    {
        return *m_pos;
    }

    void VerletPoint::setX( float x )
    {
        m_pos->setX( x );
    }

    void VerletPoint::setY( float y )
    {
        m_pos->setY( y );
    }

    void VerletPoint::setOldX( float x )
    {
        m_oldPos->setX( x );
    }

    void VerletPoint::setOldY( float y )
    {
        m_oldPos->setY( y );
    }

    void VerletPoint::setMass( float mass )
    {
        m_mass = mass;
    }

    void VerletPoint::setRadius( float radius )
    {
        m_radius = radius;
    }

    int VerletPoint::hash()
    {
        int hash = 17;
        int x = (int)this->getX();
        int y = (int)this->getY();
        hash = ( ( hash + x ) << 5 ) - ( hash + x );
        hash = ( ( hash + y ) << 5 ) - ( hash + y );
        return hash;
    }
}
