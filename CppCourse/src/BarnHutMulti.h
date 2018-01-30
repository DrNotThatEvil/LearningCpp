#ifndef BARNHUTMULTI_H
#define BARNHUTMULTI_H

#include "VerletPoint.h"
#include "screen.h"
#include <SDL2/SDL.h>
#include <algorithm>
#include <cmath>
#include <vector>

namespace caveofprogramming
{
    class BarnHutMulti
    {
      private:
        int m_x;
        int m_y;
        int m_width;
        int m_height;
        int m_numThreads;
        int m_wRemaining;
        bool m_drawed;
        bool m_running;
        bool m_done;
        volatile int m_avilableThreads;
        std::vector<VerletPoint *> m_contained;
        std::vector<SDL_Thread *> m_pThreads;
        BarnHutMulti *m_parent;
        BarnHutMulti **m_children;

      protected:
        static int startThread( void *data );

      private:
        int thread();
        void makeThreadAvialable();
        void setParentThread( BarnHutMulti *parent );
        std::vector<VerletPoint *>
        getContained( int x, int y, int width, int height, std::vector<VerletPoint *> possible );

      public:
        BarnHutMulti( const int x,
                      const int y,
                      const int width,
                      const int height,
                      const int numThreads,
                      const std::vector<VerletPoint *> contained );
        ~BarnHutMulti();
        bool isDone();
        bool isStarted();
        void startSolve();
        void render( Screen *screen );
    };
}

#endif /* BARNHUTMULTI_H */
