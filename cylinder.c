/*
 * cylinder.c
 * A cylinder is drawn by first tesselating (=triangulating) a grid
 * and then mapping points of the grid on to the cylinder.
 */

/* Use the x, X, y, Y, z, Z keys to turn the cylinder. */

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
 
#define PI 3.14159265358979324

/* 
 * The parameter space is the unit plane square with corners at (0,0) and (1,1).
 * Create an M x N grid of subrectangles of the square. Each subrectangle is
 * further subdivided into 2 triangles. There are M subrectangles horizontally
 * and N subrectangles vertically. 
 * The total number of triangles is 2MN (2 per subrectangle).
 */ 
#define M  25  
#define N  15

/* Define the parametrizing fuction that maps the parameter point (i/M, j/N)
 * on the plane square to the point (FNX(i,j), FNY(i,j), FNZ(i,j)) on the cylinder.
 */

 //The two vertical sides of the square
 //are wrapped by this parametrizing function one on to the other.
 #define FNX(i,j) ( cos( ( (float) i/M ) * 2 * PI) )
 #define FNY(i,j) ( sin( ( (float) i/M ) * 2 * PI) ) 
 #define FNZ(i,j) ( 3.0 * (float) j/N )

/* Comment out the preceding block and uncomment the next block to see new
 * functions for FNX, FNY and FNZ.
 *
 *#define FNX(i,j) ( 3.0 * (float) j/N * cos( ( (float) i/M ) * 2 * PI) )
 *#define FNY(i,j) ( 3.0 * (float) j/N * sin( ( (float) i/M ) * 2 * PI) ) 
 *#define FNZ(i,j) ( 3.0 * (float) j/N )
 */

// Try the functions defined in the file cylinderFunctions.txt.
// Try your own function definitions as well!!

// Vertex array: the x,y,z co-ordinates of the points to which the grid points 
// are mapped. 
static GLfloat vdata[3*(M+1)*(N+1)];

// Angles used to rotate the cylinder with keyboard entry.
static int Xangle = 0, Yangle = 0, Zangle = 0;

void init (void) 
{
  int i, j, k;

  glClearColor (0.0, 0.0, 0.0, 0.0);
      
  /* x, y, z co-ordinates of the cylinder points (ie., points to
   * which the mesh vertices are mapped) are placed in the vertex array.
   * The order of the points is row-wise, from left to right, starting
   * from the bottom row (j=0), going up.
   */
  k = 0;
  for (j = 0; j <= N; j++)
    for (i = 0; i <= M; i++){
      vdata[k++] = FNX(i,j); 
      vdata[k++] = FNY(i,j);
      vdata[k++] = FNZ(i,j); 
	}  

  glEnableClientState(GL_VERTEX_ARRAY);

  glVertexPointer(3, GL_FLOAT, 0, vdata);
}

void display(void)
{
   int  i, j;
  
   glClear (GL_COLOR_BUFFER_BIT);

   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   glColor3f (1.0, 1.0, 1.0);
   
   glPushMatrix();
   glRotatef ((GLfloat) Zangle, 0.0, 0.0, 1.0);
   glRotatef ((GLfloat) Yangle, 0.0, 1.0, 0.0);
   glRotatef ((GLfloat) Xangle, 1.0, 0.0, 0.0);
   
   /* N triangle strips are drawn corresponding to the
    * N horizontal rows of rectangles. The first (j=0)
    * triangle strips covers the bottom row, and we
    * move upwards strip by strip with increasing j.
    * Note the parameters to glArrayElement() are chosen
    * according to the location of the data for the 
    * appropriate grid point in the vdata array.
    * For example the order of the vertices in the
    * bottom-most strip is (0,1), (0,0), (1,1), (1,0), (2,1), etc.
    */
   for(j = 0; j < N; j++){
     glBegin(GL_TRIANGLE_STRIP);
     for(i = 0; i <= M; i++){
       glArrayElement( (j+1)*(M+1) + i );
       glArrayElement( j*(M+1) + i );
     }
   glEnd();
   }
   glPopMatrix();

  glFlush ();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (0.0, 0.0, 9.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 'x':
         Xangle = (Xangle + 5) % 360;
         glutPostRedisplay();
         break;
      case 'X':
         Xangle = (Xangle - 5) % 360;
         glutPostRedisplay();
         break;
      case 'y':
         Yangle = (Yangle + 5) % 360;
         glutPostRedisplay();
         break;
      case 'Y':
         Yangle = (Yangle - 5) % 360;
         glutPostRedisplay();
         break;
      case 'z':
         Zangle = (Zangle + 5) % 360;
         glutPostRedisplay();
         break;
      case 'Z':
         Zangle = (Zangle - 5) % 360;
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
   glutCreateWindow ("cylinder2");
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;  
}
