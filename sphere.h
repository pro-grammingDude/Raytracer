#include "hitrecord.h"
#include "ray.h"
#include "light.h"
#include<cmath>
class Sphere{
    Surface s;
    Vector center;
    float radius;
    public:
    Sphere()
    {
        
    }
    Sphere(Vector center, float radius,Vector color,Material mat)
    {
        this->center = center;
        this->radius = radius;
        s = Surface(color,mat);
        
    }
    Vector getCenter()
    {
        return center;
    }
    float getRadius()
    {
        return radius;
    }
    Vector getNormal(Vector hitpoint)
    {
        return hitpoint.subtract(center);
    }
    HitRecord check(Ray r)
    {
        Vector ray_direction  = r.getDirection().normalize(); //d
        
        Vector ec = r.getOrigin().subtract(center); // e-c
        
        
        float b = (ray_direction.dotproduct(ec)) ;  //d⋅(e−c))

        float c = ec.dotproduct(ec) - radius*radius; //(e-c).(e-c)
        float a = ray_direction.dotproduct(ray_direction) ; // d.d 
        
       
        float discriminant = (b*b) - a*c;
        
        double t = 0;  
        
        
        if(discriminant < 0)
        {
                                 
            HitRecord hit(this->s,0,0,false);
            return hit;
            
        }
        else
        {
            float root_discriminant = sqrt(discriminant);
            t = min((-b + root_discriminant) /(1.0f*a),(-b - root_discriminant) /(a*1.0f));
            Vector hitPoint = r.at(t);
            Vector normal = getNormal(hitPoint).normalize();
            HitRecord hit1(this->s,hitPoint,normal,true);
            return hit1;
        }
    }
    
    
    Vector getColor(Ray r,Light l) 
    {
        
        HitRecord t = check(r);
        if(t.didItHit())
        {
            
            Vector color = l.ambientLight(r,t,this->s.getMaterial());
            color = color.add(l.diffuseLight(r,t,this->s.getMaterial()));      
            Vector spec = l.specularLight(r,t,this->s.getMaterial());
               
            color = color.add(spec);
            return color;
        }
        
        Vector zero(0,0,0);
        return zero;
    }

    Vector getColorNoLight(Ray r) 
    {
        
        Vector color(0,0,0);
        HitRecord t = check(r);
        if(t.didItHit())
        {
            cout<<" ";
            color = t.getSurface().getColor();
            
        }        
        
        return color;

    }
    
};