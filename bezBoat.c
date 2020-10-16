// bezBoat.c

// Modified from bezmesh.c by Sumanta. 
// The changes are all commented.
//
// Mesh data is needed from the file bezBoatData.txt -
// in four steps we go from a flat rectangle to a boat.

#include <stdlib.h>
#include <GL/glut.h>

// Insert control point data from the file bezBoatData.txt below.
// There are 4 sets of data in that file that show the boat
// formed in 4 steps starting with a plane rectangle.

// Step 1
// Just a rectangle lying on the xz (i.e., y=0) plane.
GLfloat ctrlpoints[4][4][3] = {
	{{-2.0, 0.0, 3.0},
	 {-1.0, 0.0, 3.0},
	 {0.0, 0.0, 3.0},
	 {1.0, 0.0, 3.0}},
	{{-2.0, 0.0, 1.0},
	 {-1.0, 0.0, 1.0},
	 {0.0, 0.0, 1.0},
	 {1.0, 0.0, 1.0}},
	{{-2.0, 0.0, -1.0},
	 {-1.0, 0.0, -1.0},
	 {0.0, 0.0, -1.0},
	 {1.0, 0.0, -1.0}},
	{{-2.0, 0.0, -3.0},
	 {-1.0, 0.0, -3.0},
	 {0.0, 0.0, -3.0},
	 {1.0, 0.0, -3.0}},
};

// This routine is no longer called (see below).
void initlights(void)
{
   GLfloat ambient[] = {0.2, 0.2, 0.2, 1.0};
   GLfloat position[] = {0.0, 0.0, 2.0, 1.0};
   GLfloat mat_diffuse[] = {0.6, 0.6, 0.6, 1.0};
   GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
   GLfloat mat_shininess[] = {50.0};

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

   glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
   glLightfv(GL_LIGHT0, GL_POSITION, position);

   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glPushMatrix();
   glRotatef(85.0, 1.0, 1.0, 1.0);
   // Replace GL_FILL with GL_LINE to see the mesh.
   glEvalMesh2(GL_LINE, 0, 20, 0, 20);
   glPopMatrix();
   glFlush();
}

void init(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glEnable(GL_DEPTH_TEST);
   glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
           0, 1, 12, 4, &ctrlpoints[0][0][0]);
   glEnable(GL_MAP2_VERTEX_3);
   glEnable(GL_AUTO_NORMAL);
   glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
   // Turn off the lights - no unnecessary artifacts.
   //initlights();       /* for lighted version only */
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho(-4.0, 4.0, -4.0*(GLfloat)h/(GLfloat)w,
              4.0*(GLfloat)h/(GLfloat)w, -4.0, 4.0);
   else
      glOrtho(-4.0*(GLfloat)w/(GLfloat)h,
              4.0*(GLfloat)w/(GLfloat)h, -4.0, 4.0, -4.0, 4.0);
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
   glutMainLoop();
   return 0;
}
