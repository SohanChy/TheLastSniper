using namespace std;


float lastShot = time - 3500;
void mouseClickFunc(int button, int state, int x, int y)
{
    // Save the left button state
    if (button == GLUT_LEFT_BUTTON)
    {
        if(paused == 0){
            if( time - lastShot > 3800 ){
                //std::cout<<time - lastShot<<std::endl;
                if((state == GLUT_UP)){
                    lastShot = time;
                    sndPlaySound("shoot.wav",SND_ASYNC);
                }
                leftMouseButtonDown = (state == GLUT_DOWN);
            }
            else {
                sndPlaySound("jam.wav",SND_ASYNC);
            }

        }
        else {
            leftMouseButtonDown = (state == GLUT_DOWN);
        }



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

    if(1.80 * (mouse_x / ww) - 0.9 > 0){
        xAngle = 1.80 * (mouse_x / ww) - 0.9;   //0.9 is X camera freedom
    }

    yAngle = 0.30 * (mouse_y / wh) - 0.15;   //0.15 is Y camera
    ly = yAngle;

  // std::cout<<"x "<<x<<std::endl;
   //std::cout<<"y "<<y<<std::endl;
}


void proceed()  {
    glutPostRedisplay();
}

void processNormalKeys(unsigned char key, int x, int y) {

     if (key == 27){
        exit(0);
     }
     else if(key == 98){
            //b key to experiment
            //textureTiles = textureTiles + 1;
    }


    if(key == 'p' || key == 'P'){
        pausedTime = glutGet(GLUT_ELAPSED_TIME);
        std::cout<<paused<<endl;
        paused = 1;
	}
	else if(key == 'r' || key == 'R')	{
		paused = 0;
        std::cout<<paused<<endl;
	}
	else if(key == 'q' || key == 'Q')	{
		paused = 2;
        std::cout<<"Game over"<<endl;
	}

	else if(key == 'n' || key == 'N')	{
		paused = 3;
        std::cout<<"New Game"<<endl;
	}
    else if(key == 'h' || key == 'H')	{
		paused = 4;
        std::cout<<"High Score"<<endl;
	}
	else if(key == 's' || key == 'S')	{

	}


}

void pressKey(int key, int x, int y) {

std::cout<<angle<<std::endl;

 switch (key) {
//  case GLUT_KEY_LEFT : deltaAngle = -0.01f;break;
//  case GLUT_KEY_RIGHT : deltaAngle = 0.01f;break;
//  case GLUT_KEY_UP : deltaMove = 1;break;
//  case GLUT_KEY_DOWN : deltaMove = -1;break;
 }

}

void releaseKey(int key, int x, int y) {

 switch (key) {
//  case GLUT_KEY_LEFT : if (deltaAngle < 0.0f)
//         deltaAngle = 0.0f;
//        break;
//  case GLUT_KEY_RIGHT : if (deltaAngle > 0.0f)
//         deltaAngle = 0.0f;
//        break;
//  case GLUT_KEY_UP :  if (deltaMove > 0)
//         deltaMove = 0;
//        break;
//  case GLUT_KEY_DOWN : if (deltaMove < 0)
//         deltaMove = 0;
//        break;
 }
}



