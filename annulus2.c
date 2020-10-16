/*
 * annulus2.c
 * Draws the outline of a square annulus using triangles
 * with the vertices specified using the pointer form glVertex3fv().
 * Uses edge flags to suppress interior edges.
 */
#include <GL/glut.h>

/* put the (x,y,z)-coordinates of the 8 vertices of the annulus in a 2D array */

static GLfloat vdata[8][3] = {
  {0.10, 0.10, 0.0}, {0.25, 0.25, 0.0}, {0.90, 0.10, 0.0}, {0.75, 0.25, 0.0}, 
  {0.90, 0.90, 0.0}, {0.75, 0.75, 0.0}, {0.10, 0.90, 0.0}, {0.25, 0.75, 0.0} 
};

/* put the 3 vertex indexes of each of the 8 triangles of a triangulation of
 * the annulus in a 2D array.
 * Note that the triangles are ORIENTED CONSISTENTLY with (outward) faces having
 * their vertices in counterclockwise order. 
 */

static GLuint triangleIndices[8][3] = {
  {2, 1, 0}, {1, 2, 3}, {4, 3, 2}, {3, 4, 5}, {6, 5, 4}, {5, 6, 7}, {0, 7, 6}, {7, 0, 1} 
};

void display(void)
{
  int i;

   glClear (GL_COLOR_BUFFER_BIT);

/* sets the polygon mode to draw only outline. See p. 56 red book. Experiment! */
   glPolygonMode(GL_FRONT, GL_LINE);

   glColor3f (1.0, 1.0, 1.0);

  glBegin(GL_TRIANGLES);
  for (i = 0; i < 8; i++){
/* suppresses a non-boundary edge. See p. 62 red book. Experiment! */
    glEdgeFlag(GL_FALSE);
    glVertex3fv(vdata[triangleIndices[i][0]]); // Messy! 
    // Vertex arrays are better. See following programs.
    glEdgeFlag(GL_FALSE);
    glVertex3fv(vdata[triangleIndices[i][1]]);
    glEdgeFlag(GL_TRUE);
    glVertex3fv(vdata[triangleIndices[i][2]]);
}
  glEnd();

   glFlush ();
}

void init (void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);

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
   glutCreateWindow ("annulus2");
   init ();
   glutDisplayFunc(display); 
   glutMainLoop();
   return 0;
}
