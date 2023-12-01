#include "surface.h"
#include "hitrecord.h"
#include "ray.h"
#include "light.h"
#pragma once
class Plane
{
    Surface s;
    Vector center;
    Vector normal;

public:
    Plane()
    {
        
    }
    Plane(Surface s, Vector center, Vector normal)
    {
        this->s = s;
        this->center = center;
        this->normal = normal;
    }
    HitRecord check(Ray r)
    {
        float d = normal.dotproduct(r.getDirection().normalize());

        if (d > 0.0001f) // your favorite epsilon
        {
            float t = (center.subtract(r.getOrigin())).dotproduct(normal) / d;
            if (t < 0)
            {
                HitRecord hit(s, r.at(t), normal, true);
                return hit;
            }
        }

        HitRecord h(s, Vector(0, 0, 0), Vector(0, 0, 0), false);
        return h;
    }
    Vector getColor(Ray r, Light l)
    {
        HitRecord t = check(r);
        if (t.didItHit())
        {
            Vector c = this->s.getColor();
            c = c.add(l.ambientLight(r, t, this->s.getMaterial()));
            c = c.add(l.diffuseLight(r, t, this->s.getMaterial()));
            // cout<<"-1";
            
            return c;
        }

        return Vector(0, 0, 0);
    }
    HitRecord getHitRecord(Ray r)
    {
        float d = normal.dotproduct(r.getDirection().normalize());

        if (d >= 0.0001f) // your favorite epsilon
        {
            float t = (center.subtract(r.getOrigin())).dotproduct(normal) / d;
            if (t <= 0)
            {
                HitRecord hit(s, r.at(t), normal, true);
                return hit;
            }
        }

        HitRecord h(s, Vector(0, 0, 0), Vector(0, 0, 0), false);
        return h;
    }
};