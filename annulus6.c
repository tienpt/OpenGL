/*
 * annulus6.c
 * Shows the use of multiple vertex/color arrays.
 *
 * (Modification of annulus3.c)
 *
 * Draws a square annulus AND a triangle:
 * The vertices and colors of the triangle strip 
 * forming the annulus are specified in arrays
 * vertices and colors. The vertices and colors
 * forming the triangle are specified in arrays
 * vertices2 and colors2.
 */
#include <GL/glut.h>

// Successive vertex x,y,z co-ordinates of the annulus.
static GLfloat vertices[] =  {0.10, 0.10, 0.0,
			      0.25, 0.25, 0.0,
			      0.90, 0.10, 0.0,
			      0.75, 0.25, 0.0,
			      0.90, 0.90, 0.0,
			      0.75, 0.75, 0.0,
			      0.10, 0.90, 0.0,
			      0.25, 0.75, 0.0};

// Successive vertex color vectors for the annulus.
static GLfloat colors[] =  {1.0, 1.0, 1.0,
			    1.0, 0.0, 0.0,
			    0.0, 1.0, 0.0,
			    0.0, 0.0, 1.0,
			    1.0, 1.0, 0.0,
			    1.0, 0.0, 1.0,
			    0.0, 1.0, 1.0,
			    0.0, 1.0, 1.0};

// Successive vertex x,y,z co-ordinates of the triangle.
static GLfloat vertices2[] =  {0.30, 0.30, 0.0,
			       0.60, 0.30, 0.0,
			       0.60, 0.60, 0.0};

// Successive vertex color vectors for the triangle.
static GLfloat colors2[] =  {1.0, 1.0, 1.0,
			    1.0, 0.0, 0.0,
			    0.0, 1.0, 0.0};
void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);
  
   glColor3f (1.0, 1.0, 1.0);

   // Compare with annulus3.c: The following pair of 
   // statements have been moved here from the init 
   // function. Now the vertex and color array pointers
   // point to the data for the annulus.
   glVertexPointer(3, GL_FLOAT, 0, vertices);
   glColorPointer(3, GL_FLOAT, 0, colors);

   // Draw annulus.
   glBegin(GL_TRIANGLE_STRIP);
   glArrayElement(0);
   glArrayElement(1);
   glArrayElement(2);
   glArrayElement(3);
   glArrayElement(4);
   glArrayElement(5);
   glArrayElement(6);
   glArrayElement(7);
   glArrayElement(0);
   glArrayElement(1);
   glEnd();

   // Now the vertex and color array pointers
   // point to the data for the triangle.
   glVertexPointer(3, GL_FLOAT, 0, vertices2);
   glColorPointer(3, GL_FLOAT, 0, colors2);

   // Draw triangle.
   glBegin(GL_TRIANGLES);
   glArrayElement(0);
   glArrayElement(1);
   glArrayElement(2);
   glEnd();

   glFlush ();
}

void init (void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);

   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   // The parameters of glOrtho are changed to 
   // accomodate the triangle.
   glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (250, 250); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("annulus6");
   init ();
   glutDisplayFunc(display); 
   glutMainLoop();
   return 0;  
}

