/*
 * planet-2views.c
 * This program by Sumanta modifies planet.c to show two views 
 * in two windows. The sun is replaced with a teapot as an asymmetrical 
 * object is prefered to show up different views. One view is exactly as
 * before (in the original planet.c) from a point in space beyond
 * the orbit of the planet. The second view is from the planet's
 * north pole. The uncommented code does not implement a view that
 * takes into account the planet's rotation about its own axis.
 * But we have an option to do that that is commented out.
 * We also enable depth testing.
 * 
 * NOTE:
 * To understand how the two windows are set up refer to windows.c.
 * Here, unlike windows.c, both windows share the same display, reshape
 * and keyboard functions. Within the display function we choose the 
 * drawing window with glutSetWindow().
 *
 * INTERACTION: Press y/Y and d/D to rotate the planet. With uncommented
 * code view does not change with d/D.
 */

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265

/* Window identifiers. */
static int id1, id2;

static int year = 0, day = 0;

void display(void)
{
  /* Draw into 1st top-level window (id 1). */
   glutSetWindow(id1);

   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glPushMatrix();

   glLoadIdentity();

   /* The static spaceship view. */
   gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   glColor3f (1.0, 0.0, 0.0);
   glutWireTeapot(0.5);   /* draw sun */
   glRotatef ((GLfloat) year, 0.0, 1.0, 0.0);
   glTranslatef (2.0, 0.0, 0.0);
   glRotatef ((GLfloat) day, 0.0, 1.0, 0.0);
   glColor3f (0.0, 0.0, 1.0);
   glutWireSphere(0.2, 10, 8);    /* draw smaller planet */
   glPopMatrix();

   glFlush();
   glutSwapBuffers();

   /* Draw into 2nd top-level window (id 2). */
   glutSetWindow(id2);

   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glColor3f (1.0, 1.0, 1.0);

   glPushMatrix();

   glLoadIdentity();

   /* The view from the north pole of the planet only taking into account yearly rotation. */
   gluLookAt (2.0 * cos( (float)year*PI/180.0 ), 0.2, -2.0 * sin( (float)year*PI/180.0 ), 
              0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   
   /* The view from the north pole of the planet taking into account both yearly 
    * & daily rotation. Replace the above gluLookAt() with the following one.
    *gluLookAt 
    *( 2.0 * cos( (float)year*PI/180.0 ), 0.2, -2.0 * sin( (float)year*PI/180.0 ), 
    *  2.0 * cos( (float)year*PI/180.0 ) - 0.2 * cos( (float)(year+day)*PI/180.0 ),
    *  0.2,
    * -2.0 * sin( (float)year*PI/180.0 ) + 0.2 * sin( (float)(year+day)*PI/180.0 ),
    *  0.0, 1.0, 0.0 );
    */

   glColor3f (1.0, 0.0, 0.0);
   glutWireTeapot(0.5);   /* draw sun */
   glRotatef ((GLfloat) year, 0.0, 1.0, 0.0);
   glTranslatef (2.0, 0.0, 0.0);
   glRotatef ((GLfloat) day, 0.0, 1.0, 0.0);
   glColor3f (0.0, 0.0, 1.0);
   glutWireSphere(0.2, 10, 8);    /* draw smaller planet */
   glPopMatrix();

   glFlush();
   glutSwapBuffers();
}

void init (void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);   
   glShadeModel (GL_FLAT);

   glEnable(GL_DEPTH_TEST);
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 'd':
         day = (day + 10) % 360;
         glutPostRedisplay();
         break;
      case 'D':
         day = (day - 10) % 360;
         glutPostRedisplay();
         break;
      case 'y':
         year = (year + 5) % 360;
         glutPostRedisplay();
         break;
      case 'Y':
         year = (year - 5) % 360;
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
   
/* First top-level window. */
   glutInitWindowSize (400, 400); 
   glutInitWindowPosition (100, 100);
   id1 = glutCreateWindow ("spaceship's view"); // Create window and return id.
   init();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);

/* Second top-level window. */
   glutInitWindowSize (400, 400); 
   glutInitWindowPosition (600, 100); 
   id2 = glutCreateWindow ("planet's view"); // Create window and return id.
   init();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);

   glutMainLoop();
   return 0; 
}
