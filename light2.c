/*
 *  light2.c 
 *  This is modified from light.c of the red book by Sumanta.
 *  As it stands now it is *exacty same* as light.c - a single 
 *  directional light source illuminating a grey sphere.
 *
 *  HOWEVER, there are 3 sets of additional statements that you 
 *  should *successively* incorporate, by uncommenting out the 
 *  corresponding blocks of code. Additional statements are 
 *  indicated by a preceding comment line. Additional variables
 *  are not separately indicated, but have all been initialized
 *  at the top of the init procedure.
 *
 *  1st set - adds an ambient component to both material and light 0.
 *  2nd set - adds a second light, which is a positional spotlight.
 *  3rd set - raises the global ambient light.
 */
#include <GL/glut.h>
#include <stdlib.h>

/*  Initialize material property, light source, lighting model,
 *  and depth buffer.
 */
void init(void) 
{
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 50.0 };
   GLfloat mat_ambient_and_diffuse[] = {0.3, 0.3, 0.3, 1.0}; 

   GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
   GLfloat light_ambient[] = {0.5, 0.5, 0.5, 1.0}; 

   GLfloat light1_position[] = { -2.0, 0.0, 2.0, 1.0 };
   GLfloat spot_direction[] = {2.0, 0.0, -2.0}; 

   GLfloat lmodel_ambient[] = {0.5, 0.5, 0.5, 1.0}; 

   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
/* Next statement belongs to 1st set of additions to light.c */
/* glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient_and_diffuse); */

   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
/* Next statement belongs to 1st set of additions to light.c */
/* glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient); */

/* Next group belongs to 2nd set of additions to light.c */
/* glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
   glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient); 
   glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 10.0);
   glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction); */

/* Next statement belongs to 3rd set of additions to light.c */
/* glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient); */

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
/* Next statement belongs to 2nd set of additions to light.c */
/* glEnable(GL_LIGHT1); */

   glEnable(GL_DEPTH_TEST);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glutSolidSphere (1.0, 20, 16);
   glFlush ();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,
         1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
   else
      glOrtho (-1.5*(GLfloat)w/(GLfloat)h,
         1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
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

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}





