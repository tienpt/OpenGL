/* texture2.c
 * by Tom Lassanske (modified by Sumanta)
 *  
 * This program is checker.c modified to use a texture object created
 * from a jpg image (grabbed from the web and then converted to
 * SGI Image rgb format using the O2 mediaconvert tool). 
 * The texture object is created from the rgb image using the 
 * function GetTextureArray().
 * 
 * Note that to compile, you must use the '-limage' compiler option.  
 * You may want to add this to your $c variable declaration in your 
 * .cshrc file 
 */

#include <GL/glut.h>
#include <gl/image.h>
#include <stdlib.h>
#include <stdio.h>

/* data for one texture map */
unsigned char *texImage = NULL;
static GLuint texName;
int height;
int width;

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
  /* specify image file */   
  char imageFile[] = "image1.rgb";
  
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);
  glEnable(GL_DEPTH_TEST);
  
  /*** generate textures *****/
  texImage = GetTextureArray(imageFile, &width, &height);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  glGenTextures(1, &texName);
  glBindTexture(GL_TEXTURE_2D, texName);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  /* Use the following instead of glTexImage() as gluBuild2DMipmaps()
   * scales the image dimensions to the nearest power of 2, 
   * even if the original dimensions were not powers of 2.
   */
  gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height,
		    GL_RGB, GL_UNSIGNED_BYTE, texImage);
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  
  glBegin(GL_QUADS);
  glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -1.0, 0.0);
  glTexCoord2f(0.0, 2.0); glVertex3f(-2.0, 1.0, 0.0);
  glTexCoord2f(2.0, 2.0); glVertex3f(0.0, 1.0, 0.0);
  glTexCoord2f(2.0, 0.0); glVertex3f(0.0, -1.0, 0.0);
  
  glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, 0.0);
  glTexCoord2f(0.0, 1.0); glVertex3f(1.0, 1.0, 0.0);
  glTexCoord2f(1.0, 1.0); glVertex3f(2.41421, 1.0, -1.41421);
  glTexCoord2f(1.0, 0.0); glVertex3f(2.41421, -1.0, -1.41421);
  glEnd();
  glFlush();
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
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
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

