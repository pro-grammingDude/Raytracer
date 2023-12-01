#include "vector.h"
#include "material.h"
#pragma once
class Surface
{
    
    Vector color;
    Material mat;
    public:
    Surface()
    {
        this->color = Vector(0,0,0);
        this->mat = Material(0);
    }
    Surface(Vector color, Material mat)
    {
        this-> color = color;
        this->mat = mat;    
    }
    Vector getColor()
    {
        return color;
    }
    Material getMaterial()
    {
        return mat;
    }
};