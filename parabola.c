/*
 * parabola.c
 * A parabola is drawn by approximating the curve with a line strip.
 */

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
 
// The number of vertices taken from the parabola to be
//  joined line strip is 2M+1. Increase M for a finer approximation.
#define M 3

void init (void) 
{
  glClearColor (0.0, 0.0, 0.0, 0.0);
}

void display(void)
{
   int i;
   glClear (GL_COLOR_BUFFER_BIT);

   glColor3f (1.0, 1.0, 1.0);
   /*
    * The 2M+1 approximating points on the parabola are
    * equally spaced between their x-coordinates from
    * -1 to 1. A better approximation would be obtained
    * by making the points closer together in the x-coordinate
    * as they move away from the origin as the parabola
    * grows faster.
    */
   glBegin(GL_LINE_STRIP);
   for(i = -M; i <= M; ++i){
       glVertex3f( (float) i/M, (float) (i*i)/(M*M), 0.0);
   }
   glEnd();
  
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
   gluLookAt (0.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
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
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Parabola");
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;  
}
