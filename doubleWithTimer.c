
// Modified from double.c by Sumanta to use glutTimerFunc() to run the animation.
// See comments for additions/modifications.
#include <GL/glut.h>
#include <stdlib.h>


static GLfloat spin = 0.0;
static GLint isAnimation = 0;


void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   glPushMatrix();
   glRotatef(spin, 0.0, 0.0, 1.0);
   glColor3f(1.0, 1.0, 1.0);
   glRectf(-25.0, -25.0, 25.0, 25.0);
   glPopMatrix();


   glutSwapBuffers();
}


// The callback function spinDisplay.
// Note that the parameter someValue(=1) passed to it by glutTimerFunc() is not used here.
void spinDisplay(int someValue)
{
   if (isAnimation)
   {
   spin = spin + 2.0;
   if (spin > 360.0)
      spin = spin - 360.0;
   glutPostRedisplay();
   }
   // Note that glutTimerFunc() calls spinDisplay *once* after the specified msecs.
   // So to make repeated calls spinDisplay must call itself again with glutTimerFunc()!
   glutTimerFunc(20, spinDisplay, 1);
}


void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}


void reshape(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}


// The mouse function is modified to set the global isAnimation,
// rather than specify an idle function as in double.c
void mouse(int button, int state, int x, int y) 
{
   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN)
         isAnimation = 1;
         break;
      case GLUT_MIDDLE_BUTTON:
      case GLUT_RIGHT_BUTTON:
         if (state == GLUT_DOWN)
                 isAnimation = 0;
         break;
      default:
         break;
   }
}

/* 
 *  Request double buffer display mode.
 *  Register mouse input callback functions
 */
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (250, 250); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape); 
   glutMouseFunc(mouse);


   // Register the callback function spinDisplay.
   // The call back function is called after 20 msecs. with the parameter 1 passed to it.
   glutTimerFunc(20, spinDisplay, 1);


   glutMainLoop();
   return 0;   /* ANSI C requires main to return int. */
}
