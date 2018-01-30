#ifndef SWARM_H
#define SWARM_H

#include "BarnHutMulti.h"
#include "VerletPoint.h"
#include "screen.h"

namespace caveofprogramming
{
    class Swarm
    {
      public:
        const static int NPARTICLES = 500;

      private:
        VerletPoint *m_pParticles;
        BarnHutMulti *m_barnhutmulti;
        int m_barnhutcount;

      public:
        Swarm();
        virtual ~Swarm();

        void update();
        void render( Screen *screen );
        const VerletPoint *const getParticles();
    };
}
#endif /* SWARM_H */
