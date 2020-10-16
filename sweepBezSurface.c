/*  sweepBezSurface.c
 *  
 *  This program illustrates how a Bezier surface is swept out by
 *  Bezier curves.
 *
 *  Interaction: Press the left/right or up/down keys to move the
 *  sweeping curve. Press the shift key to toggle between sweeping
 *  the surface in either direction.
 */
#include <stdlib.h>
#include <GL/glut.h>

GLfloat t =0.0;
GLint leftright = 1;

GLfloat ctrlpointsSurf[4][4][3] = {
   { {-3.0, -2.0, 4.0},
     {-1.0, 2.0, 4.0},
     {1.0, -2.0, 4.0},
     {3.0, 2.0, 4.0}},
   { {-3.0, -5.0, 3.0},
     {-1.0, -1.0, 3.0},
     {1.0, -5.0, 3.0},
     {3.0, -1.0, 3.0}},
   { {-3.0, -2.0, 2.0},
     {-1.0, 2.0, 2.0},
     {1.0, -2.0, 2.0},
     {3.0, 2.0, 2.0}},
   { {-3.0, -5.0, 1.0},
     {-1.0, -1.0, 1.0},
     {1.0, -5.0, 1.0},
     {3.0, -1.0, 1.0}}
};

GLfloat ctrlpointsSurfTemp[4][4][3];

GLfloat ctrlpointsMovingCurv[4][3]; 
GLfloat ctrlpointsCurv0[4][3]; 
GLfloat ctrlpointsCurv1[4][3]; 
GLfloat ctrlpointsCurv2[4][3]; 
GLfloat ctrlpointsCurv3[4][3]; 

void computeFixedCurvs(void)
{
	int i, j;
    for (i = 0; i < 4; i++)
		for (j = 0; j < 3; j++)
		{
			ctrlpointsCurv0[i][j] = ctrlpointsSurf[i][0][j];
			ctrlpointsCurv1[i][j] = ctrlpointsSurf[i][1][j];
			ctrlpointsCurv2[i][j] = ctrlpointsSurf[i][2][j];
			ctrlpointsCurv3[i][j] = ctrlpointsSurf[i][3][j];
		}
}

void flipCtrlpointsSurf(void)
{
	int i, j, k;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
				for (k = 0; k < 3; k++)
					ctrlpointsSurfTemp[i][j][k] = ctrlpointsSurf[j][i][k];
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
				for (k = 0; k < 3; k++)
					ctrlpointsSurf[i][j][k] = ctrlpointsSurfTemp[i][j][k];
}


void computeMovingCurv(void)
{
	GLfloat s = 1.0 - t;
	int i, j;
	for (j = 0; j < 3; j++)
		for (i = 0; i < 4; i++)
			ctrlpointsMovingCurv[i][j] =     
			                           s * s * s * ctrlpointsSurf[0][i][j]
								 + 3 * s * s * t * ctrlpointsSurf[1][i][j]
								 + 3 * s * t * t * ctrlpointsSurf[2][i][j]
								 +     t * t * t * ctrlpointsSurf[3][i][j];
}

void display(void)
{
   int i;
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glPushMatrix();
   glTranslatef(0.0, 2.0, 0.0);
   glRotatef(75.0, 0.0, 0.0, 1.0);
   
   glPointSize(5.0);
   glColor3f(1.0, 1.0, 0.0);
   glBegin(GL_POINTS);
      for (i = 0; i < 4; i++) 
			glVertex3fv(ctrlpointsSurf[i][0]);
   glEnd();
   glColor3f(1.0, 0.0, 0.0);
   glBegin(GL_POINTS);
      for (i = 0; i < 4; i++) 
			glVertex3fv(ctrlpointsSurf[i][1]);
   glEnd();
   glColor3f(0.0, 1.0, 0.0);
   glBegin(GL_POINTS);
      for (i = 0; i < 4; i++) 
			glVertex3fv(ctrlpointsSurf[i][2]);
   glEnd();
   glColor3f(0.0, 0.0, 1.0);
   glBegin(GL_POINTS);
      for (i = 0; i < 4; i++) 
			glVertex3fv(ctrlpointsSurf[i][3]);
   glEnd();

   glColor3f(0.25, 0.25, 0.25);
   glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
           0, 1, 12, 4, &ctrlpointsSurf[0][0][0]);
   glEnable(GL_MAP2_VERTEX_3);
   glMapGrid2f(50, 0.0, 1.0, 50, 0.0, 1.0);
   glEvalMesh2(GL_LINE, 0, 50, 0, (int)(t*50.0) );

   glColor3f(1.0, 1.0, 0.0);
   glMap1f(GL_MAP1_VERTEX_3, 0, 1, 3, 4, &ctrlpointsCurv0[0][0]);
   glEnable(GL_MAP1_VERTEX_3);
   glMapGrid1f(30, 0.0, 1.0);
   glEvalMesh1(GL_LINE, 0, 30);
   glColor3f(1.0, 1.0, 1.0);

   glColor3f(1.0, 0.0, 0.0);
   glMap1f(GL_MAP1_VERTEX_3, 0, 1, 3, 4, &ctrlpointsCurv1[0][0]);
   glEnable(GL_MAP1_VERTEX_3);
   glMapGrid1f(30, 0.0, 1.0);
   glEvalMesh1(GL_LINE, 0, 30);
   glColor3f(1.0, 1.0, 1.0);

   glColor3f(0.0, 1.0, 0.0);
   glMap1f(GL_MAP1_VERTEX_3, 0, 1, 3, 4, &ctrlpointsCurv2[0][0]);
   glEnable(GL_MAP1_VERTEX_3);
   glMapGrid1f(30, 0.0, 1.0);
   glEvalMesh1(GL_LINE, 0, 30);
   glColor3f(1.0, 1.0, 1.0);

   glColor3f(0.0, 0.0, 1.0);
   glMap1f(GL_MAP1_VERTEX_3, 0, 1, 3, 4, &ctrlpointsCurv3[0][0]);
   glEnable(GL_MAP1_VERTEX_3);
   glMapGrid1f(30, 0.0, 1.0);
   glEvalMesh1(GL_LINE, 0, 30);
   glColor3f(1.0, 1.0, 1.0);

   glPointSize(8.0);
   glColor3f(0.0, 0.0, 1.0);
   glBegin(GL_POINTS);
        glColor3f(1.0, 1.0, 0.0);
		glVertex3fv(ctrlpointsMovingCurv[0]);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3fv(ctrlpointsMovingCurv[1]);
        glColor3f(0.0, 1.0, 0.0);
		glVertex3fv(ctrlpointsMovingCurv[2]);
        glColor3f(0.0, 0.0, 1.0);
		glVertex3fv(ctrlpointsMovingCurv[3]);
   glEnd();

   glColor3f(1.0, 1.0, 1.0);
   glMap1f(GL_MAP1_VERTEX_3, 0, 1, 3, 4, &ctrlpointsMovingCurv[0][0]);
   glEnable(GL_MAP1_VERTEX_3);
   glMapGrid1f(30, 0.0, 1.0);
   glEvalMesh1(GL_LINE, 0, 30);
   glLineWidth(1.0);

   glPopMatrix();
   glFlush();
}

void init(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   computeMovingCurv();
   computeFixedCurvs();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   
   gluLookAt(4.0, 5.0, 9.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case ' ':
         flipCtrlpointsSurf();
         computeMovingCurv();
         computeFixedCurvs();
		 leftright = 1 - leftright;
		 glutPostRedisplay();
         break;
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

void specialKeys(int key, int x, int y)
{
	if (leftright == 1)
	{
		if(key == GLUT_KEY_LEFT) 
			if (t > 0.01) t -= 0.02f;
		if(key == GLUT_KEY_RIGHT)
			if (t < 0.98) t += 0.02f;
	}
	if (leftright == 0)
	{
		if(key == GLUT_KEY_DOWN) 
			if (t > 0.01) t -= 0.02f;
		if(key == GLUT_KEY_UP)
			if (t < 0.98) t += 0.02f;
	}
	computeMovingCurv();
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (500, 500);
   glutInitWindowPosition (100, 100);
   glutCreateWindow(argv[0]);
   init();
   glutReshapeFunc(reshape);
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(specialKeys);
   glutMainLoop();
   return 0;
}
