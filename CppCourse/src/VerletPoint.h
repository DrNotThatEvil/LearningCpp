#ifndef VERLETPOINT_H
#define VERLETPOINT_H

#include "svector.h"

namespace caveofprogramming
{

    class VerletPoint
    {
      public:
        const static float GRAVITY;
        const static float BOUNCE;
        const static float FRICTION;

      private:
        SVector *m_pos;
        SVector *m_oldPos;
        float m_radius;
        float m_mass;

      public:
        VerletPoint();
        VerletPoint( float x, float y, float ox, float oy );
        VerletPoint( SVector *pos, SVector *oldPos );
        ~VerletPoint();
        float getX() const;
        float getY() const;
        float getRadius() const;
        float getMass() const;
        SVector getPos() const;
        void setX( float x );
        void setY( float y );
        void setOldX( float x );
        void setOldY( float y );
        void setMass( float mass );
        void setRadius( float radius );
        void update();
        void colide( VerletPoint &p2 );
        void colideNonMove( VerletPoint &p2 );
        void gravitateTo( const SVector *target, float mass );
        void gravitateTo( VerletPoint *target );
        int hash();
    };
}


#endif /* VERLETPOINT_H */
