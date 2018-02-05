#ifndef SVECTOR_H
#define SVECTOR_H

namespace wilvin
{
    class SVector
    {
    private:
        float m_x;
        float m_y;

    public:
        SVector();
        SVector( float x, float y );
        float x() const;
        float y() const;
        float angle() const;
        float length() const;
        void setX( const float x );
        void setY( const float y );
        void setAngle( const int angle );
        void setLength( const float len );

        SVector operator+( const SVector &b );
        SVector &operator+=( const SVector &b );

        SVector operator-( const SVector &b );
        SVector &operator-=( const SVector &b );

        float operator*( const SVector &b );
        SVector operator*( const float b );
        SVector &operator*=( const float b );

        SVector operator/( const float b );
        SVector &operator/=( const float b );

        void normalize();
        void normalize( const float dist );
        SVector normalized();
        SVector normalized( const float dist );
    };
}

#endif /* SVECTOR_H */
