/*
 *  movelight3.c
 *  This is movelight.c of the red book modified by Sumanta.
 *  The light "moves with" (ie., stays fixed at) the viewpoint (=eye). 
 *  This is achieved by setting the light position before all 
 *  modelview transformations.
 *
 *  Interaction:  pressing the left mouse button rotates
 *  the eye by 30 degrees about the y-axis.
 */
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265

static int spin = 0;

/*  Initialize material property, light source, lighting model,
 *  and depth buffer.
 */
void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
}

void display(void)
{
   GLfloat position[] = { 0.0, 0.0, 0.0, 1.0 };

   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glPushMatrix ();

/* The light is positioned and the cube is drawn *before*
 * modelview transformations.
 */
   glLightfv (GL_LIGHT0, GL_POSITION, position);

   gluLookAt (5.0 * sin( (float)spin/360.0 * PI ), 0.0 , 5.0 * cos( (float)spin/360.0 * PI), 
              0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   glutSolidTorus (0.275, 0.85, 8, 15);
   glPopMatrix ();
   glFlush ();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(40.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN) {
            spin = (spin + 30) % 360;
            glutPostRedisplay();
         }
         break;
      default:
         break;
   }
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
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutMouseFunc(mouse);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
