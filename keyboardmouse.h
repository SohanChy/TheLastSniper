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

void mouseMotion(int x, int y)
{
    int wh = glutGet(GLUT_WINDOW_HEIGHT);
    int ww = glutGet(GLUT_WINDOW_WIDTH);

    y = (wh-y);

    mouse_x = (float) x ;
    mouse_y = (float) y ;

    xAngle = 1.80 * (mouse_x / ww) - 0.9;   //0.6 is X camera freedom
    yAngle = 0.30 * (mouse_y / wh) - 0.15;   //0.15 is Y camera
    ly = yAngle;

  // std::cout<<"x "<<x<<std::endl;
   //std::cout<<"y "<<y<<std::endl;
}

void processNormalKeys(unsigned char key, int x, int y) {

 if (key == 27){
    exit(0);
 }
 else if(key == 98){
     if(zombieMoveSpeed != 0){
        zombieMoveSpeed = 0;
     }
     else zombieMoveSpeed = 7.5f;

        //b key to experiment
        //textureTiles = textureTiles + 1;

}

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
