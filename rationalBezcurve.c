
// rationalBezcurve.c	

// Displays a rational Bezier curve with 6 control points, all on the xy-plane.
// Press shift key to select a control point. Use arrow keys to move
// a control point on the xy-plane. Press 'W' to increase w(eight) of a 
// control point, press 'w' to decrease weight. If the weight of a control
// point becomes 0 the program *exits*


#include <GL/glut.h>
#include <stdlib.h>
static int count = 0;

GLfloat ctrlpoints4d[6][4] = {
	{ -4.0, 0.0, 0.0, 1.0}, { -3.0, 0.0, 0.0, 1.0}, { -1.0, 0.0, 0.0, 1.0},
	{0.0, 0.0, 0.0, 1.0}, {3.0, 0.0, 0.0, 1.0}, { 4.0, 0.0, 0.0, 1.0}};

GLfloat ctrlpoints3d[6][3] = {
	{ -4.0, 0.0, 0.0}, { -3.0, 0.0, 0.0}, { -1.0, 0.0, 0.0},
	{0.0, 0.0, 0.0}, {3.0, 0.0, 0.0}, { 4.0, 0.0, 0.0}};

GLfloat weights[6] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0};

void init(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);

}

void computeCtrlpoints4d(void)
{
	int i, j;
	for (i = 0; i < 6; i++)
		for (j = 0; j < 2; j++)
		{
			ctrlpoints4d[i][j] = ctrlpoints3d[i][j] * weights[i];
			ctrlpoints4d[i][3] = weights[i];
		}
}

void display(void)
{
   int i;
   glMap1f(GL_MAP1_VERTEX_4, 0.0, 1.0, 4, 6, &ctrlpoints4d[0][0]);
   glEnable(GL_MAP1_VERTEX_4);

   // Define a one-dimensional grid.
   glMapGrid1f(100, 0.0, 1.0);
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(1.0, 1.0, 1.0);

   glEvalMesh1(GL_LINE, 0, 100);

   /* The following code displays the control points as dots. */
   glPointSize(5.0);
   glColor3f(1.0, 1.0, 0.0);
   glBegin(GL_POINTS);
      for (i = 0; i < 6; i++) 
         glVertex3fv(ctrlpoints3d[i]);
   glEnd();
   glColor3f(1.0, 0.0, 0.0);
   glBegin(GL_POINTS);
   glVertex3fv(ctrlpoints3d[count]);     
   glEnd();
   glFlush();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho(-5.0, 5.0, -5.0*(GLfloat)h/(GLfloat)w, 
               5.0*(GLfloat)h/(GLfloat)w, -5.0, 5.0);
   else
      glOrtho(-5.0*(GLfloat)w/(GLfloat)h, 
               5.0*(GLfloat)w/(GLfloat)h, -5.0, 5.0, -5.0, 5.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
   case 27:	
    exit(0);
    break;
  case ' ':
	 if (count < 5) count++;
	 else count = 0;
    glutPostRedisplay();
    break;
  case 'W':
	weights[count] += 0.1f;
	computeCtrlpoints4d();
    glutPostRedisplay();
    break;
  case 'w':
	weights[count] -= 0.1f;
	if ( weights[count] < 0.1 ) exit(0);
	computeCtrlpoints4d();
    glutPostRedisplay();
    break;
  default:
    break;
  }
}

void SpecialKeys(int key, int x, int y)
	{
	if(key == GLUT_KEY_UP)
		ctrlpoints3d[count][1] += 0.1f;
	if(key == GLUT_KEY_DOWN)
		ctrlpoints3d[count][1] -= 0.1f;
	if(key == GLUT_KEY_LEFT)
		ctrlpoints3d[count][0] -= 0.1f;
	if(key == GLUT_KEY_RIGHT)
		ctrlpoints3d[count][0] += 0.1f;
	computeCtrlpoints4d();
	glutPostRedisplay();
	}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (600, 600);
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc (keyboard);
   glutSpecialFunc(SpecialKeys);
   glutMainLoop();
   return 0;
}
