/*
 *  splineCurveOrder4.c
 *
 *  This program draws a 4th order B-spline approximation of 9 control points.
 *  The B-spline curve is shown in red. At the bottom there are 13 white 
 *  horizontal bars corresponding, from bottom to top, to the first through
 *  thirteenth knot points.
 *
 *  Interaction: 
 *  Press 'c' to enter control points mode. In this mode the selected control 
 *  point (in red) can be moved using the left/right and up/down arrow keys. 
 *  Pressing the shift key cycles through the control points.
 *  Press 'k' to enter knot points mode. In this mode the value of the 
 *  selected knot can be changed using the left/right keys from a minimum
 *  of 0 to a maximum of 80. Pressing the shift key cycles through the knot 
 *  points.
 */

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef CALLBACK
#define CALLBACK
#endif

static int changeControls = 1;
static int countControls = 0;
static int countKnots = 0;

GLfloat ctrlpoints[9][3] = {
	{-4.0, 1.0, 0.0}, {-3.0, 1.0, 0.0}, {-2.0, 1.0, 0.0},
	{-1.0, 1.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 1.0, 0.0},
	{2.0, 1.0, 0.0}, {3.0, 1.0, 0.0}, { 4.0, 1.0, 0.0}};
GLfloat knots[13] = {0.0, 7.0, 14.0, 21.0, 28.0, 35.0, 41.0, 47.0, 53.0, 59.0, 65.0, 73.0, 80.0};
GLUnurbsObj *theNurb;

void CALLBACK nurbsError(GLenum errorCode)
{
   const GLubyte *estring;

   estring = gluErrorString(errorCode);
   fprintf (stderr, "Nurbs Error: %s\n", estring);
   exit (0);
}
			
void init(void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   theNurb = gluNewNurbsRenderer();
   gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 25.0);
   gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_OUTLINE_POLYGON);
   gluNurbsCallback(theNurb, GLU_ERROR, 
                    nurbsError);
}

// Function to increase value of a knot.
void increaseKnot(int i)
{
	if ( (i < 12) )
	{
		if (knots[i] < knots[i+1]) knots[i] += 1.0;
		else 
		{
			increaseKnot(i+1);
			if (knots[i] < knots[i+1]) knots[i] += 1.0;
		}
	}
	if ( (i == 12 )  && ( knots[i] < 80.0) )    knots[i] += 1.0;
}

// Function to decrease value of a knot.
void decreaseKnot(int i)
{
	if ( (i > 0) )
	{
		if (knots[i] > knots[i-1]) knots[i] -= 1.0;
		else 
		{
			decreaseKnot(i-1);
			if (knots[i] > knots[i-1]) knots[i] -= 1.0;
		}
	}
	if ( (i == 0 )  && ( knots[i] > 0.0) )    knots[i] -= 1.0;
}

void display(void)
{
   int i;
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glPushMatrix();
   
   glColor3f(1.0, 0.0, 0.0);
   gluBeginCurve(theNurb);
   gluNurbsCurve(theNurb, 
                   13, knots,
                   3, &ctrlpoints[0][0], 
                   4, GL_MAP1_VERTEX_3);
   gluEndCurve(theNurb);

   // The following code displays the control points as dots.
   glPointSize(5.0);
   glColor3f(1.0, 1.0, 0.0);
   glBegin(GL_POINTS);
      for (i = 0; i < 9; i++) 
         glVertex3fv(ctrlpoints[i]);
   glEnd();

   // Highlight the selected control point.
   if (changeControls == 1)
   {
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_POINTS);
			glVertex3fv(ctrlpoints[countControls]);     
		glEnd();
   }
 
   // Draw horizontal bars corresponding to knot points.
   glColor3f(1.0, 1.0, 1.0);
   glBegin(GL_LINES);
      for (i = 0; i < 13; i++) 
	  {
        glVertex3f(-4.0, -4.5 + (float)i * 0.1, 0.0);
        glVertex3f( 4.0, -4.5 + (float)i * 0.1, 0.0);
	  }
   glEnd();

   // Draw the knot points as dots on their respective bars.
   glColor3f(0.0, 1.0, 0.0);
   glBegin(GL_POINTS);
      for (i = 0; i < 13; i++) 
         glVertex3f( -4.0 + knots[i]/10.0, -4.5 + (float)i * 0.1, 0.0);
   glEnd();

   // Highlight the selected knot point.
   if (changeControls == 0)
   {
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_POINTS);
			 glVertex3f( -4.0 + knots[countKnots]/10.0, -4.5 + (float)countKnots * 0.1, 0.0);     
		glEnd();
   }

   glPopMatrix();
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
  case 'k':
     if (changeControls == 1)  changeControls = 0;
    glutPostRedisplay();
    break;
  case 'c':
     if (changeControls == 0)  changeControls = 1;
    glutPostRedisplay();
    break;
  case ' ':
     if (changeControls == 1)
	 {
		 if (countControls < 8) countControls++;
		 else countControls = 0;
	 }
	 else
	 {
		 if (countKnots < 12) countKnots++;
		 else countKnots = 0;
	 }
    glutPostRedisplay();
    break;
  default:
    break;
  }
}

void SpecialKeys(int key, int x, int y)
	{
	if(key == GLUT_KEY_UP)
		if (changeControls == 1) ctrlpoints[countControls][1] += 0.1f;
	if(key == GLUT_KEY_DOWN)
		if (changeControls == 1) ctrlpoints[countControls][1] -= 0.1f;
	if(key == GLUT_KEY_LEFT)
	{
		if (changeControls == 1) ctrlpoints[countControls][0] -= 0.1f;
		else decreaseKnot(countKnots);
	}
	if(key == GLUT_KEY_RIGHT)
	{
		if (changeControls == 1) ctrlpoints[countControls][0] += 0.1f;
		else increaseKnot(countKnots);
	}
	glutPostRedisplay();
	}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (600, 600);
   glutInitWindowPosition (100, 100);
   glutCreateWindow(argv[0]);
   init();
   glutReshapeFunc(reshape);
   glutDisplayFunc(display);
   glutKeyboardFunc (keyboard);
   glutSpecialFunc(SpecialKeys);
   glutMainLoop();
   return 0; 
}
