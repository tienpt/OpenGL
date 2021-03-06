/* icosahedron.c
 * This program is based on the example from the red book
 * on drawing an icosahedron (p. 88 on), which is one of the
 * Platonic solids with 12 vertices and 20 triangular sides.
 * Developed by Glenn Wardius.
 * Repeated subdivision, by entering 's', causes successively
 * better approximations of a sphere. Cycles through s = 0 to 5.
 */
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define X  0.525731112119133606
#define Z  0.850650808352039932

void display();
void subdivide (float* v1, float* v2, float* v3, int depth);
void drawtriangle(float* v1, float* v2, float* v3);
void normalize(float v[3]);

// The presentation of the following data may be improved with
// vertex arrays.

// x,y,z co-ordinates of the 12 vertices in sets of 3.
static GLfloat vdata[12][3] = {
  {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X,0.0,-Z},
  {0.0,Z,X}, {0.0,Z,-X}, {0.0,-Z, X},{0.0, -Z, -X},
  {Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0}
};

// Vertex indices of the 20 triangular sides in sets of 3.
static GLuint tindices[20][3] = {
  {0,4,1},  {0,9,4},  {9,5,4},  {4,5,8},  {4,8,1},
  {8,10,1}, {8,3,10}, {5,3,8},  {5,2,3},  {2,7,3},
  {7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6},
  {6,1,10}, {9,0,11}, {9,11,2}, {9,2,5},  {7,2,11} 
};

int depth = 0;

void display(){

  int i;

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for (i = 0; i < 20; ++i)
    subdivide(vdata[tindices[i][0]], vdata[tindices[i][1]], 
	    vdata[tindices[i][2]], depth);

  glFlush();
}

/* we subdivide as follows: for each edge of a triangle face of
 * the icosahedron we find its midpoint. This midpoint is then
 * extended (normalized) to lie on the sphere. From each icosahedron
 * triangle we therefore get 6 vertices on the sphere - 3 original
 * and 3 edge midpoints. These are then joined as indicated to 
 * form 4 new smaller triangles. Thus each original triangle is
 * subdivided into 4.
 * The procedure can be repeated recursively.
 *
 *                  ________
 *                  \  /\  /
 *                   \/__\/
 *                    \  /
 *                     \/
 */

void subdivide (float* v1, float* v2, float* v3, int depth){

  GLfloat v12[3], v23[3], v31[3];
  GLint i;

  if (depth == 0){
    drawtriangle(v1, v2, v3);
    return;
  }

  for(i=0; i < 3; i++){
    v12[i] = v1[i] + v2[i];
    v23[i] = v2[i] + v3[i]; 
    v31[i] = v3[i] + v1[i];
  }

  normalize(v12);
  normalize(v23);
  normalize(v31);

  subdivide(v1, v12, v31, depth-1);
  subdivide(v2, v23, v12, depth-1);
  subdivide(v3, v31, v23, depth-1);
  subdivide(v12, v23, v31, depth-1);
}

void drawtriangle(float* v1, float* v2, float* v3){

  glBegin(GL_TRIANGLES);
    glNormal3fv(v1);  glVertex3fv(v1);
    glNormal3fv(v2);  glVertex3fv(v2);
    glNormal3fv(v3);  glVertex3fv(v3);
  glEnd();
}

// Given a vector (an array of size 3) normalize to unit length.
void normalize(float v[3]){

  GLfloat d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

  if (d == 0.0){
    printf("zero length vector\n");
    exit(-1);
  }

  v[0] /= d;  v[1] /= d;  v[2] /= d;
}

void init(void)
{
   GLfloat ambient[] = { 0.1, 0.1, 0.1, 1.0 };
   GLfloat diffuse[] = { 1.0, 1.0, 0.0, 1.0 };
   GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat position[] = { 0.0, 1.0, 3.0, 0.0 };
    
   GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };

   glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
   glLightfv(GL_LIGHT0, GL_POSITION, position);
    
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
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
   gluLookAt (0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case 'e':
    exit(0);
    break;
  case 's':
    ++depth;
    if (depth > 5)
      depth =0;
    printf("The subdividing depth is now %d\n", depth);
    glutPostRedisplay();
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
