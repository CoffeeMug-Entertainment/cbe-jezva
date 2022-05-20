#ifndef CB_UTIL_HPP
#define CB_UTIL_HPP

#include "Types/Vector2.hpp"

namespace IntId
{
    /*
    * Calculate Id to a single value
    * Id = y * size + x
    * X = id % size
    * Y = id / size
    */
    int Vec2IntId(CB::Vec2 data, int size) {

    return static_cast<int>(data.y) * size + static_cast<int>(data.x);
    }

    CB::Vec2 IntId2Vec(int Id, int size){
        return CB::Vec2{static_cast<float>(Id % size), static_cast<float>(Id / size)};
    }
}

#endif