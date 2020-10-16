/*
 * noseCone.c
 *
 * A nose cone is made in two pieces: a circular cylinder is attached
 * to half of a circular ellipsoid.
 */

/* Use the x, X, y, Y, z, Z keys to turn the cone. */

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
 
#define PI 3.14159265358979324

#define M  25  
#define N  15

// The FN1 functions define the mapping from ij space to xyz space for
// the cylinder
GLfloat FN1X(int i, int j)
{
  return ( cos( ( (float) i/M ) * 2 * PI) );
}

GLfloat FN1Y(int i, int j)
{
  return ( sin( ( (float) i/M ) * 2 * PI) );
}

GLfloat FN1Z(int i, int j)
{
  return 3.0 * (float) j/N;
}

// The FN2 functions define the mapping from ij space to xyz space for
// half of an ellipsoid with a circular cross-section parallel to the xy-plane.  
GLfloat FN2X(int i, int j)
{
  return ( cos( ( (float) i/M ) *  PI) * cos( ( (float) j/N ) *  PI) );
}

GLfloat FN2Y(int i, int j)
{
  return ( cos( ( (float) i/M ) *  PI) * sin( ( (float) j/N ) *  PI) );  
}

GLfloat FN2Z(int i, int j)
{
  return ( 2 * sin( ( (float) i/M ) *  PI) );  
}

// Two vertex arrays.
static GLfloat vdata1[3*(M+1)*(N+1)];
static GLfloat vdata2[3*(M+1)*(N+1)];

// Angles used to rotate the cylinder with keyboard entry.
static int Xangle = 0, Yangle = 0, Zangle = 0;

void init (void) 
{
  int i, j, k;

  glClearColor (0.0, 0.0, 0.0, 0.0);
      
  // Fill the first vertex array with cylinder points.
  k = 0;
  for (j = 0; j <= N; j++)
    for (i = 0; i <= M; i++){
      vdata1[k++] = FN1X(i,j); 
      vdata1[k++] = FN1Y(i,j);
      vdata1[k++] = FN1Z(i,j); 
	} 

  // Fill the second vertex array with ellipsoid points.
  k = 0;
  for (j = 0; j <= N; j++)
    for (i = 0; i <= M; i++){
      vdata2[k++] = FN2X(i,j); 
      vdata2[k++] = FN2Y(i,j);
      vdata2[k++] = FN2Z(i,j); 
	} 

  glEnableClientState(GL_VERTEX_ARRAY);
}

void display(void)
{
   int  i, j;
  
   glClear (GL_COLOR_BUFFER_BIT);

   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   glColor3f (1.0, 1.0, 1.0);
   
   glPushMatrix();
   glRotatef ((GLfloat) Zangle, 0.0, 0.0, 1.0);
   glRotatef ((GLfloat) Yangle, 0.0, 1.0, 0.0);
   glRotatef ((GLfloat) Xangle, 1.0, 0.0, 0.0);
 
   // Draw the cylinder.
   glVertexPointer(3, GL_FLOAT, 0, vdata1);
   for(j = 0; j < N; j++){
     glBegin(GL_TRIANGLE_STRIP);
     for(i = 0; i <= M; i++){
       glArrayElement( j*(M+1) + i );
       glArrayElement( (j+1)*(M+1) + i );
     }
   glEnd();
   }

   // Draw the half-ellipsoid translated to attach to the cylinder.
   glTranslatef(0.0, 0.0, 3.0);
   glVertexPointer(3, GL_FLOAT, 0, vdata2);
   for(j = 0; j < N; j++){
     glBegin(GL_TRIANGLE_STRIP);
     for(i = 0; i <= M; i++){
       glArrayElement( j*(M+1) + i );
       glArrayElement( (j+1)*(M+1) + i );
     }
   glEnd();
   }

   glPopMatrix();

  glFlush ();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (0.0, 0.0, 9.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
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
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("cylinder2");
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;  
}
