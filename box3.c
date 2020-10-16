/* box3.c
 * This program draws a red box and then draws a green sphere within 
 * the box. The top face of the box is opened INCREMENTALLY by pressing 
 * 'o' and closed by pressing 'c. 'e' = exit. 
 * NOTE:
 * (1) This program is identical to box2.c except for 
 *     (a) incremental opening, and
 *     (b) different normals at the vertices of the top of the box.
 * (2) Also see comments in box1.c and box2.c.
 */

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define PI 3.14159265

static int Step = 0;

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
  double angle, Y, Z, NY, NZ;

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

  // Five sides of the box, excluding the top:
  glBegin(GL_QUADS);
  for (i = 0; i < 5; ++i){
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
  
  angle = ((float)Step/120) * PI;
  Y = 1 + 2 * sin(angle);
  Z = -1 + 2 * cos(angle);
  NY = cos(angle);
  NZ = -sin(angle);

  // The top of the box:
  glBegin(GL_QUADS);
    glNormal3f (0, NY, NZ);
    glVertex3f (1.0, Y, Z);
    glNormal3f (0, NY, NZ);
    glVertex3f (1.0, 1.0, -1.0);
    glNormal3f (0, NY, NZ);
    glVertex3f (-1.0, 1.0, -1.0);
    glNormal3f (0, NY, NZ);
    glVertex3f (-1.0, Y, Z);
glEnd();

/* material lighting properties are specified for the sphere */
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular2);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess2);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);

  glutSolidSphere (1.0, 20.0, 16.0);
  glutSwapBuffers();
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

/* Enable two-sided lighting */
   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

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
    if (Step < 120) Step++;
    glutPostRedisplay();
    break;
  case 'c':
    if (Step > 0) Step--;
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
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
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
