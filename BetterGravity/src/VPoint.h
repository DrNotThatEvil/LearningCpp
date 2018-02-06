#ifndef VERLETPOINT_H
#define VERLETPOINT_H

#include "SVector.h"
#include "Screen.h"
#include <memory>

namespace wilvin
{
    class VPoint
    {
    public:
        const static float GRAVITY;
        const static float BOUNCE;
        const static float FRICTION;

    private:
        std::unique_ptr<SVector> m_pos;
        std::unique_ptr<SVector> m_oldPos;
        float m_radius;
        float m_mass;

    public:
        VPoint();
        VPoint( const float x, const float y, const float ox, const float oy );
        VPoint( const float x,
                const float y,
                const float ox,
                const float oy,
                const float radius );
        VPoint( const float x,
                const float y,
                const float ox,
                const float oy,
                const float radius,
                const float mass );
        VPoint( std::unique_ptr<SVector> pos,
                std::unique_ptr<SVector> oldPos,
                const float radius );
        VPoint( std::unique_ptr<SVector> pos,
                std::unique_ptr<SVector> oldPos,
                const float radius,
                const float mass );

        ~VPoint();
        float x() const;
        float y() const;
        float oldX() const;
        float oldY() const;
        float radius() const;
        float mass() const;
        SVector *getPos() const;
        SVector *getOldPos() const;
        void setX( const float x );
        void setY( const float y );
        void setOldX( const float x );
        void setOldY( const float y );
        void render( Screen &screen );
        void update();
        void colide( VPoint &target );
        void colideNonMove( VPoint &target );
        void gravitateTo( SVector &target, float mass );
        void gravitateToPoint( VPoint &target );
    };
}

#endif /* VERLETPOINT_H */
