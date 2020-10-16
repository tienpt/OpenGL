/* texture3.c
 * by Tom Lassanske (modified by Sumanta)
 *
 * This program is similar to texture2.c, except that
 * two rgb images are read in and applied to two rectangles.
 * 
 * Note that to compile, you must use the '-limage' compiler option.  
 * You may want to add this to your $c variable declaration in your 
 * .cshrc file 
 */

#include <GL/glut.h>
#include <gl/image.h>
#include <stdlib.h>
#include <stdio.h>

/* data for two texture maps */
unsigned char *texImage[2] = {NULL, NULL};
GLuint texName[2];
int height[2];
int width[2];

/* function that creates the texture object from the rgb image */
unsigned char *GetTextureArray(char file_name[], int *w, int *h)
/* modified from a program by Paul Haeberli, SGI */
{
  unsigned char *new_image;
  IMAGE *image;
  int x, y, z, i;
  short *cbuf[3];
  
  /* open the image file */
  if( (image=iopen(file_name, "r")) == NULL ) {
    fprintf(stderr,"readimage: can't open input file %s\n", file_name);
    exit(1);
  }
  
  /* check if image file is RGB */
  if(image->zsize != 3) {  /* if the image has alpha zsize is 4 */
    fprintf(stderr,"readimage: input file is not RGB\n");
    exit(1);
  }

  /* update the width and height pointer values */
  *w  = image->xsize; 
  *h  = image->ysize;

  /* allocate buffers for temporary image data */
  for (i=0; i<3; i++)
    cbuf[i] = (short *) malloc((*w)*sizeof(short));
  
  /* allocate memory for the texture map */
  new_image = (unsigned char *) malloc((*h)*(*w)*3);

  /* store pixel data */
  z = 0;
  for(y=0; y<(*h); y++) {
    for (i=0; i<3; i++)
      getrow(image,cbuf[i],y,i);
    for(x=0; x<(*w); x++)
      for (i=0; i<3; i++)
	new_image[z++] = (unsigned char) cbuf[i][x];
  }
  
  /* free the temporary buffers & close input file */
  for (i=0; i<3; i++)
    free (cbuf[i]);
  iclose(image);

  return new_image;
}

void init(void)
{    
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);
  glEnable(GL_DEPTH_TEST);
  
  /*** generate textures *****/
  texImage[0] = GetTextureArray("emsBldg.rgb", &width[0], &height[0]);
  texImage[1] = GetTextureArray("bridge.rgb", &width[1], &height[1]);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  glGenTextures(2, texName);

  glBindTexture(GL_TEXTURE_2D, texName[0]);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width[0], height[0],
		    GL_RGB, GL_UNSIGNED_BYTE, texImage[0]);  

  glBindTexture(GL_TEXTURE_2D, texName[1]);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width[1], height[1],
		    GL_RGB, GL_UNSIGNED_BYTE, texImage[1]);  
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

  glBindTexture(GL_TEXTURE_2D, texName[0]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -1.0, 0.0);
  glTexCoord2f(0.0, 1.0); glVertex3f(-2.0, 1.0, 0.0);
  glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 1.0, 0.0);
  glTexCoord2f(1.0, 0.0); glVertex3f(0.0, -1.0, 0.0);
  glEnd();

  glBindTexture(GL_TEXTURE_2D, texName[1]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, 0.0);
  glTexCoord2f(0.0, 1.0); glVertex3f(1.0, 1.0, 0.0);
  glTexCoord2f(1.0, 1.0); glVertex3f(2.41421, 1.0, -1.41421);
  glTexCoord2f(1.0, 0.0); glVertex3f(2.41421, -1.0, -1.41421);
  glEnd();
  glFlush();

  /* NOTE the following: it is essential! Buffers need to be
   * swapped to replace the contents from what was written
   * by the GetTextureArray() routine.
   */
  glutSwapBuffers();

  glDisable(GL_TEXTURE_2D);
}

void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 30.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, -3.6);
}

void keyboard (unsigned char key, int x, int y)
{
  switch (key) {
  case 27:
    exit(0);
    break;
  default:
    break;
  }
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(250, 250);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0; 
}
