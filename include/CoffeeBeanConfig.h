#ifndef COFFEEBEANCONFIG_H
#define COFFEEBEANCONFIG_H

#include <string>

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
};


#endif