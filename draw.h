void drawSnowMan()
{

    glColor3f(1.0f, 1.0f, 1.0f);

    glBindTexture(GL_TEXTURE_2D, zombie);
    loaded_quad = gluNewQuadric();
    gluQuadricTexture( loaded_quad, GL_TRUE);
    gluQuadricDrawStyle(loaded_quad, GLU_FILL);
    gluQuadricNormals(loaded_quad, GLU_SMOOTH);
// Draw Body
    glTranslatef(0.0f,0.75f, 0.0f);
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
    glColor3f(1.0f, 0.5f, 0.5f);
    glRotatef(0.0f,1.0f, 0.0f, 0.0f);
    glutSolidCone(0.08f,0.5f,10,2);
}

void showCrossHair(int sw, int sh)
{

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

void show2D()
{

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
    zMove += legSpeed; // Moving object on the z-axis

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

void drawGround()
{
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




















void tower(double x,double y,double z,int height)//x means front-back,y means up-down,z means left-right
{
        //cout<<"inside tower"<<endl;
        ////////sticks//////////
        glPushMatrix(); //back left
        glTranslatef(x+50,y,z+50);
        glRotatef(270, 1.0, 0.0, 0.0);
        GLUquadricObj* stick = gluNewQuadric();
        gluQuadricDrawStyle(stick, GLU_FILL);
        gluCylinder(stick, 80, 30, height, 30, 30);
        glPopMatrix();

        glPushMatrix(); //back right
        glTranslatef(x+50,y,z+950);
        glRotatef(270, 1.0, 0.0, 0.0);
        GLUquadricObj* stick1 = gluNewQuadric();
        gluQuadricDrawStyle(stick1, GLU_FILL);
        gluCylinder(stick1, 80, 30, height, 30, 30);
        glPopMatrix();


        glPushMatrix(); //front left
        glTranslatef(x+950,y,z+50);
        glRotatef(270, 1.0, 0.0, 0.0);
        GLUquadricObj* stick2 = gluNewQuadric();
        gluQuadricDrawStyle(stick2, GLU_FILL);
        gluCylinder(stick2, 80, 30, height, 30, 30);
        glPopMatrix();


        glPushMatrix(); //front right
        glTranslatef(x+950,y,z+950);
        glRotatef(270, 1.0, 0.0, 0.0);
        GLUquadricObj* stick3 = gluNewQuadric();
        gluQuadricDrawStyle(stick3, GLU_FILL);
        gluCylinder(stick3, 80, 30, height, 30, 30);
        glPopMatrix();


        ////////box/////////
        glPushMatrix(); //
        glColor3ub(64, 132, 108);
        glTranslatef(x+500,y+2000,z+500);
        glutSolidCube(1000);
        glPopMatrix();

}


