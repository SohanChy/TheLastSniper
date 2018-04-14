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

