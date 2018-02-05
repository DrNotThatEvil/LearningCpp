#include "Screen.h"
#include <memory>

namespace wilvin
{
    Screen::Screen()
    {
    }

    bool Screen::init()
    {
        if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
        {
            return false;
        }

        m_window = std::unique_ptr<SDL_Window, SDLDeleter>(
            SDL_CreateWindow( "Gravity sim", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN ),
            SDLDeleter() );

        if ( m_window.get() == nullptr )
        {
            return false;
        }

        m_renderer = std::unique_ptr<SDL_Renderer, SDLDeleter>(
            SDL_CreateRenderer( m_window.get(), -1, SDL_RENDERER_PRESENTVSYNC ),
            SDLDeleter() );

        if ( m_renderer.get() == nullptr )
        {
            return false;
        }

        m_texture = std::unique_ptr<SDL_Texture, SDLDeleter>(
            SDL_CreateTexture( m_renderer.get(), SDL_PIXELFORMAT_RGBA8888,
                               SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH,
                               SCREEN_HEIGHT ),
            SDLDeleter() );

        if ( m_texture.get() == nullptr )
        {
            return false;
        }

        m_buffer = std::unique_ptr<Uint32>(
            new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT] );

        this->clear();

        return true;
    }

    void Screen::clear()
    {
        memset( m_buffer.get(), 0x00,
                SCREEN_WIDTH * SCREEN_HEIGHT * sizeof( Uint32 ) );
    }

    void Screen::setPixel(
        int x, int y, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha )
    {
        if ( x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT ) return;

        Uint32 color = 0;
        color += red;
        color <<= 8;

        color += green;
        color <<= 8;

        color += blue;
        color <<= 8;

        color += alpha;
        color <<= 8;

        m_buffer.get()[( y * SCREEN_WIDTH ) + x] = color;
    }

    void Screen::update()
    {
        SDL_UpdateTexture( m_texture.get(), NULL, m_buffer.get(),
                           SCREEN_WIDTH * sizeof( Uint32 ) );
        SDL_RenderClear( m_renderer.get() );
        SDL_RenderCopy( m_renderer.get(), m_texture.get(), NULL, NULL );
        SDL_RenderPresent( m_renderer.get() );
    }

    bool Screen::processEvents()
    {
        SDL_Event event;
        while ( SDL_PollEvent( &event ) )
        {
            if ( event.type == SDL_QUIT )
            {
                return false;
            }
        }
    }
}
