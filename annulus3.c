/*
 * annulus3.c
 * Draws a square annulus using a triangle strip
 * with the vertices specified in a vertex array
 * and accessed with glArrayElement().
 */
#include <GL/glut.h>

// Successive vertex x,y,z co-ordinates.
static GLfloat vertices[] =  {0.10, 0.10, 0.0,
			      0.25, 0.25, 0.0,
			      0.90, 0.10, 0.0,
			      0.75, 0.25, 0.0,
			      0.90, 0.90, 0.0,
			      0.75, 0.75, 0.0,
			      0.10, 0.90, 0.0,
			      0.25, 0.75, 0.0};

// Successive vertex color vectors.
static GLfloat colors[] =  {1.0, 1.0, 1.0,
			    1.0, 0.0, 0.0,
			    0.0, 1.0, 0.0,
			    0.0, 0.0, 1.0,
			    1.0, 1.0, 0.0,
			    1.0, 0.0, 1.0,
			    0.0, 1.0, 1.0,
			    0.0, 1.0, 1.0};

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);
  
   glColor3f (1.0, 1.0, 1.0);
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

   glFlush ();
}

void init (void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);

   // Enable two vertex arrays: position and color.
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_COLOR_ARRAY);

   // Specify locations for the respective arrays.
   glVertexPointer(3, GL_FLOAT, 0, vertices);
   glColorPointer(3, GL_FLOAT, 0, colors);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}
	
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (250, 250); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("annulus3");
   init ();
   glutDisplayFunc(display); 
   glutMainLoop();
   return 0;  
}




