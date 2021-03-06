#ifndef BARNHUTMULTI_H
#define BARNHUTMULTI_H

#include "VPoint.h"
#include <vector>

namespace wilvin
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
        bool m_running;
        bool m_done;
        int m_avilableThreads;
        std::vector<VPoint *> m_contained;
        std::vector<SDL_Thread *> m_pThreads;
        std::shared_ptr<BarnHutMulti> m_parent;
        std::vector<std::unique_ptr<BarnHutMulti>> m_children;

    protected:
        static int startThread( void *data );

    private:
        int thread();
        void setParentThread( std::shared_ptr<BarnHutMulti> parent );
        static std::vector<VPoint *>
        getContained( int x,
                      int y,
                      int width,
                      int height,
                      std::vector<VPoint *> possible );

    public:
        BarnHutMulti( const int x,
                      const int y,
                      const int width,
                      const int height,
                      const int numThreads,
                      const std::vector<VPoint *> contained );
        virtual ~BarnHutMulti();
        bool isDone();
        bool isStarted();
        void startSolve();
        void render( Screen *screen );
    };
}

#endif /* BARNHUTMULTI_H */
