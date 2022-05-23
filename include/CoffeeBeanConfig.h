#ifndef COFFEEBEANCONFIG_H
#define COFFEEBEANCONFIG_H

#include <string>

namespace CBE
{
    enum class CBE_Backend
    {
        SDL = 0,
        BACKEND_COUNT
    };

    struct window_info
    {
        int width;
        int height;

        int position_x;
        int position_y;

        int flags;
    };


    struct CoffeeBeanConfig
    {
        window_info window;
        std::string title;
        CBE_Backend backend;
    };
}

#endif