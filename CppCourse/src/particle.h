#ifndef PARTICLE_H
#define PARTICLE_H

#include "svector.h"

namespace caveofprogramming
{
    class Particle;

    struct collisionDataTemp
    {
        float depth;
        SVector normal;
        Particle *bod;
    };

    class Particle
    {
      public:
        SVector *m_pos;
        SVector *m_vel;
        collisionDataTemp coll;
        float m_radius;
        float m_mass;
        bool m_disabled;

        Particle();
        float angleTo( const Particle *p2 );
        float distanceTo( const Particle *p2 );
        void gravitateTo( const Particle *p2 );
        bool checkColl( Particle *colObj );
        bool checkColl( Particle *colObj, float dist );
        void processColl();
        float getMass();
        void setMass( float mass );
        virtual ~Particle();
        void update();
    };
}

#endif /* PARTICLE_H */
