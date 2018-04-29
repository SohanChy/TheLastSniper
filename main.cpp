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
#include <string>
#include<windows.h>
#include<windows.h>
#include <sstream>

double real_scores[6]={1,2,3,4,5,6};
//#include <cstdlib>
//if you got error in exit() by compiler then does not incluede stdlib.h because //exit() is also defined in glut.h file.

int paused = 3;
float skyTextureTiles = 1;
float angle=0.0,deltaAngle = 0.0,ratio;
float skySphere = 100.0;

//BEGINING CAMERA
float x=0.0f,y=2.75f,z=+25.0f;
float zoom = 60.0;

float lx=0.0f,ly=0.0f,lz=-1.0f;
int deltaMove = 0,h,w;
int font=(int)GLUT_BITMAP_8_BY_13;
int bitmapHeight=13;

int pausedTime = 0;
int frame,time,timebase=0;
int newGameTime = 0;
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
 // If right mouse clicked, this variable will be used to change position of object. Object will move on z-axis.



float mouse_x = 0;
float mouse_y = 0;

float xAngle = 0.0;
float yAngle = 0.0;


bool leftMouseButtonDown = false;
bool rightMouseButtonDown = false;

void sortTheThing();
void saveScores();
void getTopScores();
bool checkCondition(double a,double b);

class Zombie {
   public:
      double xLoc;   // Length of a box
      int goLeftOrRight;
      float startPosX;
      float zMove = 0.0;
      float zombieMoveSpeed = 4.0f;
      bool hide = true;


      float mmmx = 1365;
      float spd = zombieMoveSpeed / 61.5384615;
      float acc = 0.0002010118;

      bool alive;
      Zombie(){
      }
      Zombie(int p_goLeftOrRight, float p_startPosX){
          goLeftOrRight = p_goLeftOrRight;
          startPosX = p_startPosX;
          alive = true;
      }
      void setup(int p_goLeftOrRight, float p_startPosX,float p_zombieMoveSpeed){
          goLeftOrRight = p_goLeftOrRight;
          startPosX = p_startPosX;
          alive = true;
          zombieMoveSpeed = p_zombieMoveSpeed;
          zMove = 0;
          hide = true;

          mmmx = 1365;


      }

    //L TO R RANGE -23800->23800
   //

    int holdVal = -23450;
    int cnt = 0;
    int deadTime = 0;
      void checkIfAlive(){

          float ownX = startPosX + zMove;

          //game over
          if(ownX > -1200){


                if( paused != 2){


                    real_scores[5] = (time - newGameTime)/1000;
                    saveScores();
                }

                 paused = 2;
          }



          if(time - deadTime > 250 && deadTime != 0){
            alive = false;
          }

          if(zMove > 14500){
                zMove = zMove + 0.3d;
          }

            if(zombieMoveSpeed != 0.0){
             {
                 hide = false;

                mmmx = mmmx - spd;
                spd = spd + spd * acc;

                if(leftMouseButtonDown){
                    if( abs(mouse_x - floor(mmmx)) < 5){
                        if( mouse_y >= 151 && mouse_y <= 260){
                            std::cout<<mouse_y<<std::endl;
                                        cnt++;


                                         deadTime = time;

                        }
                    }

                    if(goLeftOrRight == 0){
                            //mX > .5
                            //mX = (1-mX) + 0.06;
                    }

                  }



              }
		    }

      }

      void drawZombie();
};

    //23800 is scope reach
    #define zomNum 100
    Zombie zom_list[zomNum];
   // Zombie zom_2(1,-23800);




#include "helpers.h"
#include"scenes.h"
#include "draw.h"

#include "keyboardmouse.h"

bool canShoot = true;
void renderScene(void)
{
//
//    if(mouse_x <= 650){
//        glutWarpPointer(1000, mouse_y);
//    }

    //glutWarpPointer(floor(mmmx), 720 / 2 + 135);


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

//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    drawGround();




    glOrtho(-750.0, 750.0, -1300.0, 500.0, -500.0, 500.0); // Changing the coordinate system.


    for(int i = 0; i < zomNum; i++){
        zom_list[i].drawZombie();
    }


    //zom_2.drawZombie();



     tower(0,0,-2200,2000);


    show2D();


}

void gameLoop(void){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


    if(paused == 0){

        for(int i = 0; i < zomNum; i++){
                if(time - newGameTime - (i * 2500) > 0){
                    zom_list[i].zombieMoveSpeed =  4.0;
                }

        }

        renderScene();
    }
    else if(paused == 1){
        drawPauseText();
    }
    else if(paused == 2){
        gameOver();
    }
     else if(paused == 3){
        gameMenu();
    }
    else if(paused == 4){
        highScore();
    }

    glutSwapBuffers();
    glutPostRedisplay();


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

    for(int i = 0; i < zomNum; i++){
        zom_list[i].setup(0,-23500,0.0);
    }


    //glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);

    glutMotionFunc(mouseMotion);
    glutPassiveMotionFunc(mouseMotion);
    glutMouseFunc(mouseClickFunc);

    glutDisplayFunc(gameLoop);
    glutIdleFunc(gameLoop);
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
