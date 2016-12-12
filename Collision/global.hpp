/*************************************************************************
 * global.hpp for project Collision
 * Author : lzh
 * Modifier : Shlw lzh Shlw lzh lziad Shlw
 * Description : Global header for the whole project, including
 * inclusion of public headers and declarations.
 ************************************************************************/

// Check whether included
#ifndef CL_GLOBAL_HPP

#define CL_GLOBAL_HPP

// Include public headers
#include <cstdlib>
#include <cmath>
#include <climits>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include <vector>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#endif
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Exception Flags
#define ERROR_UNKNOWN_MODEL 0x0001
#define FILE_NOT_FOUND 0x0002
#define ERROR_TOO_MANY_OBJ 0x0003

// class declarations
class Point;
class Triangle;
class Model;
class Object;

// typedef definitions
typedef glm::vec3* PVec3;
typedef glm::vec4* PVec4;
typedef glm::mat4* PMat4;
typedef Point* PPoint;
typedef Triangle* PTriangle;
typedef Model* PModel;
typedef Object* PObject;

// matrix operations
PPoint MultPoint(PMat4 matrix,PPoint p);
PTriangle MultTriangle(PMat4 matrix,PTriangle cone);

// point class represents the still point in local coordinate system
class Point{
public:
    int nFlag;
    PVec4 vpCoordinate;
    PVec4 vpColor;

    Point();
    Point(PPoint example);
    Point(
        float x,float y,float z,
        float r,float g,float b,float alpha
    );
    ~Point();

    void DrawVertex();
};

// triangle class represents the still triangle(cone) in local coordinate system
class Triangle{
public:
    PPoint pppVertex[3];
    PVec4 vpNormalVector;

    Triangle();
    Triangle(PPoint a,PPoint b,PPoint c);
    Triangle(PPoint a,PPoint b,PPoint c,PVec4 v);
    ~Triangle();

    void Draw();
};

// model class represents the still model in local coordinate system
class Model{
public:
    int nLength; // the number of triangular cones
    PTriangle* tppCone; // the point array of triangle pointers
    float fVolume,fElastic,fMass,fMaxRadius;
    glm::mat3* mMomentOfInertia;

    Model();
    ~Model();

    void Draw();
};

// object class contains
// the matrix(mFrame) to transform between local and global coordinate system
// and several indispensable descriptive aspect of the object
class Object{
public:
    int nModelType;
    PMat4 mpFrame;
    PVec3 vpSpeed;
    PVec3 vpAngularMomentum;
    float fMomentInertia;

    Object();
    Object(int model,float vx=0,float vy=0,float vz=0,float mx=0,float my=0,float mz=0);
    ~Object();

    PTriangle IsInside(PPoint tp);

    void Draw();
    void Update();
};

extern int nModelTot;
extern int nObjectTot;
extern PModel mppModelList[100];
extern PObject oppObjectList[100];

// Declarations of global variables defined in .cpp files

// extern int nWindowFlags;
extern int nInitWindowWidth;
extern int nInitWindowHeight;
extern int nTimerSpeed;
extern const char* cpWindowTitle;

extern double dLastClock, dLastLastClock;
extern double dLastMouseX, dLastMouseY;
extern int npButtonState[3];
extern glm::mat4 mModelTransformMat;

extern float fRotateSpeed;
extern float fTranslateSpeed;
extern float fScrollSpeed;

extern float fpBoxLimit[6];

// Declarations of functions

int ReadFiles(const char* str);

void WindowInit();
void WindowCleanUp();

void Display(GLFWwindow* w);
int UnProjectNow(double x, double y, double z, double* rx, double* ry, double* rz);

void EventInit();
void MouseMotionEvent(GLFWwindow* w, double x, double y);
void MouseWheelEvent(GLFWwindow* w, double x, double y);
void MouseDropEvent(GLFWwindow* w, int c, const char** p);

void Draw();
void DrawBox();

void Update();

void GameInit();
void GameMove(GLFWwindow* w, double x, double y);
void GameDrag(GLFWwindow* w, int c, const char** p);

void ModelCleanUp();

int main(int argc, char *argv[]);

#endif
