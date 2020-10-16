/* disc.c. */
/* by Glenn Wardius*/

/* draws a disc (= filled circle) with color that gradually changes */

#include <GL/glut.h>
#include <unistd.h>
#include <math.h>

#define PI 3.14159265

/* draw the circle */
void display (void){

  GLint circle_pnts = 200;  /* # of vertices around the circle */
  GLdouble angle;
  int i;
  GLfloat color1 = 1.0;
  GLfloat color2 = 0.0;

  /* clear screen */
  glClear(GL_COLOR_BUFFER_BIT);

  /* starting color */
  glColor3f(color1, 1.0, color2);

  /* begin drawing circle by drawing a lot of small pie slices */
  glBegin(GL_TRIANGLE_FAN);

  /* set a vertex in the middle */
  glVertex2f(0.0, 0.0);

  /* now set some vertices around the edge of the circle
     changing color slightly for each vertex */
  for(i = 0; i < circle_pnts; ++i){
    angle = 2 * PI * i / circle_pnts;
    glVertex2f(cos(angle) * 0.9, sin(angle) * 0.9);
    color1 = color1 - 1.0 / circle_pnts;
    color2 = color2 + 1.0 / circle_pnts;
    glColor3f(color1, 1.0, color2);
  }

  /* the last vertex */
  glVertex2f(0.9, 0.0);

  glEnd();

  glFlush();
}


void init (void){

  glShadeModel(GL_FLAT);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case 27:
    exit(0);
    break;
  }
}

int main(int argc, char** argv){

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowSize (500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);
  init ();
  glutDisplayFunc(display); 
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return 0;   /* ANSI C requires main to return int. */
}

