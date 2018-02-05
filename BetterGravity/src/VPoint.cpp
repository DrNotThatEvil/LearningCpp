#include "VPoint.h"
#include <memory>

namespace wilvin
{
    const float VPoint::GRAVITY = 0.8f;
    const float VPoint::BOUNCE = 1.0f;
    const float VPoint::FRICTION = 1.0f;

    VPoint::VPoint()
    {
        m_pos = std::unique_ptr<SVector>( new SVector( 0.0f, 0.0f ) );
        m_oldPos = std::unique_ptr<SVector>( new SVector( 0.0f, 0.0f ) );
        m_radius = 5.0f;
        m_mass = 1.0f;
    }

    VPoint::VPoint( const float x,
                    const float y,
                    const float ox,
                    const float oy )
    {
        m_pos = std::unique_ptr<SVector>( new SVector( x, y ) );
        m_oldPos = std::unique_ptr<SVector>( new SVector( ox, oy ) );
        m_radius = 5.0f;
        m_mass = 1.0f;
    }

    VPoint::VPoint( const float x,
                    const float y,
                    const float ox,
                    const float oy,
                    const float radius )
    {
        m_pos = std::unique_ptr<SVector>( new SVector( x, y ) );
        m_oldPos = std::unique_ptr<SVector>( new SVector( ox, oy ) );
        m_radius = radius;
        m_mass = 1.0f;
    }

    VPoint::VPoint( const float x,
                    const float y,
                    const float ox,
                    const float oy,
                    const float radius,
                    const float mass )
    {
        m_pos = std::unique_ptr<SVector>( new SVector( x, y ) );
        m_oldPos = std::unique_ptr<SVector>( new SVector( ox, oy ) );
        m_radius = radius;
        m_mass = mass;
    }

    VPoint::VPoint( std::unique_ptr<SVector> pos,
                    std::unique_ptr<SVector> oldPos,
                    const float radius )
    : m_pos( std::move( pos ) )
    , m_oldPos( std::move( oldPos ) )
    , m_radius( radius )
    , m_mass( 1.0f )
    {
    }

    VPoint::VPoint( std::unique_ptr<SVector> pos,
                    std::unique_ptr<SVector> oldPos,
                    const float radius,
                    const float mass )

    : m_pos( std::move( pos ) )
    , m_oldPos( std::move( oldPos ) )
    , m_radius( radius )
    , m_mass( mass )
    {
    }

    VPoint::~VPoint()
    {
    }

    float VPoint::x() const
    {
        return m_pos.get()->x();
    }

    float VPoint::y() const
    {
        return m_pos.get()->y();
    }

    float VPoint::oldX() const
    {
        return m_oldPos.get()->y();
    }

    float VPoint::oldY() const
    {
        return m_oldPos.get()->y();
    }

    float VPoint::radius() const
    {
        return m_radius;
    }

    float VPoint::mass() const
    {
        return m_mass;
    }

    SVector *VPoint::getPos() const
    {
        return m_pos.get();
    }

    SVector *VPoint::getOldPos() const
    {
        return m_oldPos.get();
    }

    void VPoint::setX( const float x )
    {
        ( *m_pos ).setX( x );
    }

    void VPoint::setY( const float y )
    {
        ( *m_pos ).setY( y );
    }

    void VPoint::setOldX( const float x )
    {
        ( *m_oldPos ).setX( x );
    }

    void VPoint::setOldY( const float y )
    {
        ( *m_oldPos ).setY( y );
    }

    void VPoint::render( Screen &screen ) const
    {
        Uint8 alpha = 0xFF;

        for ( float angle = 0.0; angle < 360; angle += 5.0f )
        {
            int x = ( *m_pos ).x() - m_radius * cos( angle );
            int y = ( *m_pos ).y() - m_radius * sin( angle );
            screen.setPixel( x, y, 0xFF, 0xFF, 0xFF, alpha );
        }

        screen.setPixel( ( *m_pos ).x(), ( *m_pos ).y(), 0xFF, 0xFF, 0xFF,
                         alpha );
    }

    void VPoint::colide( VPoint &target )
    {
        /// Handle colision
        float x = ( *m_pos ).x() - ( target.x() );
        float y = ( *m_pos ).y() - ( target.y() );
        float len = sqrt( x * x + y * y );
        float targetlen = m_radius + target.radius();

        if ( len < targetlen )
        {
            float factor = ( len - targetlen ) / len / 2;
            *m_pos -= SVector( x * factor, y * factor );

            target.setX( target.x() + x * factor );
            target.setY( target.y() + y * factor );
        }
    }

    void VPoint::colideNonMove( VPoint &target )
    {
        this->colide( target );

        *m_oldPos = *m_pos;
        target.setOldX( target.x() );
        target.setOldY( target.x() );
    }

    void VPoint::gravitateTo( SVector &target, float mass )
    {
        SVector grav = SVector( 0.0f, 0.0f );

        float x = ( *m_pos ).x() - target.x();
        float y = ( *m_pos ).y() - target.y();
        float dist = sqrt( x * x + y * y );

        grav.setLength( ( mass / ( dist * dist ) ) / m_mass );

        float angle
            = atan2( target.y() - ( *m_pos ).y(), target.x() - ( *m_pos ).x() );

        grav.setAngle( angle );
        *m_pos += grav;
    }

    void VPoint::gravitateToPoint( VPoint &target )
    {
        this->gravitateTo( *target.getPos(), target.mass() );
    }

    void VPoint::update()
    {
        /// update
        SVector v = ( *m_pos - *m_oldPos ) * FRICTION;
        *m_oldPos = *m_pos;
        *m_pos += v;

        if ( ( *m_pos ).x() > Screen::SCREEN_WIDTH
             || ( *m_pos ).x() < ( m_radius * 0.5 )
             || ( *m_pos ).y() > Screen::SCREEN_HEIGHT
             || ( *m_pos ).y() < ( m_radius * 0.5 ) )
        {
            float x
                = static_cast<float>( rand() ) / static_cast<float>( RAND_MAX )
                  - 0.5;
            float y
                = static_cast<float>( rand() ) / static_cast<float>( RAND_MAX )
                  - 0.5;

            m_pos->setX( ( Screen::SCREEN_WIDTH / 2 )
                         + ( x * ( Screen::PSCREEN_WIDTH ) ) );
            m_pos->setY( ( Screen::SCREEN_HEIGHT / 2 )
                         + ( y * ( Screen::PSCREEN_HEIGHT ) ) );
            m_oldPos->setX( ( *m_pos ).x() );
            m_oldPos->setY( ( *m_pos ).y() );
        }
    }
}
