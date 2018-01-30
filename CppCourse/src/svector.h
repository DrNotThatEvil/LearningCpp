#ifndef __SVECTOR_INCLUDE__
#define __SVECTOR_INCLUDE__

namespace caveofprogramming
{

    class SVector
    {
      private:
        float m_x;
        float m_y;

      public:
        SVector();
        SVector( float x, float y );
        void setX( float x );
        float getX() const;
        void setY( float y );
        float getY() const;
        void setAngle( int angle );
        float getAngle() const;
        void setLength( float l );
        float getLength() const;

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

#endif
