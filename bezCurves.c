/*
 *  bezCurves.c	
 *  
 *  This program shows Bezier curves of orders (= number of 
 *  control points) from 2 to 6.
 *
 *  Interaction:
 *  Press the up/down arrows to choose the order and then press enter.
 *  Press shift to select (highlight) a control point and then up/down
 *  and left/right arrows to move it.
 *  Press delete to reset.
 */

#include <GL/glut.h>
#include <stdlib.h>
static int count = 0, order = 2, askOrder = 1;
int font=(int)GLUT_BITMAP_8_BY_13;

GLfloat ctrlpoints[6][3] = {
	{ -4.0, 0.0, 0.0}, { -3.0, 0.0, 0.0}, { -1.0, 0.0, 0.0},
	{0.0, 0.0, 0.0}, {3.0, 0.0, 0.0}, { 4.0, 0.0, 0.0}};

// Control point values stored unchanged for use on reset.
GLfloat originalCtrlpoints[6][3] = {
	{ -4.0, 0.0, 0.0}, { -3.0, 0.0, 0.0}, { -1.0, 0.0, 0.0},
	{0.0, 0.0, 0.0}, {3.0, 0.0, 0.0}, { 4.0, 0.0, 0.0}};

void init(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);

}

// Restore control points to original values.
void restoreCtrlpoints(void)
{
	int i, j;
	for (i=0; i<6; i++)
		for (j=0; j<3; j++)
			ctrlpoints[i][j] = originalCtrlpoints[i][j];
}

// Draw text.
void writeBitmapString(void *font, char *string, float rasterx, float rastery) 
{  
		int i = 0; 
		float rx = rasterx, ry = rastery;
		glRasterPos2f(rx, ry);
        while (string[i] != '\0') { 
                glutBitmapCharacter(font, string[i]); 
	
				rx+=glutBitmapWidth(font, string[i]);

				i++;
        } 
} 

void display(void)
{
    char theStringShowBezCurve[] = "Show Bezier curve order";
    char theString2[] = "2";
    char theString3[] = "3";
    char theString4[] = "4";
    char theString5[] = "5";
    char theString6[] = "6";

	float rx = 1.7, ry = 3.5;
	glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

	if (askOrder == 1)
    // First screen.
	{
		writeBitmapString((void*)font, theStringShowBezCurve, -1.7, ry);
		glColor3f(1.0, 0.0, 0.0);
		switch (order) 
		{
		case 2:
			 writeBitmapString((void*)font, theString2, rx, ry);
		break;
		case 3:
			 writeBitmapString((void*)font, theString3, rx, ry);
		break;
		case 4:
			 writeBitmapString((void*)font, theString4, rx, ry);
		break;
		case 5:
			 writeBitmapString((void*)font, theString5, rx, ry);
		break;
		case 6:
			 writeBitmapString((void*)font, theString6, rx, ry);
		break;
		default:
	    break;
		}
	}
	else
    // Second screen.
	{
        int i;
		glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, order, &ctrlpoints[0][0]);
		glEnable(GL_MAP1_VERTEX_3);

		// Define a one-dimensional grid and evaluate on it.
		glMapGrid1f(100, 0.0, 1.0);
		glEvalMesh1(GL_LINE, 0, 100);

		/* Draw the control points as dots. */
		glPointSize(5.0);
		glColor3f(1.0, 1.0, 0.0);
		glBegin(GL_POINTS);
		for (i = 0; i < order; i++) 
			 glVertex3fv(ctrlpoints[i]);
		glEnd();

		// Highlight selected control point,
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_POINTS);
			glVertex3fv(ctrlpoints[count]);     
		glEnd();
	}
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
   case 13:	
     askOrder = 0;
	 glutPostRedisplay();
    break;
   case 127:	
     askOrder = 1; 
	 order = 2;
	 restoreCtrlpoints();
	 glutPostRedisplay();
    break;
  case ' ':
	  if (askOrder == 0)
	  {
		if (count < order-1) count++;
		else count = 0;
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
	{
		if (askOrder == 1) 
		{
			if (order < 6) order += 1;
		}
		else
			ctrlpoints[count][1] += 0.1f;
	}
	if(key == GLUT_KEY_DOWN)
	{
		if (askOrder == 1) 
		{
			if (order > 2) order -= 1;
		}
		else
			ctrlpoints[count][1] -= 0.1f;
	}
	if(key == GLUT_KEY_LEFT)
		ctrlpoints[count][0] -= 0.1f;
	if(key == GLUT_KEY_RIGHT)
		ctrlpoints[count][0] += 0.1f;
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
