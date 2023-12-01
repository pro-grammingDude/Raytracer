
#include "vector.h"
class Camera
{
    Vector e;  //origin
    Vector w;   // W is the lookAt vector. 
    int top;    //look up
    int right;  //lookright
    
    public:
    bool perspective; 
    Camera(Vector center,Vector LookAt, int width, int height,bool type)
    {
        e = center;
        w = LookAt.normalize();
        top = width;
        right = height;
        perspective = type;
    }   
    Vector getOrthographicPosition(float i, float j,int pixelX, int pixelY)    //generates the origin of the pixel in the camera
    {
        double u = -top + (((top + top)*(i + 0.5)))/pixelX;    //u = l + (r − l)(i + 0.5)/nx,  r =-l
        double v = -right + (((right +right)*(j +0.5)))/pixelY;   //v = b + (t − b)(j + 0.5)/ny,
        Vector origin(u,v,e.z);
        return origin;
    }
    Vector getOrthographicDirection()
    {
        return w.multS(-1);
    }

    // POSTION NEEDED FOR PERSPECTIVE AS ITS NOT 000 ALWAYS
    Vector getPerspectivePostition(float i, float j,int pixelX, int pixelY)
    {
        Vector U(1,0,0);
        Vector V(0,1,0);
        double u = -top + (((top + top)*(i + 0.5)))/pixelX;    //u = l + (r − l)(i + 0.5)/nx,
        double v = -right + (((right + right)*(j +0.5)))/pixelY;   //v = b + (t − b)(j + 0.5)/ny,
        Vector PcamE = e.add(U.multS(u).add(V.multS(v)));
        return PcamE;
    }
    Vector getPerpectiveDirection(float i, float j,int pixelX, int pixelY,float focalLength) //focalLength = d
    {

        Vector U(1,0,0);
        Vector V(0,1,0);
        double u = -top + (((top + top)*(i + 0.5)))/pixelX;    //u = l + (r − l)(i + 0.5)/nx,
        double v = -right + (((right + right)*(j +0.5)))/pixelY;   //v = b + (t − b)(j + 0.5)/ny,
        Vector temp(0,0,0);     //direction = – d w + u u + v v
        temp = U.multS(u).add(V.multS(v));
        temp = (w.multS(-1*focalLength)).add(temp);
        return temp.normalize();
    }
    bool getType()
    {
        return perspective;
    }
    
};