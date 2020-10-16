/*
 * shear.c
 * This program animates a cube shearing as it "strikes" a sphere. 
 * The sphere matrix is explicitly computed and applied by 
 * multiplying the current modelview matrix.
 *  
 * Interaction: Press 's' and 'S' to move forward and backward
 * through the animation.
 */

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

static float angle = 0.0;

/* The shear matrix - see our notes on shears. Here the line of shear
 * is the x-axis and the shearing plane is the xz-plane. Keep in mind
 * that the OpenGL modelview matrix is represented in column-major 
 * form, ie., 
 * matrixdata[0][0], matrixdata[1][0], matrixdata[2][0], matrixdata[3][0],
 * matrixdata[0][1], etc.
 */
static GLfloat matrixdata[16] = {
1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0
};

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);
   glColor3f (1.0, 1.0, 1.0);
   glLoadIdentity ();          
   gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   /* A stationary wire sphere */
   glutWireSphere(0.2, 10, 8);

   /* The cube is multiplied by the shear matrix (ie., sheared)
    * and then translated to keep it touching the sphere.
    */
   glTranslatef(0.7 - 0.25*tan(angle), -0.3, 0.0);
   glMultMatrixf(matrixdata);
   glutWireCube (1.0);

   glFlush ();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
   glMatrixMode (GL_MODELVIEW);
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
     /* Only the entry matrixdata[4] needs to be updated -
      * see our notes for the explicit form of the shear matrix
      * when the line of shear is the x-axis, the plane 
      * is the xz-plane and the shearing angle is given.
      * Note: we limit the shear in both directions.
      */
      case 's':
         if (angle < 1.0) {
	   angle += 0.05;
	   matrixdata[4] = tan(angle);
	 }
         glutPostRedisplay();
         break;
      case 'S':
         if (angle >= 0.05) {
	   angle -= 0.05;
	   matrixdata[4] = tan(angle);
	 }
         glutPostRedisplay();
         break;
      case 27:
         exit(0);
         break;
      default:
         break;
   }
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
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
