/*
 * turn-textured-torus.c
 * by Sumanta
 * This is textured-torus.c modified
 * so that the texture co-ordinates change
 * creating the illusion that the torus is turning.
 *
 * NOTE: Refer first to textured-torus.c.  
 */

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
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

GLfloat incr = 0;

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

// Most of init is copied verbatim from checker.c. In addition
// there is a loop to fill the vertex and texture co-ordinates array.
void init (void) 
{
  int i, j, k;

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
  for (j = 0; j <= N; j++)
    for (i = 0; i <= M; i++){

      /* The vertex array is filled. */
      vdata[k++] = FNX(i,j); 
      vdata[k++] = FNY(i,j);
      vdata[k++] = FNZ(i,j); 
	}  

  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  glVertexPointer(3, GL_FLOAT, 0, vdata);
  glTexCoordPointer(2, GL_FLOAT, 0, texdata);
}

void display(void)
{
   int  i, j, l;
  
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glColor3f (1.0, 1.0, 1.0);
  
   glEnable(GL_TEXTURE_2D);
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
#ifdef GL_VERSION_1_1
   glBindTexture(GL_TEXTURE_2D, texName);
#endif

   /* The texture co-ordinates array is filled exactly as
    * in textured-torus.c, *except* that at each redisplay
    * the i (or, rather, s) co-ordinate is incremented by incr.
    */
   l = 0;
   for (j = 0; j <= N; j++)
    for (i = 0; i <= M; i++){
         texdata[l++] = (GLfloat) i/M + incr;
	 texdata[l++] = (GLfloat) j/N; 
	}  

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
   gluLookAt (2.0, 2.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void idle(void)
{
  incr += .01;
  glutPostRedisplay();
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
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("turn-textured-torus");
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutIdleFunc(idle);
   glutMainLoop();
   return 0;  
}



