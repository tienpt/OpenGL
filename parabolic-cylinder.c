/*
 * parabolic-cylinder.c
 * A cylinder is made by "extruding" a parabola on the xy-plane 
 * along the z-axis (SEE parabola.c). Triangle strips are defined 
 * parallel to the parabola, one on top of the other.
 * NOTE: Compare this program with cylinder*.c for drawing a curved
 * surface. 
 * (1) In cylinder*.c we explicitly formulate an intermediate
 *     object - the triangulated grid - which is then mapped to the cylinder.
 * (2) The vertex co-ordinates in cylinder.c are precomputed and stored in
 * an array vdata. Here, on the other hand, we compute them on the fly. 
 * For complex objects precomputing is preferable. 
 */

/* Use the x, X, y, Y, z, Z keys to turn the cylinder. */

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
 
// The number of vertices on the parabola will be 2M+1.
// The number of parallel triangle strips will be N.
// Increase for a finer approximation.
#define M 4
#define N 4

// Angles used to rotate the cylinder with keyboard entry.
static int Xangle = 0, Yangle = 0, Zangle = 0;

void init (void) 
{
  glClearColor (0.0, 0.0, 0.0, 0.0);
}

void display(void)
{
   int i, j;

   glClear (GL_COLOR_BUFFER_BIT);

   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  
   glColor3f (1.0, 1.0, 1.0);

   glRotatef ((GLfloat) Zangle, 0.0, 0.0, 1.0);
   glRotatef ((GLfloat) Yangle, 0.0, 1.0, 0.0);
   glRotatef ((GLfloat) Xangle, 1.0, 0.0, 0.0);

   for(j = 0; j < N; j++){
     glBegin(GL_TRIANGLE_STRIP);
     for(i = -M; i <= M; ++i){
       glVertex3f( (float) i/M, (float) (i*i)/(M*M), (float) (j+1)/N );
       glVertex3f( (float) i/M, (float) (i*i)/(M*M), (float) j/N );
     }
   glEnd();
   }
  
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
   gluLookAt (0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
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
   glutCreateWindow ("Parabolic cylinder");
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;  
}
