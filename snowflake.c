/* snowflake.c
 * Sumanta
 * This program follows the ideas of icosahedron.c.
 * Repeated subdivision causes successive layers to 
 * be added to the Koch snowflake.
 *
 * Interaction: Press 's' to add a layer.
 */
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define C1 1.732050807568877294 /* sqrt(3) */
#define C2 0.288675134594812882 /* 1/(2 * sqrt(3)) */

void display();
void bump (float* v1, float* v2, int depth);
void drawtriangle(float* v1, float* v2, float* v3);

static GLfloat vdata[3][3] = {
  {-1.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, C1, 0.0}
};

int depth = 0;

void display(){
  GLfloat fdepth;
  glClear (GL_COLOR_BUFFER_BIT);
  /* The single level 0 triangle is drawn with color determined by (depth + 1)
   * as level 1, the next level,  will be called with value depth, and level 2 with
     value (depth  - 1) and so on. Compare coloring routine in the bump function. */

  fdepth = (float) depth;
  fdepth++;
  glColor3f ( 0.5 + sin(fdepth)/2, 0.5 + cos(fdepth)/2, 0.5 - sin(fdepth)/2 );

  drawtriangle(&vdata[0][0], &vdata[1][0], &vdata[2][0]);

  bump(&vdata[0][0], &vdata[1][0], depth);
  bump(&vdata[1][0], &vdata[2][0], depth);
  bump(&vdata[2][0], &vdata[0][0], depth);

  glFlush();
}


void bump (float* v1, float* v2, int depth){
  /* The bump function draws the equilateral triangle centered on 
   * the middle third of the segment from v1 to v2 and recursively
   * calls bump on the resulting four line segments.
   */

  GLfloat v3[3], v4[3], v5[3], fdepth;
  GLint i;

  if (depth == 0){
    return;
  }
  
  for(i=0; i < 3; i++){
    v3[i] = 2.0*v1[i]/3.0 + v2[i]/3.0;
    v4[i] = v1[i]/3.0 + 2.0*v2[i]/3.0; 
  }
    v5[0] = 0.5 * (v1[0] + v2[0]) + C2 * (v2[1] - v1[1]);
    v5[1] = 0.5 * (v1[1] + v2[1]) - C2 *( v2[0] - v1[0]);
    v5[2] = 0.0;
    
    /* Compare the coloring routine in display. */
    fdepth = (float) depth;
    glColor3f ( 0.5 + sin(fdepth)/2, 0.5 + cos(fdepth)/2, 0.5 - sin(fdepth)/2 );
   
  drawtriangle(v3, v5, v4);

  bump(v1, v3, depth-1);
  bump(v3, v5, depth-1);
  bump(v5, v4, depth-1);
  bump(v4, v2, depth-1);
}

void drawtriangle(float* v1, float* v2, float* v3){

  glBegin(GL_TRIANGLES);
    glVertex3fv(v1);
    glVertex3fv(v2);
    glVertex3fv(v3);
  glEnd();
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case 'e':
    exit(0);
    break;
  case 's':
    ++depth;
    printf("The snowflake level has %d levels.\n", depth);
    glutPostRedisplay();
    break;
  }
}

void init (void) 
{
/* select clearing color 	*/
   glClearColor (0.0, 0.0, 0.0, 0.0);

/* initialize viewing values  */
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-1.5, 1.5, -1.0, 2.0, -1.0, 1.0);

    printf("The snowflake level has 0 levels.\n");
}

/*  Main Loop
 */

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (800, 800); 
   glutInitWindowPosition (50, 20);
   glutCreateWindow ("Koch snowflake2d");
   init ();
   glutDisplayFunc(display); 
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;   /* ANSI C requires main to return int. */
}

