#include <iostream>
#include <stdlib.h>
#include<GL/gl.h>
#include <GL/glut.h>
#include<math.h>
#include<fstream>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include<windows.h>

using namespace std;
//#include <cstdlib>
//if you got error in exit() by compiler then does not incluede stdlib.h because //exit() is also defined in glut.h file.

float skyTextureTiles = 1;
float angle=0.0,deltaAngle = 0.0,ratio;

//BEGINING CAMERA
float x=0.0f,y=2.75f,z=+25.0f;
float zoom = 60.0;

float lx=0.0f,ly=0.0f,lz=-1.0f;
int deltaMove = 0,h,w;
int font=(int)GLUT_BITMAP_8_BY_13;
static GLint snowman_display_list;
int bitmapHeight=13;

int frame,time,timebase=0;
char s[30];


void changeSize(int w1, int h1);


//FOR LOADING TEXTURE
GLUquadric *loaded_quad;
GLuint grass,sky,zombie;


//ZOMBIE GLOBAL
int rightHandAngle = 180; // Angle of lower right hand
int leftHandAngle = 180; // Angle of lower left hand
bool mouseLeftState = false; // Is left mouse clicked?
bool mouseRightState = false; // Is right mouse clicked?
int rightHandMove = 2; // If left mouse clicked, right hand will rotate 2 degrees.
int leftHandMove = 2;
int leftLegMove = 1; // If right mouse clicked, left leg will move by 1.
int rightLegMove = -1; // If right mouse clicked, right leg will move by 1.
int leftLegAngle = 90; // If right mouse clicked, this variable will be used to rotate left leg and it initialized to 90 degrees for first position of leg.
int rightLegAngle = 90; // If right mouse clicked, this variable will be used to rotate right leg and it initialized to 90 degrees for first position of leg.
float zMove = 0.0; // If right mouse clicked, this variable will be used to change position of object. Object will move on z-axis.
float legSpeed = 1.5f;


void zombieShow();

#include "helpers.h"
#include "draw.h"



bool leftMouseButtonDown = false;
bool rightMouseButtonDown = false;

void mouseClickFunc(int button, int state, int x, int y)
{
    // Save the left button state
    if (button == GLUT_LEFT_BUTTON)
    {
        leftMouseButtonDown = (state == GLUT_DOWN);
    }

    else if (button == GLUT_RIGHT_BUTTON)
    {
        // \/ right MouseButton
        rightMouseButtonDown = (state == GLUT_DOWN);
    }
}


float mouse_x = 0;
float mouse_y = 0;

float xAngle = 0.0;
float yAngle = 0.0;

#include "keyboardmouse.h"



void renderScene(void)
{

    int wh = glutGet(GLUT_WINDOW_HEIGHT);
    int ww = glutGet(GLUT_WINDOW_WIDTH);

    if(rightMouseButtonDown)
    {
        zoom = 10;
        changeSize(ww,wh);
    }
    else
    {
        zoom = 45;
        changeSize(ww,wh);
    }


    if (deltaMove)
        moveMeFlat(deltaMove);
    if (deltaAngle)
    {
        angle += deltaAngle;
        orientMe(angle);
    }



    orientMe(xAngle);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    drawGround();

// Draw 36 Snow Men

    glCallList(snowman_display_list);


    glOrtho(-750.0, 750.0, -1300.0, 500.0, -500.0, 500.0); // Changing the coordinate system.

    glPushMatrix();

    glRotatef(90,0.0,1.0,0);


    zombieShow();
    tower(0,0,5000,2000);
    glPopMatrix();


    show2D();

    glutSwapBuffers();
}

void initWindow()
{
    glEnable ( GL_TEXTURE_2D );
    glEnable(GL_DEPTH_TEST);
    loaded_quad = gluNewQuadric();
    gluQuadricTexture( loaded_quad, GL_TRUE);


    glutWarpPointer(1280 / 2, 720 / 2);


    grass = LoadBitmap("image/grass.bmp");
    zombie = LoadBitmap("image/zombie.bmp");
    sky = LoadBitmap("image/sky.bmp");


    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);

    glutMotionFunc(mouseMotion);
    glutPassiveMotionFunc(mouseMotion);
    glutMouseFunc(mouseClickFunc);

    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutReshapeFunc(changeSize);
    initScene();

}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(20,20);
    glutInitWindowSize(1280,720);


    glutCreateWindow("Snowman");

// register all callbacks
    initWindow();

    glutMainLoop();

    return(0);
}
