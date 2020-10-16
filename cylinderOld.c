/*
 * cylinder1.c
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

// TRY YOUR OWN FUNCTION DEFINITIONS AS WELL!!

// The x,y,z co-ordinates of the points to which the grid points are mapped. 
static GLfloat vdata[M+1][N+1][3];
// The i,j grid indices for each vertex of each grid triangle.
static GLuint tindices[2][M][N][3][2];

// Angles used to rotate the cylinder with keyboard entry.
static int Xangle = 0, Yangle = 0, Zangle = 0;

void init (void) 
{
  int i, j;

  glClearColor (0.0, 0.0, 0.0, 0.0);

  /* Define the mapping from grid points to points on the cylinder. */
  for (i = 0; i < M+1; ++i)
    for (j = 0; j < N+1; ++j){
      vdata[i][j][0] = FNX(i,j);
      vdata[i][j][1] = FNY(i,j);
      vdata[i][j][2] = FNZ(i,j);
	}

  /* tindices[0][i][j][k][l] represents the lower triangle in the subrectangle
   * whose lower left corner is grid point (i,j). k runs through 0, 1, 2 corresponding
   * to the 3 vertices of the triangle and l runs through 0, 1 giving the grid 
   * co-ordinates of a vertex.
   * tindices[1][i][j][k][l] similarly represents the upper triangle in the 
   * subrectangle whose lower left corner is grid point (i,j).
   */
  for (i = 0; i < M; ++i)
    for (j = 0; j < N; ++j){
      tindices[0][i][j][0][0] = i;
      tindices[0][i][j][0][1] = j;
      tindices[0][i][j][1][0] = (i+1);
      tindices[0][i][j][1][1] = j;
      tindices[0][i][j][2][0] = (i+1);
      tindices[0][i][j][2][1] = j+1;

      tindices[1][i][j][0][0] = i;
      tindices[1][i][j][0][1] = j+1;
      tindices[1][i][j][1][0] = i;
      tindices[1][i][j][1][1] = j;
      tindices[1][i][j][2][0] = (i+1);
      tindices[1][i][j][2][1] = j+1;
    }
}

void display(void)
{
  int h, i, j;

   glClear (GL_COLOR_BUFFER_BIT);

   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

   glColor3f (1.0, 1.0, 1.0);
   
   glPushMatrix();
   glRotatef ((GLfloat) Zangle, 0.0, 0.0, 1.0);
   glRotatef ((GLfloat) Yangle, 0.0, 1.0, 0.0);
   glRotatef ((GLfloat) Xangle, 1.0, 0.0, 0.0);

  // Draw the 2MN triangles.
  glBegin(GL_TRIANGLES);
  for (h = 0; h < 2; ++h)
     for (i = 0; i < M; ++i)
       for (j = 0; j < N; ++j){
	 glVertex3fv( vdata[ tindices[h][i][j][0][0] ][ tindices[h][i][j][0][1] ] );
	 glVertex3fv( vdata[ tindices[h][i][j][1][0] ][ tindices[h][i][j][1][1] ] );
	 glVertex3fv( vdata[ tindices[h][i][j][2][0] ][ tindices[h][i][j][2][1] ] );
       }
  glEnd();
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
   glutCreateWindow ("cylinder1");
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;  
}
