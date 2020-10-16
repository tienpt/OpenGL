/*
 * annulus5.c
 * Draws a square annulus using triangles
 * with the vertices specified in a vertex array.
 * and accessed with a loop of glDrawElements()
 * with parameter GL_TRIANGLES.
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

// The 8 triangle vertex indices in sets of 3.
static GLubyte triangleIndices[8][3] = {
  {2, 1, 0}, {1, 2, 3}, {4, 3, 2}, {3, 4, 5}, {6, 5, 4}, {5, 6, 7}, {0, 7, 6}, {7, 0, 1} 
};

void display(void)
{
   int i;
   glClear (GL_COLOR_BUFFER_BIT);
  
   glColor3f (1.0, 1.0, 1.0);

   // Using glDrawElements in a loop to pull up data for 3 vertices at a time
   // for 8 different triangles - note that this is *less* efficient than using
   // glDrawElements once to pull up data for one triangle strip.
   for (i = 0; i < 8; i++){
   glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, triangleIndices[i]);
   }

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
   glutCreateWindow ("annulus5");
   init ();
   glutDisplayFunc(display); 
   glutMainLoop();
   return 0;  
}
