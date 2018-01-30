#ifndef SCREEN_H
#define SCREEN_H

#include "SDL.h"

namespace caveofprogramming
{
    class Screen
    {
      public:
        const static int SCREEN_WIDTH = 1920;
        const static int SCREEN_HEIGHT = 1080;
        const static int PSCREEN_WIDTH = 1280;
        const static int PSCREEN_HEIGHT = 1024;

      private:
        SDL_Window *m_window;
        SDL_Renderer *m_renderer;
        SDL_Texture *m_texture;
        Uint32 *m_buffer;

      public:
        Screen();
        bool init();
        bool processEvents();
        void clear();
        void update();
        void setPixel( int x, int y, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha );
        void close();
    };
}

#endif /* SCREEN_H */
