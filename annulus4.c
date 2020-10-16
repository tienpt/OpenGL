/*
 * annulus4.c
 * Draws a square annulus using a triangle strip
 * with the vertices specified in a vertex array
 * and accessed with a single glDrawElements()
 * with parameter GL_TRIANGLE_STRIP.
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

// Triangle strip vertex indices in order.
static GLubyte stripIndices[] = {0, 1, 2, 3, 4, 5, 6, 7, 0, 1};

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);
  
   glColor3f (1.0, 1.0, 1.0);

   // Using glDrawElements to "pull up" data for 10 vertices in one command -
   // more efficient than calling glArrayElement 10 times.
   glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_BYTE, stripIndices);

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
   glutCreateWindow ("annulus4");
   init ();
   glutDisplayFunc(display); 
   glutMainLoop();
   return 0;  
}
