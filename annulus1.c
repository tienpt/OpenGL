/*
 * annulus1.c
 * Draws a square annulus using a triangle strip with
 * the vertices specified using glVertex3f().
 */

#include <GL/glut.h>

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);

/* draws a square annulus formed between the rectangle with corners at
 * (0.25, 0.25, 0.0) and (0.75, 0.75, 0.0)  
 * and the rectangle with corners at
 * (0.10, 0.10, 0.0) and (0.90, 0.90, 0.0)
 */
  
   glColor3f (1.0, 1.0, 1.0);
   glBegin(GL_TRIANGLE_STRIP);
      glVertex3f (0.10, 0.10, 0.0);
      glVertex3f (0.25, 0.25, 0.0);
      glVertex3f (0.90, 0.10, 0.0);
      glVertex3f (0.75, 0.25, 0.0);
      glVertex3f (0.90, 0.90, 0.0);
      glVertex3f (0.75, 0.75, 0.0);
      glVertex3f (0.10, 0.90, 0.0);
      glVertex3f (0.25, 0.75, 0.0);
      glVertex3f (0.10, 0.10, 0.0);
      glVertex3f (0.25, 0.25, 0.0);
   glEnd();

   glFlush ();
}

void init (void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (250, 250); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("annulus1");
   init ();
   glutDisplayFunc(display); 
   glutMainLoop();
   return 0;   
}
