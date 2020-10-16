/*
 * windows.c
 * We modify hello.c to show two top-level windows.
 */
#include <GL/glut.h>
#include <stdlib.h>

/* Window identifiers. */
static int id1, id2;

void display1(void)
{
   /* Draw into 1st top-level window (id 1). */
   glutSetWindow(id1);

   glClear (GL_COLOR_BUFFER_BIT);
   /* Draw white polygon (rectangle). */
   glColor3f (1.0, 1.0, 1.0);
   glBegin(GL_POLYGON);
      glVertex3f (0.25, 0.25, 0.0);
      glVertex3f (0.75, 0.25, 0.0);
      glVertex3f (0.75, 0.75, 0.0);
      glVertex3f (0.25, 0.75, 0.0);
   glEnd();

   glFlush ();
}

void display2(void)
{
   /* Draw into 2nd top-level window (id 2). */
   glutSetWindow(id2);

   glClear (GL_COLOR_BUFFER_BIT);
/* Draw red polygon (rectangle). */
   glColor3f (1.0, 0.0, 0.0);
   glBegin(GL_POLYGON);
      glVertex3f (0.25, 0.25, 0.0);
      glVertex3f (0.75, 0.25, 0.0);
      glVertex3f (0.75, 0.75, 0.0);
      glVertex3f (0.35, 0.85, 0.0);
      glVertex3f (0.25, 0.75, 0.0);
   glEnd();

   glFlush ();
}

void init1 (void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

void init2 (void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 2.0, 0.0, 2.0, -1.0, 1.0);
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   
/* First top-level window. */
   glutInitWindowSize (100, 100); 
   glutInitWindowPosition (100, 100);
   id1 = glutCreateWindow ("hello"); // Create window and return id.
   init1();
   glutDisplayFunc(display1); 

/* Second top-level window. */
   glutInitWindowSize (100, 100); 
   glutInitWindowPosition (300, 100); 
   id2 = glutCreateWindow ("again"); // Create window and return id.
/* We use different init and display functions for the heck of it
 * but its not required.
 */
   init2();
   glutDisplayFunc(display2); 

   glutMainLoop();
   return 0;   /* ANSI C requires main to return int. */
}
