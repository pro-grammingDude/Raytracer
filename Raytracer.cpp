#include "GL/glew.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include <iostream>
#include<cmath>
#include "sphere.h"
#include "camera.h"
#include "plane.h"
using namespace std;



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;


const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "layout (location = 2) in vec2 aTexCoord;\n"
    "out vec3 ourColor;\n"
    "out vec2 TexCoord;\n"
    "void main()\n"
    "{\n"
	"gl_Position = vec4(aPos, 1.0);\n"
	"ourColor = aColor;\n"
	"TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "in vec2 TexCoord;\n"
    "uniform sampler2D texture1;\n"
    "void main()\n"
    "{\n"
    "   FragColor = texture(texture1, TexCoord);\n"
    "}\n\0";
    
Vector reflect(Ray r,HitRecord h,Plane p,Sphere s1,Sphere s2,Light l)
{
    Vector reflectedRayDirection = r.getDirection().reflect(r.getDirection(),h.getNormal());
    Ray reflectedRay(h.getHitPoint(),reflectedRayDirection);
    Vector ec = h.getHitPoint().subtract(s1.getCenter()); // e-c
        
        
        float b = (reflectedRayDirection.dotproduct(ec)) ;  //d⋅(e−c))

        float c = ec.dotproduct(ec) - s1.getRadius()*s1.getRadius(); //(e-c).(e-c)
        float a = reflectedRayDirection.dotproduct(reflectedRayDirection) ; // d.d 
        
       
        float discriminant = (b*b) - a*c;
        //h.getHitPoint().printV();
    //cout<<a<<" "<<b<<" "<<c<<" "<<ec.magnitude()<<" "<<discriminant<<<<" ::::::::::";
    Vector color = s1.getColorNoLight(reflectedRay);
    if(color.x == 0 && color.y == 0 && color.z == 0)
    {
        color= s2.getColorNoLight(reflectedRay);
    }
    Vector planeColor = p.getColor(r,l);
    color = color.add(planeColor);
    return color;

}

Vector cameraPos(0,0,0);
Vector cameraLookAt(0,0,-1);
bool perspective_camera = false;

Camera c(cameraPos,cameraLookAt, 8, 8,perspective_camera);
Sphere s,s1;
Vector origin,lightPos,lightDir;
Material material_Plane,material_s;
Plane plane;
Light light;
Camera Render(bool perspective_camera){
    c= Camera (cameraPos,cameraLookAt, 8, 8,perspective_camera);
    origin = Vector(0,0,0);
    lightPos= Vector(25,-6,0);
    lightDir= Vector(0,0,0);
    material_Plane= Material(3.0f,0.4f,0.5f,0.2f);
    material_s= Material(0,0.6f,0.5f,0.4f);
    plane= Plane(Surface(Vector(112,255,246),material_Plane),Vector(0,0,0),Vector(0,1,0));
    s = Sphere (Vector(9,5,1),4.0f,Vector(10,150,10),material_s);   
    s1 = Sphere (Vector(15,15,1),4.0f,Vector(120,10,10),material_s);
    light=Light (lightPos,lightDir,0.9f);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS && key == GLFW_KEY_Q  ) {
        perspective_camera = !perspective_camera;
        Render(perspective_camera);

    }
}

int main()
{
    
    Render(perspective_camera=true);
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Display RGB Array", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetKeyCallback(window, key_callback);
    // // GLEW: load all OpenGL function pointers
    glewInit();

    // build and compile the shaders
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // load and create a texture 
    // -------------------------
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Create the image (RGB Array) to be displayed
    // Create the image (RGB Array) to be displayed
    const int width  = 512; // keep it in powers of 2!
    const int height = 512; // keep it in powers of 2!

   
    
    unsigned char image[width*height*3];
    
    
    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int idx = (i * width + j) * 3;
            Vector dir(0,0,1);    
            if(c.getType())
            {
                origin = c.getPerspectivePostition(i,j,width/2,height/2);
                dir = c.getPerpectiveDirection(i,j,width/2,height/2,100);
            }  
            else
            {
                origin = c.getOrthographicPosition(i,j,width,height);
                dir = c.getOrthographicDirection();
            }     
            
            
            Ray r(origin,dir);
            Vector color(0,0,0);
            color = s.getColor(r,light);
            if(color.x == 0 && color.y == 0 && color.z == 0)
            {
                
                color = s1.getColor(r,light);
            }
            if(color.x == 0 && color.y == 0 && color.z == 0)
            {
                
                color = plane.getColor(r,light);
                // if(color.x == 0 && color.y == 0 && color.z == 0)
                // {
                    
                    
                // }
                // else
                // {
                //     HitRecord temp = plane.getHitRecord(r);              
                    
                //     Vector rcolor=reflect(r,temp,plane,s,s1,light);                    
                //     color = color.add(rcolor);
                // }
            }
            if(color.x == 0 && color.y == 0 && color.z == 0)
            {
                color = Vector(0,120,180);
            }
            image[idx] = color.x;
            image[idx+1] = color.y;
            image[idx+2] = color.z;
            
        }
    }
    
    unsigned char *data = &image[0];
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
   


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // bind Texture
        glBindTexture(GL_TEXTURE_2D, texture);

        // render container
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


