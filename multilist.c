/*
 *  multilist.c
 *  This program demonstrates the definition and execution of multiple 
 *  display lists.  
 *  Modified by Sumanta Guha from list.c of the red book.
 */
#include <GL/glut.h>
#include <stdlib.h>

GLuint base;
static GLint hieroglyphic[6] = {0, 2, 1, 1, 0, 2};

/* Create 3 display lists whose indices are 0, 1, and 2, resp.,
 * offset from a base value.
 */
static void init (void)
{
   base = glGenLists (3); /* returns the first of an available block
                             of 3 successive display-list indices */

   glNewList (base, GL_COMPILE);
      glColor3f (1.0, 0.0, 0.0);  /*  red triangle  */
      glBegin (GL_TRIANGLES);
      glVertex2f (0.0, 0.0);
      glVertex2f (1.0, 0.0);
      glVertex2f (0.0, 1.0);
      glEnd ();
      glTranslatef (1.5, 0.0, 0.0); /*  move 1.5 units in x-direction  */
   glEndList ();

   glNewList (base + 1, GL_COMPILE);
      glColor3f (0.0, 1.0, 0.0);  /*  green  square  */
      glBegin (GL_QUADS);
      glVertex2f (0.0, 0.0);
      glVertex2f (1.0, 0.0);
      glVertex2f (1.0, 1.0);
      glVertex2f (0.0, 1.0);
      glEnd ();
      glTranslatef (1.5, 0.0, 0.0); /*  move 1.5 units in x-direction  */
   glEndList ();

   glNewList (base + 2, GL_COMPILE);
      glColor3f (0.0, 0.0, 1.0);  /*  blue pentagon  */
      glBegin (GL_POLYGON);
      glVertex2f (0.0, 0.0);
      glVertex2f (1.0, 0.0);
      glVertex2f (1.0, 1.0);
      glVertex2f (0.5, 1.5);
      glVertex2f (0.0, 1.0);
      glEnd ();
      glTranslatef (1.5, 0.0, 0.0); /*  move 1.5 units in x-direction  */
   glEndList ();

   glShadeModel (GL_FLAT);
}

void display(void)
{ 
   glClear (GL_COLOR_BUFFER_BIT); 
   glListBase(base); /* specifies that base is to be used as the offset in
                        subsequent display list calls */
   glCallLists(6, GL_INT, hieroglyphic); /* executes 6 display lists whose indices
                                            are in the array "hieroglyphic" */
   glFlush ();
}

void reshape(int w, int h)
{
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h) 
      gluOrtho2D (0.0, 2.0, -0.5 * (GLfloat) h/(GLfloat) w, 
         1.5 * (GLfloat) h/(GLfloat) w);
   else 
      gluOrtho2D (0.0, 2.0 * (GLfloat) w/(GLfloat) h, -0.5, 1.5); 
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}

/*  Main Loop
 *  Open window with initial window size, title bar, 
 *  RGBA display mode, and handle input events.
 */
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(650, 50);
   glutCreateWindow(argv[0]);
   init ();
   glutReshapeFunc (reshape);
   glutDisplayFunc (display);
   glutKeyboardFunc (keyboard);
   glutMainLoop();
   return 0;
}

