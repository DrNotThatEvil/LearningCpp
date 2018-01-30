#include "svector.h"
#include <cmath>
#include <iostream>

namespace caveofprogramming
{

    SVector::SVector()
    : m_x( 0.0f )
    , m_y( 0.0f )
    {
    }

    SVector::SVector( float x, float y )
    : m_x( x )
    , m_y( y )
    {
    }

    void SVector::setX( float x )
    {
        m_x = x;
    }

    float SVector::getX() const
    {
        return m_x;
    }

    void SVector::setY( float y )
    {
        m_y = y;
    }

    float SVector::getY() const
    {
        return m_y;
    }

    void SVector::setAngle( int angle )
    {
        float length = getLength();

        m_x = cos( angle ) * length;
        m_y = sin( angle ) * length;
    }

    float SVector::getAngle() const
    {
        return atan2( m_y, m_x );
    }

    void SVector::setLength( float l )
    {
        int angle = getAngle();
        m_x = cos( angle ) * l;
        m_y = sin( angle ) * l;
    }

    float SVector::getLength() const
    {
        return sqrt( m_x * m_x + m_y * m_y );
    }

    SVector SVector::operator+( const SVector &b )
    {
        SVector temp;
        temp.setX( m_x + b.getX() );
        temp.setY( m_y + b.getY() );
        return temp;
    }

    SVector &SVector::operator+=( const SVector &b )
    {
        if ( this != &b )
        {
            m_x = m_x + b.getX();
            m_y = m_y + b.getY();
        }
        return *this;
    }


    SVector SVector::operator-( const SVector &b )
    {
        SVector temp;
        temp.setX( m_x - b.getX() );
        temp.setY( m_y - b.getY() );
        return temp;
    }

    SVector &SVector::operator-=( const SVector &b )
    {
        if ( this != &b )
        {
            m_x = m_x - b.getX();
            m_y = m_y - b.getY();
        }
        return *this;
    }

    float SVector::operator*( const SVector &b )
    {
        return ( m_x * b.getX() + m_y * b.getY() );
    }

    SVector SVector::operator*( const float b )
    {
        SVector temp;
        temp.setX( m_x * b );
        temp.setY( m_y * b );
        return temp;
    }

    SVector &SVector::operator*=( const float b )
    {
        m_x *= m_x * b;
        m_y *= m_y * b;
        return *this;
    }

    SVector SVector::operator/( const float b )
    {
        SVector temp = SVector( 0.0f, 0.0f );
        if ( b > 0 )
        {
            temp.setX( m_x / b );
            temp.setY( m_y / b );
        }
        return temp;
    }

    SVector &SVector::operator/=( const float b )
    {
        if ( b > 0 )
        {
            m_x = m_x / b;
            m_y = m_y / b;
        }
        return *this;
    }

    void SVector::normalize()
    {
        float dist = sqrt( m_x * m_x + m_y * m_y );
        m_x /= dist;
        m_y /= dist;
    }

    void SVector::normalize( const float dist )
    {
        m_x /= dist;
        m_y /= dist;
    }

    SVector SVector::normalized()
    {
        float dist = sqrt( m_x * m_x + m_y * m_y );
        return SVector( m_x / dist, m_y / dist );
    }
}
