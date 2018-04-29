void drawPauseText(){

    int sw = glutGet(GLUT_WINDOW_WIDTH);
    int sh = glutGet(GLUT_WINDOW_HEIGHT);

    glColor3f(1.0f,0.0f,0.0f);
    setOrthographicProjection();

    glLoadIdentity();
    glPushMatrix();

    renderBitmapString(sw/2 - 110,sh/2 + 70,GLUT_BITMAP_HELVETICA_18,"Paused! Press 'R' to Resume.");

    glPopMatrix();

    resetPerspectiveProjection();


}
#include"objlocs.h"


void gameOver(){

 int sw = glutGet(GLUT_WINDOW_WIDTH);
    int sh = glutGet(GLUT_WINDOW_HEIGHT);

    glColor3f(1.0f,0.0f,0.0f);
    setOrthographicProjection();

    glLoadIdentity();
    glPushMatrix();


    renderBitmapString(sw/2 - 110,sh/2 + 70,GLUT_BITMAP_TIMES_ROMAN_24,"Game Over");

    glPopMatrix();

      glPushMatrix();

      sprintf(s,"Your Score: %d",(time - newGameTime)/1000);
    renderBitmapString(sw/2 - 110,sh/2 - 20,GLUT_BITMAP_TIMES_ROMAN_24,s);

    renderBitmapString(sw/2 - 110,sh/2 - 170,GLUT_BITMAP_HELVETICA_18,"Press 'H' to see HighScore");


    glPopMatrix();

    resetPerspectiveProjection();

}

void gameMenu(){


    int sw = glutGet(GLUT_WINDOW_WIDTH);
    int sh = glutGet(GLUT_WINDOW_HEIGHT);

    glutSetCursor(GLUT_CURSOR_CROSSHAIR);
    //CHANGE STATE
    if(leftMouseButtonDown){

        if(mouse_x >= sw/2 - 130 && mouse_x <= sw/2 - 20){
            if(mouse_y >= sh/2 + 50 && mouse_y <= sh/2 + 50 + 25){
                paused = 0;
                newGameTime = time;
                glutWarpPointer(1000 , 720 / 2);
                time = 0;

                 for(int i = 0; i < zomNum; i++){
                        Zombie zomb;
                    zom_list[i] = zomb;
                    zom_list[i].setup(0,-23500,0.0);
                 }


            }
        }


         if(mouse_x >= sw/2 - 130 && mouse_x <= sw/2 - 20){
            if(mouse_y >= sh/2 - 60 && mouse_y <= sh/2 - 40 ){
                paused = 4;
            }
        }


        //cout<<mouse_x <<": "<<mouse_y<<endl;

    }


    glColor3f(1.0f,0.0f,0.0f);
    setOrthographicProjection();

    glLoadIdentity();
    glPushMatrix();

    renderBitmapString(sw/2 - 130,sh/2 + 50,GLUT_BITMAP_TIMES_ROMAN_24,"New Game");
    renderBitmapString(sw/2 - 130,sh/2 - 60,GLUT_BITMAP_TIMES_ROMAN_24,"High Score");

    glPopMatrix();



    resetPerspectiveProjection();

}

void highScore(){

    int sw = glutGet(GLUT_WINDOW_WIDTH);
    int sh = glutGet(GLUT_WINDOW_HEIGHT);


    glColor3f(1.0f,0.0f,0.0f);
    setOrthographicProjection();

    glLoadIdentity();

    //CHANGE STATE
    if(leftMouseButtonDown){

        if(mouse_x >= sw/2 + 200 && mouse_x <= sw/2 + 200 + 48){
            if(mouse_y >= sh/2 - 300 && mouse_y <= sh/2 - 300 + 24 ){
                paused = 3;
            }
       }

       //cout<<mouse_x<<": "<<mouse_y<<endl;

}
       glPushMatrix();
        renderBitmapString(sw/2 + 200,sh/2 - 300,GLUT_BITMAP_TIMES_ROMAN_24,"Back");
        glPopMatrix();


    glPushMatrix();
    renderBitmapString(sw/2 - 130,sh/2 + 130,GLUT_BITMAP_TIMES_ROMAN_24,"High Score");

   for(int i = 0; i < 5; i++){


    int sw = glutGet(GLUT_WINDOW_WIDTH);
    int sh = glutGet(GLUT_WINDOW_HEIGHT);

    getTopScores();

    glutSetCursor(GLUT_CURSOR_CROSSHAIR);
        char showwww[12];

        std::string ranking;
        std::stringstream ss;
        ss << i+1;

        std::string temp = score[i];

        temp = ss.str() + ". " + temp;
        strcpy(showwww, temp.c_str());
        //cout<<temp;
        renderBitmapString(sw/2 - 95,sh/2 + 80 - i*30,GLUT_BITMAP_TIMES_ROMAN_24,showwww);

   }

    glPopMatrix();



resetPerspectiveProjection();
}


