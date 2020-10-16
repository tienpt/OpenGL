/*
 * curve3d.c
 *
 * KEYBOARD OPERATION: Press 'x', 'X', 'y', 'Y', 'z', 'Z'
 * to rotate the helix. Press 'esc', 'q' or 'e' to exit.
 */

#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#define PI 3.14159265

// Angles used to turn the helix with keyboard entry.
static int Xangle = 0, Yangle = 0, Zangle = 0;

void init (void) 
{
  glClearColor (0.0, 0.0, 0.0, 0.0);
}

void display(void)
{
   int i, j;

   glClear (GL_COLOR_BUFFER_BIT);

   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  
   glColor3f (1.0, 1.0, 1.0);

   // Following commands are used to rotate the scene.
   glRotatef ((GLfloat) Zangle, 0.0, 0.0, 1.0);
   glRotatef ((GLfloat) Yangle, 0.0, 1.0, 0.0);
   glRotatef ((GLfloat) Xangle, 1.0, 0.0, 0.0);

   glPointSize(1.0);
   // The helix is drawn here as a polygonal line joining 100 points.
   /*
   glBegin(GL_POINTS);
   for(i = 0; i < 2000; i = i+10)
     glVertex3f( cos( ( ((float)i - 4.0 + rand()%7)/400.0)*2.0*PI ), 
                 sin( ( ((float)i - 4.0 + rand()%7)/400.0)*2.0*PI ) , 
                 -2.5 + ((float)i - 4.0 + rand()%7)/500.0 );
   glEnd();
   */
   glBegin(GL_LINE_STRIP);
   for(i = 0; i < 2000; i = i+10)
     glVertex3f( cos( ( ((float)i - 4.0 + rand()%7)/400.0)*2.0*PI ), 
                 sin( ( ((float)i - 4.0 + rand()%7)/400.0)*2.0*PI ) , 
                 -2.5 + ((float)i - 4.0 + rand()%7)/500.0 );
   glEnd();

   glFlush ();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();

   // This statement creates a viewing frustum.
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 'x':
	//Xangle = (Xangle + 5) % 360;
	cout << "Enter x valuess; ";
        cin >> Xangle;
         glutPostRedisplay();
         break;
      case 'X':
         Xangle = (Xangle - 5) % 360;
         glutPostRedisplay();
         break;
      case 'y':
         Yangle = (Yangle + 5) % 360;
         glutPostRedisplay();
         break;
      case 'Y':
         Yangle = (Yangle - 5) % 360;
         glutPostRedisplay();
         break;
      case 'z':
         Zangle = (Zangle + 5) % 360;
         glutPostRedisplay();
         break;
      case 'Z':
         Zangle = (Zangle - 5) % 360;
         glutPostRedisplay();
         break;
      case 'e':
         exit(0);
         break;
      case 'q':
         exit(0);
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
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Parabolic cylinder");
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;  
}
