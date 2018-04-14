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

void initWindow();

GLUquadric *loaded_quad;
GLuint grass,sky,zombie;

int LoadBitmap(char *filename)
{
    FILE * file;
    char temp;
    long i;

    BITMAPINFOHEADER infoheader;
    unsigned char *infoheader_data;

    GLuint num_texture;

    if( (file = fopen(filename, "rb"))==NULL) return (-1); // Open the file for reading

    fseek(file, 18, SEEK_CUR);  /* start reading width & height */
    fread(&infoheader.biWidth, sizeof(int), 1, file);

    fread(&infoheader.biHeight, sizeof(int), 1, file);

    fread(&infoheader.biPlanes, sizeof(short int), 1, file);
    if (infoheader.biPlanes != 1) {
      printf("Planes from %s is not 1: %u\n", filename, infoheader.biPlanes);
      return 0;
    }

    // read the bpp
    fread(&infoheader.biBitCount, sizeof(unsigned short int), 1, file);
    if (infoheader.biBitCount != 24) {
      printf("Bpp from %s is not 24: %d\n", filename, infoheader.biBitCount);
      return 0;
    }

    fseek(file, 24, SEEK_CUR);

    // read the data
    if(infoheader.biWidth<0){
  infoheader.biWidth = -infoheader.biWidth;
    }
    if(infoheader.biHeight<0){
  infoheader.biHeight = -infoheader.biHeight;
    }
    infoheader_data = (unsigned char *) malloc(infoheader.biWidth * infoheader.biHeight * 3);
    if (infoheader_data == NULL) {
      printf("Error allocating memory for color-corrected image data\n");
      return 0;
    }

    if ((i = fread(infoheader_data, infoheader.biWidth * infoheader.biHeight * 3, 1, file)) != 1) {
      printf("Error reading image data from %s.\n", filename);
      return 0;
    }

    for (i=0; i<(infoheader.biWidth * infoheader.biHeight * 3); i+=3) { // reverse all of the colors. (bgr -> rgb)
      temp = infoheader_data[i];
      infoheader_data[i] = infoheader_data[i+2];
      infoheader_data[i+2] = temp;
    }


    fclose(file); // Closes the file stream

    glGenTextures(1, &num_texture);
    glBindTexture(GL_TEXTURE_2D, num_texture); // Bind the ID texture specified by the 2nd parameter

    // The next commands sets the texture parameters
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // If the u,v coordinates overflow the range 0,1 the image is repeated
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // The magnification function ("linear" produces better results)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); //The minifying function

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // Finally we define the 2d texture
    glTexImage2D(GL_TEXTURE_2D, 0, 3, infoheader.biWidth, infoheader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, infoheader_data);

    // And create 2d mipmaps for the minifying function
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, infoheader.biWidth, infoheader.biHeight, GL_RGB, GL_UNSIGNED_BYTE, infoheader_data);

    free(infoheader_data); // Free the memory we used to load the texture

    return (num_texture); // Returns the current texture OpenGL ID
}


void changeSize(int w1, int h1)
 {

 // Prevent a divide by zero, when window is too short
 // (you cant make a window of zero width).
 if(h1 == 0)
  h1 = 1;

 w = w1;
 h = h1;
 ratio = 1.0f * w / h;
 // Reset the coordinate system before modifying
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();

 // Set the viewport to be the entire window
 glViewport(0, 0, w, h);

 // Set the clipping volume
//std::cout<<zoom;
 gluPerspective(zoom,ratio,0.1,1000);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
// std::cout<<ly<<std::endl;
 gluLookAt(x, y, z,
        x + lx,y + ly,z + lz,
     0.0f,1.0f,0.0f);
}



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


 void zombieShow()
 {
         glPushMatrix(); //BODY
         glColor3ub(179,94,116);
         glTranslatef(0.0, 221, zMove);
         glRotatef(90, 1.0, 0.0, 0.0);
         GLUquadricObj* body = gluNewQuadric();
         gluQuadricDrawStyle(body, GLU_FILL);
         gluCylinder(body, 80, 120, 300, 30, 30);
         glPopMatrix();



         glPushMatrix(); //LEFT ARM
         glColor3ub(140, 78, 142);
         glTranslatef(-80, 160, zMove);
          glRotatef((GLfloat)leftHandAngle, 0.0, -2.0, -15.0);
         glRotatef(-45, 0.0, 1.0, 1.0);

         GLUquadricObj* leftLowerArm = gluNewQuadric();
         gluQuadricDrawStyle(leftLowerArm, GLU_FILL);
         gluCylinder(leftLowerArm, 16, 16, 200, 30, 30);
         glPopMatrix();

         glPushMatrix(); //Right ARM
         glColor3ub(140, 78, 142);
         zMove+=10;
         glTranslatef(120, 160, zMove);

         glRotatef(-45, 0.0, 0.0, 1.0);
         glRotatef((GLfloat)rightHandAngle, 0.0, -2.0, -20.0);
         GLUquadricObj* rightUpperArm = gluNewQuadric();
         gluQuadricDrawStyle(rightUpperArm, GLU_FILL);
         gluCylinder(rightUpperArm, 16, 16, 200, 30, 30);
         glPopMatrix();

        zMove-=10;

         glPushMatrix(); //LEFT LEG
         glColor3ub(119, 103, 119);
         glTranslatef(-35, -80, zMove);
         glRotatef(-15, 0.0, 0.0, 1.0);
         glRotatef((GLfloat)leftLegAngle, 1.0, 0.0, 0.0);
         GLUquadricObj* leftLeg = gluNewQuadric();
         gluQuadricDrawStyle(leftLeg, GLU_FILL);
         gluCylinder(leftLeg, 36, 16, 400, 30, 30);
         glPopMatrix();

         glPushMatrix(); //RIGHT LEG
         glColor3ub(119, 103, 119);
         glTranslatef(35, -80, zMove);
         glRotatef(15, 0.0, 0.0, 1.0);
         glRotatef((GLfloat)rightLegAngle, 1.0, 0.0, 0.0);
         GLUquadricObj* rightLeg = gluNewQuadric();
         gluQuadricDrawStyle(rightLeg, GLU_FILL);
         gluCylinder(rightLeg, 36, 16, 400, 30, 30);
         glPopMatrix();

         //pa narano
         if (leftLegAngle > 110){
                 leftLegMove = -leftLegMove;
             }
             else if (leftLegAngle < 70){
                 leftLegMove = -leftLegMove;
             }
             leftLegAngle = int(leftLegAngle + leftLegMove) % 360; // Changing angle of left leg

             if (rightLegAngle > 110) {
                 rightLegMove = -rightLegMove;
             }
             else if (rightLegAngle < 70){
                 rightLegMove = -rightLegMove;
             }
             rightLegAngle = int(rightLegAngle + rightLegMove) % 360; // Changing angle of right leg
             zMove += legSpeed; // Moving object on the z-axis

             //hat narano
              // If left mouse clicked right hand of object will shake its lower arm
             if (rightHandAngle >= 225) { // If angle is greater than 225 incrementing degree will become decrement
                 rightHandMove = -rightHandMove;
             }
             else if (rightHandAngle <= 135){ // If angle is lower than 135 decrementing degree will become increment
                 rightHandMove = -rightHandMove;
             }
             rightHandAngle = (rightHandAngle + rightHandMove) % 360; // changing angle of right hand.

             if (leftHandAngle >= 225) { // If angle is greater than 225 incrementing degree will become decrement
                 leftHandMove = -leftHandMove;
             }
             else if (leftHandAngle <= 135){ // If angle is lower than 135 decrementing degree will become increment
                 leftHandMove = -leftHandMove;
             }
             leftHandAngle = (leftHandAngle + leftHandAngle) % 360; // changing angle of right hand.


         glPushMatrix(); //NECK
         glColor3ub(145, 129, 145);
         glTranslatef(0.0, 251, zMove);
         glRotatef(90, 1.0, 0.0, 0.0);
         GLUquadricObj* neck = gluNewQuadric();
         gluQuadricDrawStyle(neck, GLU_FILL);
         gluCylinder(neck, 20, 20, 30, 30, 30);
         glPopMatrix();

         glPushMatrix(); // HEAD
         glColor3ub(56, 53, 56);
         glPushMatrix();
         glTranslatef(0.0, 350, zMove);
         glutSolidSphere(100, 30, 30);
         glPopMatrix();
 }





void drawSnowMan() {

 glColor3f(1.0f, 1.0f, 1.0f);

  glBindTexture(GL_TEXTURE_2D, zombie);
  loaded_quad = gluNewQuadric();
  gluQuadricTexture( loaded_quad, GL_TRUE);
  gluQuadricDrawStyle(loaded_quad, GLU_FILL);
  gluQuadricNormals(loaded_quad, GLU_SMOOTH);
// Draw Body
 glTranslatef(0.0f ,0.75f, 0.0f);
 gluSphere( loaded_quad, 0.75f, 20, 20);

// Draw Head
 glTranslatef(0.0f, 1.0f, 0.0f);
 glutSolidSphere(0.25f,20,20);

// Draw Eyes
 glPushMatrix();
 glColor3f(0.0f,0.0f,0.0f);
 glTranslatef(0.05f, 0.10f, 0.18f);
 glutSolidSphere(0.05f,10,10);
 glTranslatef(-0.1f, 0.0f, 0.0f);
 glutSolidSphere(0.05f,10,10);
 glPopMatrix();

// Draw Nose
 glColor3f(1.0f, 0.5f , 0.5f);
 glRotatef(0.0f,1.0f, 0.0f, 0.0f);
 glutSolidCone(0.08f,0.5f,10,2);
}



GLuint createDL() {
 GLuint snowManDL;

 // Create the id for the list
 snowManDL = glGenLists(2);

 glNewList(snowManDL+1,GL_COMPILE);

//  drawSnowMan();
 glEndList();
 // start list
 glNewList(snowManDL,GL_COMPILE);

 // call the function that contains the rendering commands
 for(int i = -3; i < 3; i++)
  for(int j=-3; j < 3; j++) {
   glPushMatrix();
   glTranslatef(i*10.0,0,j * 10.0);
   glCallList(snowManDL+1);
   glPopMatrix();
  }

 // endList
 glEndList();

 return(snowManDL);
}

void initScene() {

 glEnable(GL_DEPTH_TEST);
 snowman_display_list = createDL();

}

void orientMe(float ang) {
 lx = sin(ang);
 lz = -cos(ang);
 glLoadIdentity();
 gluLookAt(x, y, z,
        x + lx,y + ly,z + lz,
     0.0f,1.0f,0.0f);
}


void moveMeFlat(int i) {
 x = x + i*(lx)*0.1;
 z = z + i*(lz)*0.1;
 glLoadIdentity();
 gluLookAt(x, y, z,
        x + lx,y + ly,z + lz,
     0.0f,1.0f,0.0f);
}

void setOrthographicProjection() {

 // switch to projection mode
 glMatrixMode(GL_PROJECTION);
 // save previous matrix which contains the
 //settings for the perspective projection
 glPushMatrix();
 // reset matrix
 glLoadIdentity();
 // set a 2D orthographic projection
 gluOrtho2D(0, w, 0, h);
 // invert the y axis, down is positive
 //glScalef(1, -1, 1);
 // mover the origin from the bottom left corner
 // to the upper left corner
 //glTranslatef(0, -h, 0);
 glMatrixMode(GL_MODELVIEW);
}

void resetPerspectiveProjection() {
 // set the current matrix to GL_PROJECTION
 glMatrixMode(GL_PROJECTION);
 // restore previous settings
 glPopMatrix();
 // get back to GL_MODELVIEW matrix
 glMatrixMode(GL_MODELVIEW);
}

void renderBitmapString(float x, float y, void *font,char *string)
{

  char *c;
  // set position to start drawing fonts
  glRasterPos2f(x, y);
  // loop all the characters in the string
  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter(font, *c);
  }
}



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

void mouseMotion(int x, int y)
{
    int wh = glutGet(GLUT_WINDOW_HEIGHT);
    int ww = glutGet(GLUT_WINDOW_WIDTH);

    y = (wh-y);

    mouse_x = (float) x ;
    mouse_y = (float) y ;

    xAngle = 1.20 * (mouse_x / ww) - 0.6;
    yAngle = 0.30 * (mouse_y / wh) - 0.15;
    ly = yAngle;

  // std::cout<<"x "<<x<<std::endl;
   //std::cout<<"y "<<y<<std::endl;
}


void showCrossHair(int sw, int sh){

glColor3f(1.0f, 0.0f, 0.0);

glLineWidth(2.5);
glColor3f(1.0f, 0.0f, 0.0);

glBegin(GL_LINES);
    glVertex2f( sw/2 - 20.0, sh/2);
    glVertex2f( sw/2 + 20.0, sh/2);
glEnd();

glBegin(GL_LINES);
    glVertex2f( sw/2, sh/2 - 20.0);
    glVertex2f( sw/2, sh/2 + 20.0);
glEnd();


glutSetCursor(GLUT_CURSOR_NONE);

}

void show2D(){

int sw = glutGet(GLUT_WINDOW_WIDTH);
int sh = glutGet(GLUT_WINDOW_HEIGHT);

     frame++;
 time=glutGet(GLUT_ELAPSED_TIME);
 sprintf(s,"S:%d",time/1000);

 glColor3f(0.0f,1.0f,1.0f);
 setOrthographicProjection();

 glPushMatrix();
 glLoadIdentity();

 showCrossHair(sw,sh);

//glBegin(GL_QUADS);
//    glColor3f(1.0f, 0.0f, 0.0);
//    glVertex2f(0.0, 0.0);
//    glVertex2f(20.0, 0.0);
//    glVertex2f(20.0, 20.0);
//    glVertex2f(0.0, 20.0);
//glEnd();

glPopMatrix();

 glPushMatrix();
 glLoadIdentity();

 renderBitmapString(30,15,(void *)font,"The Last Sniper");
 renderBitmapString(30,35,(void *)font,s);
 renderBitmapString(30,55,(void *)font,"Esc - Quit");

 glPopMatrix();



 resetPerspectiveProjection();


}


void processNormalKeys(unsigned char key, int x, int y) {

 if (key == 27)
  exit(0);
}

void pressKey(int key, int x, int y) {

std::cout<<angle<<std::endl;

 switch (key) {
  case GLUT_KEY_LEFT : deltaAngle = -0.01f;break;
  case GLUT_KEY_RIGHT : deltaAngle = 0.01f;break;
  case GLUT_KEY_UP : deltaMove = 1;break;
  case GLUT_KEY_DOWN : deltaMove = -1;break;
 }

}

void releaseKey(int key, int x, int y) {

 switch (key) {
  case GLUT_KEY_LEFT : if (deltaAngle < 0.0f)
         deltaAngle = 0.0f;
        break;
  case GLUT_KEY_RIGHT : if (deltaAngle > 0.0f)
         deltaAngle = 0.0f;
        break;
  case GLUT_KEY_UP :  if (deltaMove > 0)
         deltaMove = 0;
        break;
  case GLUT_KEY_DOWN : if (deltaMove < 0)
         deltaMove = 0;
        break;
 }
}


void drawGround(){
    // Draw ground
  glMatrixMode(GL_MODELVIEW);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glColor3f(0.9f, 0.9f, 0.9f);

  glBindTexture ( GL_TEXTURE_2D, grass);
  float textureTiles = 10.0;

  glBegin(GL_QUADS);
  glTexCoord2f(0.0, textureTiles);
  glVertex3f(-100.0f, 0.0f, -100.0f);
  glTexCoord2f(textureTiles, 0.0);
  glVertex3f(-100.0f, 0.0f,  100.0f);
  glTexCoord2f(textureTiles, textureTiles);
  glVertex3f( 100.0f, 0.0f,  100.0f);
  glTexCoord2f(0.0, 0.0);
  glVertex3f( 100.0f, 0.0f, -100.0f);
  glEnd();




  //X is RED
    //Y IS PINK
    //Z is BLUE


    glBegin(GL_LINES);
        //X-Axis
        glColor3ub(255,0,0);
        glVertex3f(1,2,0);
        glVertex3f(2,2,0);

        //Z-Axis
        glColor3ub(0,0,255);
        glVertex3f(1,2,0);
        glVertex3f(1,2,1);

        //Y-Axis

        glColor3ub(255,0,255);
        glVertex3f(1,2,0);
        glVertex3f(1,3,0);

    glEnd();


  glBegin(GL_QUADS);
  glTexCoord2f(0.0, textureTiles);
  glVertex3f(-100.0f, 0.0f, -100.0f);
  glTexCoord2f(textureTiles, 0.0);
  glVertex3f(-100.0f, 0.0f,  100.0f);
  glTexCoord2f(textureTiles, textureTiles);
  glVertex3f( 100.0f, 0.0f,  100.0f);
  glTexCoord2f(0.0, 0.0);
  glVertex3f( 100.0f, 0.0f, -100.0f);
  glEnd();


  //draw sky
  glBindTexture ( GL_TEXTURE_2D, sky);
  //skyTextureTiles = 5.0;
  glColor3ub(132, 179, 255);



   //FRONT DEYAL
    glBegin(GL_QUADS);

    glTexCoord2f(0.0, 0.0);

    glVertex3f(-250,0,-100);

    glTexCoord2f(1.0, 0.0);

    glVertex3f(250,0,-100);

    glTexCoord2f(1.0, 1.0);

    glVertex3f(250,80,0);

    glTexCoord2f(0.0, 1.0);

    glVertex3f(-250,80,0);

    glTexCoord2f(0.0, 0.0);

    glEnd();


}




void renderScene(void) {

    int wh = glutGet(GLUT_WINDOW_HEIGHT);
    int ww = glutGet(GLUT_WINDOW_WIDTH);

 if(rightMouseButtonDown){
        zoom = 10;
        changeSize(ww,wh);
 }
 else {
     zoom = 45;
     changeSize(ww,wh);
 }


 if (deltaMove)
  moveMeFlat(deltaMove);
 if (deltaAngle) {
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
 glPopMatrix();



 show2D();




 glutSwapBuffers();
}

void initWindow() {
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
