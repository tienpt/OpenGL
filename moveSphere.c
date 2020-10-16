/*
 * moveSphere.c
 *  
 * This program allows to move a sphere to demonstrate
 * distortion at the edges of the viewing frustum.
 */

/* 
 * Key control: The x, X, and y, Y move the sphere.
 *              The i, I keys restore the sphere to the start position.
 *              The r, R keys rotate the sphere.
 */

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

// Globals to set the position of the sphere.
static float Xvalue = 0.0, Yvalue = 0.0, Angle = 0.0;

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);
   glColor3f (1.0, 1.0, 1.0);
   glPushMatrix();
   gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   // Set the position of the sphere.
   glTranslatef(Xvalue, Yvalue, 0.0);
   glRotatef(Angle, 1.0, 1.0, 1.0);

   glutWireSphere (0.5, 16, 10);
   glPopMatrix();
   glFlush ();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity ();
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 'x':
         Xvalue += 0.1;
         glutPostRedisplay();
		 break;
       case 'X':
         Xvalue -= 0.1;
         glutPostRedisplay();
         break;  
      case 'y':
         Yvalue += 0.1;
         glutPostRedisplay();
         break;
      case 'Y':
         Yvalue -= 0.1;
         glutPostRedisplay();
         break; 
      case 'i':
      case 'I':
         Xvalue = Yvalue = 0.0;
         glutPostRedisplay();
         break;
      case 'r':
      case 'R':
         Angle += 10.0;
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
   printf("The x, X, and y, Y keys move the sphere.\n");
   printf("The i, I keys restore the sphere to the start position.\n");
   printf("The r, R keys rotate the sphere.\n");
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("moveSphere");
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
