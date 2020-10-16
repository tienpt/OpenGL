/*
 *  allQuadrics.c
 *  Sumanta
 *  Draws the four different GLU quadrics.
 * 
 *  Press the shift key to change quadrics. 
 *  Press the x, X, y, Y, z, Z keys to rotate the quadric.
 */

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

// Create a pointer to a new quadric object.
GLUquadricObj *qobj;

// Variables used to rotate the object.
static int Xangle = 0, Yangle = 0, Zangle = 0;

// Variable used to choose which quadric to draw.
static int count = 1;

void init(void) 
{
   // Create the new quadric.
   qobj = gluNewQuadric();

   // Draw the quadric in wireframe.
   gluQuadricDrawStyle(qobj, GLU_LINE); 

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);
   glColor3f (1.0, 1.0, 1.0);
   glLoadIdentity ();             
   gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
     
   glRotatef ((GLfloat) Zangle, 0.0, 0.0, 1.0);
   glRotatef ((GLfloat) Yangle, 0.0, 1.0, 0.0);
   glRotatef ((GLfloat) Xangle, 1.0, 0.0, 0.0);

   // A sphere of radius 0.75 with the frame consisting of 
   // 15 longitudinal and 10 latitudinal slices.
   if (count == 1) gluSphere(qobj, 0.75, 15, 10);

   // A cylinder with base radius 0.5, top radius 0.3, height 1.0
   // with the frame consisting of 15 up-down slices parallel to the axis 
   // and 5 slices perpendicular to the axis.
   if (count == 2) gluCylinder(qobj, 0.5, 0.3, 1.0, 15, 5); 

   // A partial disk with inner radius 0.4, outer radius 1.0, drawn
   // from 30 degrees to 300(=30+270) degrees with the frame 
   // consting of 10 radial slices and 5 circular slices.
   if (count == 3) gluPartialDisk(qobj, 0.4, 1.0, 10, 5, 30, 270); 

   // An entire disk with inner radius 0.4, outer radius 1.0, drawn
   // with the frame consting of 10 radial slices and 5 circular slices.
   if (count == 4) gluDisk(qobj, 0.4, 1.0, 10, 5); 
   glFlush ();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
   glMatrixMode (GL_MODELVIEW);
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case ' ':
         if (count == 1) count = 2;
         else if (count == 2) count = 3;
         else if (count == 3) count = 4;
         else count = 1;
         glutPostRedisplay();
         break;	  
      case 'x':
         Xangle = (Xangle + 5) % 360;
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
   printf("Press the shift key to see different quadrics.\n Press x, X, y, Y, z, Z to rotate the quadric.\n");
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
