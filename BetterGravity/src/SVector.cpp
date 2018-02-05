#include "SVector.h"
#include <cmath>
#include <iostream>

namespace wilvin
{

    // Constructors
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

    // Getters
    float SVector::y() const
    {
        return m_y;
    }

    float SVector::x() const
    {
        return m_x;
    }

    float SVector::angle() const
    {
        return atan2( m_y, m_x );
    }

    float SVector::length() const
    {
        return sqrt( m_x * m_x + m_y * m_y );
    }

    void SVector::setX( float x )
    {
        m_x = x;
    }

    void SVector::setY( const float y )
    {
        m_y = y;
    }

    void SVector::setAngle( const int angle )
    {
        float length = this->length();

        m_x = cos( angle ) * length;
        m_y = sin( angle ) * length;
    }

    void SVector::setLength( const float l )
    {
        int angle = this->angle();
        m_x = cos( angle ) * l;
        m_y = sin( angle ) * l;
    }

    SVector SVector::operator+( const SVector &b )
    {
        SVector temp;
        temp.setX( m_x + b.x() );
        temp.setY( m_y + b.y() );
        return temp;
    }

    SVector &SVector::operator+=( const SVector &b )
    {
        if ( this != &b )
        {
            m_x = m_x + b.x();
            m_y = m_y + b.y();
        }
        return *this;
    }


    SVector SVector::operator-( const SVector &b )
    {
        SVector temp;
        temp.setX( m_x - b.x() );
        temp.setY( m_y - b.y() );
        return temp;
    }

    SVector &SVector::operator-=( const SVector &b )
    {
        if ( this != &b )
        {
            m_x = m_x - b.x();
            m_y = m_y - b.y();
        }
        return *this;
    }

    float SVector::operator*( const SVector &b )
    {
        return ( m_x * b.x() + m_y * b.y() );
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

    SVector SVector::normalized( const float dist )
    {
        return SVector( m_x / dist, m_y / dist );
    }
}
