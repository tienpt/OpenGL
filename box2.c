/* box2.c
 * This program draws a red box and then draws a green sphere within 
 * the box. The top face of the box is drawn by pressing 'c' to close the box, and
 * not drawn by pressing 'o' to open the box. 'e' = exit. 
 * NOTE:
 * (1) There is ONE LIGHT SOURCE to give a better 3D effect than box1.c 
 * (search keyword "light"). See also specification of normal vectors.
 * (2) Also see comments in box1.c.
 */

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

static int N = 6;

void display();

static GLfloat vdata[8][3] = {
  {1.0, -1.0, 1.0}, {1.0, 1.0, 1.0}, {1.0, 1.0, -1.0}, {1.0, -1.0, -1.0}, 
  {-1.0, -1.0, 1.0}, {-1.0, 1.0, 1.0}, {-1.0, 1.0, -1.0}, {-1.0, -1.0, -1.0}
};

static GLuint tindices[6][4] = {
  {3,2,1,0}, {7,6,2,3}, {4,5,6,7}, {0,1,5,4}, {4,7,3,0}, {6,5,1,2} 
};

void display(){
  int i;

/* vectors are defined to be used to specify material lighting properties */ 
  GLfloat mat_specular1[] = { 1.0, 0.0, 0.0, 1.0 };
  GLfloat mat_shininess1[] = { 50.0 };
  GLfloat mat_diffuse1[] = {0.9, 0.0, 0.0};
  GLfloat mat_specular2[] = { 0.0, 1.0, 0.0, 1.0 };
  GLfloat mat_shininess2[] = { 50.0 };
  GLfloat mat_diffuse2[] = {0.0, 0.9, 0.0};

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

/* material lighting properties are specified for the box */
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular1);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess1);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);

/* preceding each vertex definition is a normal vector definition, which 
 * is the specification of a normal direction to the surface at that vertex.
 * This is required as lighting has been enabled. Normal vectors are
 * used by OpenGL to calculate how the light striking an object is
 * reflected to a viewer. 
 * In this example, we use the co-ordinates of a vertex itself
 * to define its normal vector - this is simply the outward pointing
 * vector from the origin to the vertex, a so-so choice in this case.
 */
  glBegin(GL_QUADS);
  for (i = 0; i < N; ++i){
    glNormal3fv(vdata[tindices[i][0]]);  
    glVertex3fv(vdata[tindices[i][0]]);
    glNormal3fv(vdata[tindices[i][1]]);  
    glVertex3fv(vdata[tindices[i][1]]);
    glNormal3fv(vdata[tindices[i][2]]);  
    glVertex3fv(vdata[tindices[i][2]]);
    glNormal3fv(vdata[tindices[i][3]]);
    glVertex3fv(vdata[tindices[i][3]]);  
}
  glEnd();

/* material lighting properties are specified for the sphere */
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular2);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess2);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);

  glutSolidSphere (1.0, 20.0, 16.0);
  glFlush();
}

void init(void)
{
   GLfloat ambient[] = { 0.1, 0.1, 0.1, 1.0 };
   GLfloat diffuse[] = { 1.0, 1.0, 0.0, 1.0 };
   GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat position[] = { 0.0, 1.0, 3.0, 0.0 };
    
   GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };

/* Define properties of the light source */
   glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
   glLightfv(GL_LIGHT0, GL_POSITION, position);
    
/* Define properties of the ambient light */
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
   gluLookAt (0.0, 3.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

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


