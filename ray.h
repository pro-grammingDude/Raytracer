#include "vector.h"
#pragma once
class Ray
{    
    Vector origin;
    Vector direction;
    
    public:

    Ray(Vector o,Vector d)
    {
        origin =o;
        direction = d;
    }
    Vector getDirection()
    {
        return direction;
    }
    Vector getOrigin()
    {
        return origin;
    }
    Vector at(float t)
    {
        return origin.add(direction.multS(t));
    }
    // bool hitSphere(Sphere s)
    // {
    //     if(s.check(this))
    //     return true;
    //     return false;
    // }
};