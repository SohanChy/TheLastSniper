void drawCircle(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_LINE_LOOP);
    for(int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component

        glVertex2f(x + cx, y + cy);//output vertex

    }
    glEnd();
}


void showCrossHair(int sw, int sh)
{


    glColor3f(0.0f, 0.0f, 0.0);
    if(rightMouseButtonDown)
    {
        glLineWidth(1.5);
        glColor3f(1.0f, 0.0f, 0.0);

        glBegin(GL_LINES);
        glVertex2f( sw/2 - 120.0, sh/2);
        glVertex2f( sw/2 + 120.0, sh/2);
        glEnd();

        glBegin(GL_LINES);
        glVertex2f( sw/2, sh/2 - 120.0);
        glVertex2f( sw/2, sh/2 + 120.0);
        glEnd();


        float scopeRadius = 350.0;
        drawCircle(sw/2, sh/2, scopeRadius, 12000);

        //darkness
        glColor3f(0.05f, 0.05f, 0.05);

        glBegin(GL_POLYGON);
        glVertex2f( sw/2 + scopeRadius, 0);
        glVertex2f( sw/2  + scopeRadius, 1500);

        glVertex2f( sw/2  + scopeRadius + 500, 1500);
        glVertex2f( sw/2 + scopeRadius + 500, 0);
        glEnd();


        glBegin(GL_POLYGON);
        glVertex2f( sw/2 - scopeRadius, 0);
        glVertex2f( sw/2  - scopeRadius, 1500);

        glVertex2f( sw/2  - scopeRadius - 500, 1500);
        glVertex2f( sw/2 - scopeRadius - 500, 0);
        glEnd();


        glBegin(GL_POLYGON);
        glVertex2f( 0, 0);
        glVertex2f( 1500, 0);

        glVertex2f( 1500, sh/2 - scopeRadius);
        glVertex2f( 0, sh/2 - scopeRadius);
        glEnd();


        glBegin(GL_POLYGON);
        glVertex2f( 0, 1500);
        glVertex2f( 1500, 1500);

        glVertex2f( 1500, sh/2 + scopeRadius);
        glVertex2f( 0, sh/2 + scopeRadius);
        glEnd();

    }
    else
    {
        glLineWidth(2.0);
        glColor3f(1.0f, 0.0f, 0.0);

        glBegin(GL_LINES);
        glVertex2f( sw/2 - 30.0, sh/2);
        glVertex2f( sw/2 + 30.0, sh/2);
        glEnd();

        glBegin(GL_LINES);
        glVertex2f( sw/2, sh/2 - 30.0);
        glVertex2f( sw/2, sh/2 + 30.0);
        glEnd();

        drawCircle(sw/2, sh/2, 70.0, 4000);
    }




    glutSetCursor(GLUT_CURSOR_NONE);

}

void show2D()
{

    int sw = glutGet(GLUT_WINDOW_WIDTH);
    int sh = glutGet(GLUT_WINDOW_HEIGHT);

    frame++;
    time=glutGet(GLUT_ELAPSED_TIME);
    sprintf(s,"S:%d",time/1000);

    glColor3f(0.0f,1.0f,1.0f);
    setOrthographicProjection();

    glLoadIdentity();
    glPushMatrix();




//glBegin(GL_QUADS);
//    glColor3f(1.0f, 0.0f, 0.0);
//    glVertex2f(0.0, 0.0);
//    glVertex2f(20.0, 0.0);
//    glVertex2f(20.0, 20.0);
//    glVertex2f(0.0, 20.0);
//glEnd();

    glPopMatrix();

    glPushMatrix();

    renderBitmapString(30,15,(void *)font,"The Last Sniper");
    renderBitmapString(30,35,(void *)font,s);
    renderBitmapString(30,55,(void *)font,"Esc - Quit");

    glPopMatrix();




    showCrossHair(sw,sh);

    resetPerspectiveProjection();


}

void zombieShow(float startPosX)
{
    glPushMatrix(); //BODY
    glColor3ub(179,94,116);
    glTranslatef(0.0, 221, startPosX+zMove);
    glRotatef(90, 1.0, 0.0, 0.0);
    GLUquadricObj* body = gluNewQuadric();
    gluQuadricDrawStyle(body, GLU_FILL);
    gluCylinder(body, 80, 120, 300, 30, 30);
    glPopMatrix();



    glPushMatrix(); //LEFT ARM
    glColor3ub(140, 78, 142);
    glTranslatef(-80, 160, startPosX+zMove);
    glRotatef((GLfloat)leftHandAngle, 0.0, -2.0, -15.0);
    glRotatef(-45, 0.0, 1.0, 1.0);

    GLUquadricObj* leftLowerArm = gluNewQuadric();
    gluQuadricDrawStyle(leftLowerArm, GLU_FILL);
    gluCylinder(leftLowerArm, 16, 16, 200, 30, 30);
    glPopMatrix();

    glPushMatrix(); //Right ARM
    glColor3ub(140, 78, 142);
    zMove+=10;
    glTranslatef(120, 160, startPosX+zMove);

    glRotatef(-45, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)rightHandAngle, 0.0, -2.0, -20.0);
    GLUquadricObj* rightUpperArm = gluNewQuadric();
    gluQuadricDrawStyle(rightUpperArm, GLU_FILL);
    gluCylinder(rightUpperArm, 16, 16, 200, 30, 30);
    glPopMatrix();

    zMove-=10;

    glPushMatrix(); //LEFT LEG
    glColor3ub(119, 103, 119);
    glTranslatef(-35, -80, startPosX+zMove);
    glRotatef(-15, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)leftLegAngle, 1.0, 0.0, 0.0);
    GLUquadricObj* leftLeg = gluNewQuadric();
    gluQuadricDrawStyle(leftLeg, GLU_FILL);
    gluCylinder(leftLeg, 36, 16, 400, 30, 30);
    glPopMatrix();

    glPushMatrix(); //RIGHT LEG
    glColor3ub(119, 103, 119);
    glTranslatef(35, -80,  startPosX+zMove);
    glRotatef(15, 0.0, 0.0, 1.0);
    glRotatef((GLfloat)rightLegAngle, 1.0, 0.0, 0.0);
    GLUquadricObj* rightLeg = gluNewQuadric();
    gluQuadricDrawStyle(rightLeg, GLU_FILL);
    gluCylinder(rightLeg, 36, 16, 400, 30, 30);
    glPopMatrix();

    //pa narano
    if (leftLegAngle > 110)
    {
        leftLegMove = -leftLegMove;
    }
    else if (leftLegAngle < 70)
    {
        leftLegMove = -leftLegMove;
    }
    leftLegAngle = int(leftLegAngle + leftLegMove) % 360; // Changing angle of left leg

    if (rightLegAngle > 110)
    {
        rightLegMove = -rightLegMove;
    }
    else if (rightLegAngle < 70)
    {
        rightLegMove = -rightLegMove;
    }
    rightLegAngle = int(rightLegAngle + rightLegMove) % 360; // Changing angle of right leg
    zMove += zombieMoveSpeed; // Moving object on the z-axis

    //hat narano
    // If left mouse clicked right hand of object will shake its lower arm
    if (rightHandAngle >= 225)   // If angle is greater than 225 incrementing degree will become decrement
    {
        rightHandMove = -rightHandMove;
    }
    else if (rightHandAngle <= 135)  // If angle is lower than 135 decrementing degree will become increment
    {
        rightHandMove = -rightHandMove;
    }
    rightHandAngle = (rightHandAngle + rightHandMove) % 360; // changing angle of right hand.

    if (leftHandAngle >= 225)   // If angle is greater than 225 incrementing degree will become decrement
    {
        leftHandMove = -leftHandMove;
    }
    else if (leftHandAngle <= 135)  // If angle is lower than 135 decrementing degree will become increment
    {
        leftHandMove = -leftHandMove;
    }
    leftHandAngle = (leftHandAngle + leftHandAngle) % 360; // changing angle of right hand.


    glPushMatrix(); //NECK
    glColor3ub(145, 129, 145);
    glTranslatef(0.0, 251, startPosX+zMove);
    glRotatef(90, 1.0, 0.0, 0.0);
    GLUquadricObj* neck = gluNewQuadric();
    gluQuadricDrawStyle(neck, GLU_FILL);
    gluCylinder(neck, 20, 20, 30, 30, 30);
    glPopMatrix();

    glPushMatrix(); // HEAD
    glColor3ub(56, 53, 56);
    glPushMatrix();
    glTranslatef(0.0, 350, startPosX+zMove);
    glutSolidSphere(100, 30, 30);
    glPopMatrix();
}



void Zombie::drawZombie()
{
    checkIfAlive();
    if(!alive){
        return;
    }

    int goAngle = -90;
    if(goLeftOrRight == 1)
    {
        goAngle = 90;
    }

    glPushMatrix();

    glRotatef(goAngle,0.0,1.0,0);

    zombieShow(startPosX);
    glPopMatrix();


}

void drawGround()
{
    float worldSize = 200.0;


    // Draw ground
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glColor3f(0.9f, 0.9f, 0.9f);

    glBindTexture ( GL_TEXTURE_2D, sand);


    glBegin(GL_QUADS);

    float textureTiles = 6.0;

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-worldSize, 0.0f, -60.0f);

    glTexCoord2f(textureTiles, 0.0);
    glVertex3f( worldSize, 0.0f, -60.0f);


    glTexCoord2f(textureTiles,textureTiles);
    glVertex3f( worldSize, 0.0f,  60.0f);


    glTexCoord2f(0.0, textureTiles);
    glVertex3f(-worldSize, 0.0f,  60.0f);

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


    /*
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
    */

    //draw sky
    glBindTexture ( GL_TEXTURE_2D, sky);
    //skyTextureTiles = 5.0;
    glColor3ub(132, 179, 255);


    gluSphere( loaded_quad, skySphere, 20, 20);



    //FRONT DEYAL
    glBegin(GL_QUADS);

    glTexCoord2f(0.0, 0.0);

    glVertex3f(-worldSize,0,-100);

    glTexCoord2f(1.0, 0.0);

    glVertex3f(worldSize,0,-100);

    glTexCoord2f(1.0, 1.0);

    glVertex3f(worldSize,80,0);

    glTexCoord2f(0.0, 1.0);

    glVertex3f(-worldSize,80,0);

    glTexCoord2f(0.0, 0.0);

    glEnd();

    //LEFT DEYAL
    glBegin(GL_QUADS);

    glTexCoord2f(0.0, 0.0);

    glVertex3f(-worldSize,0,-100);

    glTexCoord2f(1.0, 0.0);

    glVertex3f(-worldSize,0,100);

    glTexCoord2f(1.0, 1.0);

    glVertex3f(-worldSize,80,100);

    glTexCoord2f(0.0, 1.0);

    glVertex3f(-worldSize,80,-100);

    glTexCoord2f(0.0, 0.0);

    glEnd();



    //RIGHT DEYAL
    glBegin(GL_QUADS);

    glTexCoord2f(0.0, 0.0);

    glVertex3f(worldSize,0,-100);

    glTexCoord2f(1.0, 0.0);

    glVertex3f(worldSize,0,100);

    glTexCoord2f(1.0, 1.0);

    glVertex3f(worldSize,80,100);

    glTexCoord2f(0.0, 1.0);

    glVertex3f(worldSize,80,-100);

    glTexCoord2f(0.0, 0.0);

    glEnd();


}






