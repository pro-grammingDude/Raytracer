#include<iostream>
#include<cmath>
#pragma once
using namespace std;
class Vector
{
    public: 
    double x,y,z;
    
    Vector(double a=0,double b=0,double c=0)
    {
        x = a;
        y = b;
        z = c;
    }
    float magnitude()
    {
        return sqrt(x*x + y*y + z*z);
    }
    float dotproduct(Vector a)
    {
        float ans = a.x* x  + a.y*y + a.z*z;
        return ans;        
    }
    void printV()
    {
        cout<<"x: "<<x<<" y: "<<y<<" z: "<<z;
    }
    Vector add(float a)
    {
        Vector ans(x+a,y+a,z+a);
        return ans;
    }
    Vector add(Vector a)
    {
        Vector ans(x+a.x,y+a.y,z+a.z);
        return ans;
    }
    Vector multS(float a)
    {
        Vector ans(x*a,y*a,z*a);
        return ans;
    }
    Vector subtract(Vector a)
    {
        Vector ans(x- a.x, y - a.y, z-a.z);
        return ans;
    }
    Vector divide(float a)
    {
        Vector ans(x/a,y/a,z/a);
        return ans;
    }
    Vector normalize()
    {
        double length = sqrt((x*x) + (y*y) + (z*z));
        double x1 = x/length;
        double y1 = y/length;
        double z1 = z/length;
        Vector n(x1,y1,z1);
        return n;
    }
    Vector reflect(Vector incident,Vector normal)
    {
        Vector reflectedRayDirection = incident.subtract( normal.multS(2*(normal.dotproduct(incident))));
        return reflectedRayDirection;
    }
};