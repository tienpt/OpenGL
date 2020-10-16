/*
 * textured-torus.c
 * by Sumanta
 * Think of this program simply as
 * cylinder2.c + checker.c
 *
 * NOTE:
 * Refer to both cylinder2.c and checker.c for comments 
 * in either program.
 */

/* Use the x, X, y, Y, z, Z keys to turn the cylinder. */

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
 
#define PI 3.14159265358979324

#define M  25  
#define N  15

/*	Create checkerboard texture	*/
#define	checkImageWidth 64
#define	checkImageHeight 64
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];

#ifdef GL_VERSION_1_1
static GLuint texName;
#endif

void makeCheckImage(void)
{
   int i, j, c;
    
   for (i = 0; i < checkImageHeight; i++) {
      for (j = 0; j < checkImageWidth; j++) {
         c = ((((i&0x8)==0)^((j&0x8))==0))*255;
         checkImage[i][j][0] = (GLubyte) c;
         checkImage[i][j][1] = (GLubyte) c;
         checkImage[i][j][2] = (GLubyte) c;
         checkImage[i][j][3] = (GLubyte) 255;
      }
   }
}

/* The parametrizing fuctions FNX(i,j), FNY(i,j), FNZ(i,j) are chosen to
 * map the parameter space to a torus.
 */
GLfloat FNX(int i, int j)
{
   return (1 + 0.5 * cos( (float) i/M  * 2 * PI ) ) * cos( (float) j/N  * 2 * PI );
}

GLfloat FNY(int i, int j)
{
   return (1 + 0.5 * cos( (float) i/M  * 2 * PI ) ) * sin( (float) j/N  * 2 * PI );
}

GLfloat FNZ(int i, int j)
{
   return 0.5 * sin( (float) i/M  * 2 * PI );
}

// The vertex array.
static GLfloat vdata[3*(M+1)*(N+1)];

// The texture co-ordinates array.
static GLfloat texdata[2*(M+1)*(N+1)];

// Angles used to rotate the cylinder with keyboard entry.
static int Xangle = 0, Yangle = 0, Zangle = 0;

// Most of init is copied verbatim from checker.c. In addition
// there is a loop to fill the vertex and texture co-ordinates array.
void init (void) 
{
  int i, j, k, l;

  glClearColor (0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);
  glEnable(GL_DEPTH_TEST);

   makeCheckImage();
   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

#ifdef GL_VERSION_1_1
   glGenTextures(1, &texName);
   glBindTexture(GL_TEXTURE_2D, texName);
#endif

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
#ifdef GL_VERSION_1_1
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth, checkImageHeight, 
                0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
#else
   glTexImage2D(GL_TEXTURE_2D, 0, 4, checkImageWidth, checkImageHeight, 
                0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
#endif

  k = 0;
  l = 0;
  for (j = 0; j <= N; j++)
    for (i = 0; i <= M; i++){

      /* The vertex array is filled. */
      vdata[k++] = FNX(i,j); 
      vdata[k++] = FNY(i,j);
      vdata[k++] = FNZ(i,j); 

      /* Filling the texture co-ordinates array:
       * The parameter space is a unit square with corners at (0,0) and (1,1)
       * so that the both the parameter space x and y co-ordinates run from 
       * 0 to 1. But this is *identical* to s and t co-ordinate ranges for the 
       * texture object. So we simply provide the grid point (s,t) in the 
       * parameter space (or more accurately the torus point to which it is 
       * mapped) the texture co-ordinates (s,t) as well.
       */
      texdata[l++] = (GLfloat) i/M;
      texdata[l++] = (GLfloat) j/N;
	}  

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  glVertexPointer(3, GL_FLOAT, 0, vdata);
  glTexCoordPointer(2, GL_FLOAT, 0, texdata);
}

void display(void)
{
   int  i, j;
  
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glColor3f (1.0, 1.0, 1.0);
  
   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
#ifdef GL_VERSION_1_1
   glBindTexture(GL_TEXTURE_2D, texName);
#endif

   glRotatef ((GLfloat) Zangle, 0.0, 0.0, 1.0);
   glRotatef ((GLfloat) Yangle, 0.0, 1.0, 0.0);
   glRotatef ((GLfloat) Xangle, 1.0, 0.0, 0.0);

   for(j = 0; j < N; j++){
     glBegin(GL_TRIANGLE_STRIP);
     for(i = 0; i <= M; i++){
       glArrayElement( j*(M+1) + i );
       glArrayElement( (j+1)*(M+1) + i );
     }
   glEnd();
   }

  glutSwapBuffers();
  glFlush ();

  glDisable(GL_TEXTURE_2D);
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (0.0, 0.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 'x':
         Xangle = (Xangle + 5) % 360;
         glutPostRedisplay();
         break;
      case 'X':
         Xangle = (Xangle - 5) % 360;
         glutPostRedisplay();
         break;
      case 'y':
         Yangle = (Yangle + 5) % 360;
         glutPostRedisplay();
         break;
      case 'Y':
         Yangle = (Yangle - 5) % 360;
         glutPostRedisplay();
         break;
      case 'z':
         Zangle = (Zangle + 5) % 360;
         glutPostRedisplay();
         break;
      case 'Z':
         Zangle = (Zangle - 5) % 360;
         glutPostRedisplay();
         break;
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
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("textured-torus");
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;  
}
