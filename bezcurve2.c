/*
 * bezcurve2.c
 *
 * Modified from bezcurve.c by Sumanta.
 * Illustrates that two Bezier curves meet smoothly when they share
 * an endpoint and the control points adjacent to the shared endpoint,
 * on either curve, lie on a straight segment with the shared endpoint 
 * in between them on the segment.
 *
 * Interaction:
 * Press space to select a control point of second Bezier curve. 
 * Press the arrow keys to move the selected control point.
 */

#include <GL/glut.h>
#include <stdlib.h>
static int count = 0;

// Control points for the first curve.
GLfloat ctrlpoints1[4][3] = {
	{ -4.0, -4.0, 0.0}, { -3.0, 2.0, 0.0}, 
	{-1.0, 0.0, 0.0}, {0.0, 2.0, 0.0}};

// Control points for the second curve.
GLfloat ctrlpoints2[4][3] = {
	{ 0.0, 1.0, 0.0}, { 2.0, 4.0, 0.0}, 
	{2.0, 1.0, 0.0}, {4.0, -1.0, 0.0}};

void init(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
}

void display(void)
{
   int i;

   glClear(GL_COLOR_BUFFER_BIT);

   // Draw the first curve in red.
   glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints1[0][0]);
   glEnable(GL_MAP1_VERTEX_3);
   glColor3f(0.0, 1.0, 0.0);
   glBegin(GL_LINE_STRIP);
      for (i = 0; i <= 30; i++) 
         glEvalCoord1f((GLfloat) i/30.0);
   glEnd();

   // Draw the second curve in blue.
   glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints2[0][0]);
   glEnable(GL_MAP1_VERTEX_3);
   glColor3f(0.0, 0.0, 1.0);
   glBegin(GL_LINE_STRIP);
      for (i = 0; i <= 30; i++) 
         glEvalCoord1f((GLfloat) i/30.0);
   glEnd();


   /* The following code displays the control points as dots. */
   // Control points of the first curve are red, of the second
   // curve are blue, and the shared point is yellow.
   glPointSize(5.0);
  
   glColor3f(0.0, 1.0, 0.0);
   glBegin(GL_POINTS);
      for (i = 0; i < 4; i++) 
         glVertex3fv(&ctrlpoints1[i][0]);
   glColor3f(0.0, 0.0, 1.0);
      for (i = 0; i < 4; i++) 
         glVertex3fv(&ctrlpoints2[i][0]);
   glColor3f(1.0, 0.0, 0.0);
      glVertex3fv(&ctrlpoints2[count][0]);     
   glEnd();

   // Draw a white dashed line for the common tangent.
   glEnable(GL_LINE_STIPPLE);
   glColor3f(0.25, 0.25, 0.25);
   glLineStipple(1, 0x00FF);
   glBegin(GL_LINES);
      glVertex3f(-3.5, -5.0, 0.0);
      glVertex3f(1.5, 5.0, 0.0);
   glEnd();
   glDisable(GL_LINE_STIPPLE);

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
	 if (count < 3) count++;
	 else count = 0;
    glutPostRedisplay();
  default:
    break;
   }
}

void SpecialKeys(int key, int x, int y)
	{
	if(key == GLUT_KEY_UP)
		ctrlpoints2[count][1] += 0.1f;
	if(key == GLUT_KEY_DOWN)
		ctrlpoints2[count][1] -= 0.1f;
	if(key == GLUT_KEY_LEFT)
		ctrlpoints2[count][0] -= 0.1f;
	if(key == GLUT_KEY_RIGHT)
		ctrlpoints2[count][0] += 0.1f;
	glutPostRedisplay();
	}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (500, 500);
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
