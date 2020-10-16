/*
 *  viewport.c
 *  This program was developed by Glenn Wardius. It shows
 *  two viewports.
 */
#include <GL/glut.h>
#include <stdlib.h>

int width, height;

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void display(void)
{  
   glClear (GL_COLOR_BUFFER_BIT);


   glMatrixMode (GL_MODELVIEW);

/* Defining the contents of the 1st viewport */
   glColor3f (0.0, 1.0, 0.0);
   glLoadIdentity ();	
   glViewport (0, 0, width/2.0,  height); /* 1st viewport */
   gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); /* viewing transformation */
   glutWireCube (1.0);
   glFlush();

/* Defining the contents of the 2nd viewport */
   glColor3f (1.0, 0.0, 0.0);
   glLoadIdentity ();
   glViewport(width/2.0, 0, width/2.0, height); /* 2nd viewport */
   gluLookAt (5.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); /* viewing transformation */
   glutWireTeapot (1.0);
   glFlush();
}

/* NOTE: Both the wire cube and the teapot appear elongated in the y-direction
   owing to the difference in the aspect ratio of the viewport (= 1/2) and the
   aspect ratio of the viewing frustum (= 1).*/

void reshape (int w, int h)
{
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity();

/* 
 * The following viewport command is needed to clear the background correctly 
 * for both smaller viewports. It is needed because (see red book p. 104)
 * glViewport must be called from within the reshape routine to correctly
 * display the window.
 */
   glViewport(0, 0, w, h);

   width = w;
   height = h;
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}

