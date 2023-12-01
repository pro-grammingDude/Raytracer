#include "ray.h"
#include<cmath>
#pragma once
class Light
{
    Vector pos;
    Vector dir;
    float intensity;
    Vector color;
    public:
    Light()
    {
        
    }
    Light(Vector p,Vector d,float i = 1)
    {
        pos = p;
        dir = d;
        color = Vector(255,255,255);
        intensity = i;
    }
    Vector getPos()
    {
        return pos;
    }
    Vector getDir()
    {
        return dir;
    }
    float getIntensity()
    {
        return intensity;
    }
    Vector ambientLight(Ray ray,HitRecord h,Material m)  
    {
    float ambient_coeff = m.getAmbientCoeff();
    return h.getSurface().getColor().multS(ambient_coeff);
    }
    Vector diffuseLight(Ray r,HitRecord h,Material m)
    {
        float diffuse_coeff = m.getDiffuseCoeff();
        float reflected_light = diffuse_coeff * this->intensity * max(0.0f,h.getNormal().dotproduct(this->pos.normalize()));//k*I*max(0,n.V);
        Vector c = this->color.multS(reflected_light);
        return c;
        
    }
    Vector specularLight(Ray r,HitRecord h,Material m)
    {
        float specualr_coeff = m.getSpecualrCoeff();
        float n = 150;
        Vector specv = r.getDirection().multS(-1);
        Vector specl = this->pos.subtract(h.getHitPoint()).normalize();
        Vector specn = h.getNormal();
        Vector spech = (specv.add(specl)).multS(1.0f/(specv.add(specl)).magnitude());
        float Ls = specualr_coeff * pow(max(0.0f,specn.dotproduct(spech)),n);
        return this->color.multS(Ls);
    }
};
// class AmbientLight : private Light{
//   public:
//   Vector illuminate(Ray ray,HitRecord h)  
//   {
//     float r = h.getSurface().getMaterial().getReflectance();
//     float k = r/3.14f;
//     return h.getSurface().getColor().multS(k);

//   }
// };