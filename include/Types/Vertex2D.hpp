#ifndef CB_VERTEX_2D
#define CB_VERTEX_2D

#include "Vector2.hpp"
#include "Colour.hpp"

namespace CB
{
    struct Vertex2D
    {
        Vec2 position;
        Colour color;

        #ifdef SDL_render_h_
        #include "SDL_render.h"

        inline SDL_Vertex ToSDLVertex()
        {
            SDL_Vertex vert;
            vert.position = position.toSDL_FPoint();
            vert.color = color.ToSDLColor();
            return vert;
        }

        Vertex2D& operator=(SDL_Vertex& rhs)
        {
            this->position = rhs.position;
            this->color = rhs.color;
            return *this;
        }

        #endif
    };
}

#endif