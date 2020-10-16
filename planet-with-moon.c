/*
 *  planet-with-moon.c
 *  Modified from planet.c by Sumanta.
 *  Interaction:  pressing the y and Y keys rotates
 *  the planet around the sun and the moon around the planet.
 */

#include <GL/glut.h>
#include <stdlib.h>

static int year = 0;

void init(void) 
{  
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);
   glPushMatrix();
   
/* draw sun */
   glColor3f (1.0, 0.0, 0.0);
   glutWireSphere(1.0, 20, 16); 

/* draw planet */
   glColor3f (0.0, 1.0, 0.0);
   glRotatef ((GLfloat) year, 0.0, 1.0, 0.0);
   glTranslatef (2.0, 0.0, 0.0);
   glRotatef ((GLfloat) 365 * year, 0.0, 1.0, 0.0);
   glutWireSphere(0.2, 10, 8);    

/* draw moon */
   glColor3f (0.0, 0.0, 1.0);
   glTranslatef (0.5, 0.0, 0.0);
   glutWireSphere(0.1, 5, 4);    

   glPopMatrix();
   glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (0.0, 3.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
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
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
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

