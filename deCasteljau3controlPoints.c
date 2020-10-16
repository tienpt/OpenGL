/*
 *  deCasteljau3controlPoints.c
 *
 *  This program illustrates de Casteljau's algorithm to create a 2nd degree
 *  Bezier curve approximating 3 control points.
 *
 *  Interaction: 
 *  Press the left/right arrows to decrease/increase the parameter. 
 */

#include <GL/glut.h>
#include <stdlib.h>

GLfloat ctrlpoints[3][3] = {
	{ -4.0, -2.0, 0.0}, { 0.0, 4.0, 0.0}, {4.0, -2.0, 0.0}};
GLfloat t = 0.0; // Curve parameter.

void init(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);

}

void display(void)
{
   int i;

   glClear(GL_COLOR_BUFFER_BIT);

   // The Bezier curve is drawn from 0 to parameter value.
   glColor3f(0.5, 0.5, 0.5);
   glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 3, &ctrlpoints[0][0]);
   glEnable(GL_MAP1_VERTEX_3);
   glMapGrid1f(100, 0.0, 1.0);
   glEvalMesh1(GL_LINE, 0, (int)(t*100));

   // The following code displays the control points as dots.
   glPointSize(5.0);
   glColor3f(1.0, 1.0, 0.0);
   glBegin(GL_POINTS);
      for (i = 0; i < 3; i++) 
         glVertex3fv(&ctrlpoints[i][0]);
   glEnd();

   // The lines joining the control points.
   glColor3f(1.0, 1.0, 1.0);
   glBegin(GL_LINE_STRIP);
      for (i = 0; i < 3; i++) 
         glVertex3fv(&ctrlpoints[i][0]);
   glEnd();

   glColor3f(1.0, 0.0, 0.0);

   // The point interpolating between the first two control points.
   glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 2, &ctrlpoints[0][0]);
   glEnable(GL_MAP1_VERTEX_3);
   glBegin(GL_POINTS);
      glEvalCoord1f(t);
   glEnd();

   // The point interpolating between the last two control points.
   glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 2, &ctrlpoints[1][0]);
   glEnable(GL_MAP1_VERTEX_3);
   glBegin(GL_POINTS);
      glEvalCoord1f(t);
   glEnd();


   glColor3f(0.0, 1.0, 0.0);
   // The line joining the two points drawn above.
   glBegin(GL_LINES);
      glVertex3f( (1-t)*ctrlpoints[0][0] + t*ctrlpoints[1][0],
		          (1-t)*ctrlpoints[0][1] + t*ctrlpoints[1][1],
				   0.0 );
      glVertex3f( (1-t)*ctrlpoints[1][0] + t*ctrlpoints[2][0],
		          (1-t)*ctrlpoints[1][1] + t*ctrlpoints[2][1],
				   0.0 );
   glEnd();

   glColor3f(1.0, 0.0, 0.0);
   // The point interpolating between the two points drawn above.
   glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 3, &ctrlpoints[0][0]);
   glEnable(GL_MAP1_VERTEX_3);
   glBegin(GL_POINTS);
      glEvalCoord1f(t);
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
   }
}

void SpecialKeys(int key, int x, int y)
	{
	if(key == GLUT_KEY_LEFT)
		if ( t > 0.01 ) t-= 0.01;
	if(key == GLUT_KEY_RIGHT)
		if ( t < 0.99 ) t += 0.01;
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
