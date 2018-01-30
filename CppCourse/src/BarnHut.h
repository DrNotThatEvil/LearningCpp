#ifndef BARNHUT_H
#define BARNHUT_H

#include "VerletPoint.h"
#include "screen.h"
#include "svector.h"
#include <vector>


namespace caveofprogramming
{
    struct Rectangle
    {
        int x;
        int y;
        int w;
        int h;
        int psize;
        int depth;
        bool done;
        float mass;
        Rectangle *p_parent;
        SVector *p_centermass;
        std::vector<VerletPoint *> *particles;
    };

    class BarnHut
    {
      private:
        int m_screenW;
        int m_screenH;
        int m_totalP;
        int m_maxDepth;
        VerletPoint *m_pParticles;
        std::vector<Rectangle> *m_drawRects;

      public:
        BarnHut( VerletPoint *particles, int psize, int screen_w, int screen_h );
        ~BarnHut();
        void solve();
        void solve( std::vector<Rectangle> rects );
        void findPointForce( VerletPoint &point );
        void render( Screen *screen );
    };
}

#endif /* BARNHUT_H */
