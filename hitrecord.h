#include "surface.h"
#pragma once
class HitRecord
{
    Surface s;
    Vector point; //Hit point
    Vector normal; //normal of the hitpoint
    bool hit;
    public:
    HitRecord(Surface s,Vector point,Vector normal,bool hit)
    {
        this-> s = s;
        this-> point = point;
        this-> normal = normal;
        this-> hit = hit;
    }
    Surface getSurface()
    {
        return s;
    }
    Vector getHitPoint()
    {
        return point;
    }
    Vector getNormal()
    {
        return normal;
    }
    bool didItHit()
    {
        return hit;
    }
    void printPoint()
    {
        point.printV();
    }
};