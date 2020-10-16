/*
 * helloWithKey.c
 *
 * Modified from hello.c by Sumanta to show 
 * simple application of keyboard entry. 
 *
 */

/*
 * Key controls: 'f' for fill, 'w' for wireframe.  
 */

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

// Global variable - 1 if square is rendered filled; 0 if wireframe.
int fill = 1; 

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);

/* draw white polygon (rectangle) with corners at
 * (0.25, 0.25, 0.0) and (0.75, 0.75, 0.0)  
 */
   glColor3f (1.0, 1.0, 1.0);
   
   // Determine polygon rendering mode.
   if (fill == 1) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   if (fill == 0) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   glBegin(GL_POLYGON);
      glVertex3f (0.25, 0.25, 0.0);
      glVertex3f (0.75, 0.25, 0.0);
      glVertex3f (0.75, 0.75, 0.0);
      glVertex3f (0.25, 0.75, 0.0);
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

/* The following defines keyboard input */
void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case 'f':
    fill = 1;
    glutPostRedisplay();
    break;
  case 'w':
    fill = 0;
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
   // Print keyboard instructions.
   printf("Press 'f' for filled figure.\nPress 'w' for wireframe.\n");

   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (250, 250); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("helloWithKey");
   init ();
   glutDisplayFunc(display); 

   // Declare the keyboard function.
   glutKeyboardFunc(keyboard);

   glutMainLoop();
   return 0;   /* ANSI C requires main to return int. */
}
