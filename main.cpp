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

//#include <cstdlib>
//if you got error in exit() by compiler then does not incluede stdlib.h because //exit() is also defined in glut.h file.

float skyTextureTiles = 1;
float angle=0.0,deltaAngle = 0.0,ratio;
float skySphere = 100.0;

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
GLuint grass,sky,zombie,sand;


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
float zombieMoveSpeed = 7.5f;

float mouse_x = 0;
float mouse_y = 0;

float xAngle = 0.0;
float yAngle = 0.0;


bool leftMouseButtonDown = false;
bool rightMouseButtonDown = false;

class Zombie {
   public:
      double xLoc;   // Length of a box
      int goLeftOrRight;
      float startPosX;
      bool alive;
      Zombie(int p_goLeftOrRight, float p_startPosX){
          goLeftOrRight = p_goLeftOrRight;
          startPosX = p_startPosX;
          alive = true;
      }



    //L TO R RANGE -23800->23800
   // std::cout<<(startPosX+zMove) - 23800<<std::endl;


      void checkIfAlive(){
            int ww = glutGet(GLUT_WINDOW_WIDTH);
            double mX = (mouse_x) - 1365/2 ;
            double ownX = (double)((double)(startPosX+zMove)/(17.289 * 2 ) ) + 80;

            std::cout<<"M: "<<mX<<std::endl;
            std::cout<<"O: "<<ownX<<std::endl;

          if(leftMouseButtonDown){

            if(goLeftOrRight == 0){
                    //mX > .5
                    mX = (1-mX) + 0.06;
            }



            if( mX < ownX + 0.01 && mX > ownX - 0.01){
                alive = false;
            }
          }
      }

      void drawZombie();
};

    //23800 is scope reach
    Zombie zom_1(0,-23600);
   // Zombie zom_2(1,-23800);




#include "helpers.h"
#include "draw.h"



#include "keyboardmouse.h"

void renderScene(void)
{

    int wh = glutGet(GLUT_WINDOW_HEIGHT);
    int ww = glutGet(GLUT_WINDOW_WIDTH);

    //ZOOM SCOPE
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

    zom_1.drawZombie();

    //zom_2.drawZombie();


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
    glutFullScreen();


    grass = LoadBitmap("image/grass.bmp");
    zombie = LoadBitmap("image/zombie.bmp");
    sky = LoadBitmap("image/sky.bmp");
    sand = LoadBitmap("image/sand.bmp");


    //glutIgnoreKeyRepeat(1);
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

    glutCreateWindow("The Last Sniper");

    initWindow();

    glutMainLoop();

    return(0);
}
