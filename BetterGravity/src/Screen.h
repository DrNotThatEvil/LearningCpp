#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>
#include <memory>

namespace wilvin
{
    struct SDLDeleter
    {
        void operator()( SDL_Window *p ) const
        {
            SDL_DestroyWindow( p );
        }
        void operator()( SDL_Renderer *p ) const
        {
            SDL_DestroyRenderer( p );
        }
        void operator()( SDL_Texture *p ) const
        {
            SDL_DestroyTexture( p );
        }
    };

    class Screen
    {
    public:
        const static int SCREEN_WIDTH = 1920;
        const static int SCREEN_HEIGHT = 1280;
        const static int PSCREEN_WIDTH = 1280;
        const static int PSCREEN_HEIGHT = 1024;

    private:
        std::unique_ptr<SDL_Window, SDLDeleter> m_window;
        std::unique_ptr<SDL_Renderer, SDLDeleter> m_renderer;
        std::unique_ptr<SDL_Texture, SDLDeleter> m_texture;
        std::unique_ptr<Uint32> m_buffer;

    public:
        Screen();
        bool init();
        bool processEvents();
        void clear();
        void update();
        void setPixel( const int x,
                       const int y,
                       Uint8 red,
                       Uint8 green,
                       Uint8 blue,
                       Uint8 alpha );
    };
}

#endif /* SCREEN_H */
