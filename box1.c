/* box1.c
 * This program draws a red box and then draws a green sphere within 
 * the box. The top face of the box is drawn by pressing 'c' to close the box, and
 * not drawn by pressing 'o' to open the box. 'e' = exit.
 * NOTE:
 * (1) Depth test has been enabled to eliminate hidden lines (search word "depth").
 * (2) Keboard input: see keyboard function.
 * (3) Perspective projection using gluPerspective (see reshape) routine, rather
 * than glOrtho.
 * (4) The code can be improved with the use of vertex arrays.
 */

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

static int N = 6;

void display();

/* put the (x,y,z)-coordinates of the 8 vertices of a box, of side length 2 
 * and centered at (0,0,0), in a 2D array 
 */
static GLfloat vdata[8][3] = {
  {1.0, -1.0, 1.0}, {1.0, 1.0, 1.0}, {1.0, 1.0, -1.0}, {1.0, -1.0, -1.0}, 
  {-1.0, -1.0, 1.0}, {-1.0, 1.0, 1.0}, {-1.0, 1.0, -1.0}, {-1.0, -1.0, -1.0}
};

/* put the 4 vertex indexes of each of the 6 faces of the box in a 2D array.
 * Note that the faces are ORIENTED CONSISTENTLY with outward faces having
 * their vertices in counterclockwise order. 
 */
static GLuint tindices[6][4] = {
  {3,2,1,0}, {7,6,2,3}, {4,5,6,7}, {0,1,5,4}, {4,7,3,0}, {6,5,1,2} 
};

void display(){
  int i;

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glColor3f (1.0, 0.0, 0.0);

/* draw 6 red faces of the box; note that the last face (i=5) is 
 * the top face, so toggling N between 5 and 6 opens and closes the box
 */
  glBegin(GL_QUADS);
  for (i = 0; i < N; ++i){
    glVertex3fv(vdata[tindices[i][0]]);
    glVertex3fv(vdata[tindices[i][1]]);
    glVertex3fv(vdata[tindices[i][2]]);
    glVertex3fv(vdata[tindices[i][3]]);  
}
  glEnd();


  glColor3f (0.0, 1.0, 0.0);
/* draw a green sphere inside the box.
 * the sphere is a 3D object from the GLUT library;
 * for other such objects see p. 20 of the red book.
 * the first parameter is the radius of the sphere,
 * the other two determine how finely it is triangulated
 */
  glutSolidSphere (1.0, 20.0, 16.0);
  glFlush();
}

void init(void)
{
   glEnable(GL_DEPTH_TEST); 

   glClearColor(0.0, 0.0, 0.0, 0.0);
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (0.0, 3.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

/* the following defines keyboard input */
void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case 'e':
    exit(0);
    break;
  case 'o':
    N = 5;
    glutPostRedisplay();
    break;
  case 'c':
    N = 6;
    glutPostRedisplay();
    break;
  default:
    break;
  }
}

/*  Main Loop
 */
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); 
   glutInitWindowSize (400, 400);
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init();
   glutReshapeFunc(reshape);
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}








