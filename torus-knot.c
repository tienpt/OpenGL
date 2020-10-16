

/*
 * torus_knot.c\
 * Developed by Sumanta.
 */
 

/* 
 *README: This program compiles on both O2s and Unix boxes.
 *        but when I run it on a Unix box it gives "floating exception".
 *        I dont know why, but it runs fine on an O2.
 */

/* Use the x, X, y, Y, z, Z keys to turn the knot. */

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
 
#define PI 3.14159265358979324

/* 
 * See triangulated_cylinder.c for use of a similar data structure.
 * The parameter space is the unit plane square with corners at (0,0) and (1,1).
 * An M x N grid is created of subrectangles of the square (each subrectangle to be
 * further subdivided into 2 triangles). There are M subrectangles horizontally
 * and N subrectangles vertically. The two vertical sides of the square
 * will be wrapped by the parametrizing function on to one another.
 * The total number of triangles is 2MN (2 per subrectangle).
 */ 
#define M  875 
#define N  25

/*  
 *  The way to think of the geometry is as follows: a knotted curve is drawn on the surface of a 
 *  (big) torus, then the knot itself is thickened to a thinner, and therefore knotted, torus.
 *  The big torus is not itself drawn, only the thinner knotted torus.
 *  R is the external radius of the big torus on which the knotted curve is drawn, r is the internal
 *  radius of the big torus, ie., radius of the cross-section of the big torus.
 *  The internal radius of the knotted torus itself is rad. 
 */
#define r  2.0
#define R  4.0
#define rad  0.2

static GLfloat vertexdata[M][N][3];
static GLfloat normaldata[M][N][3];
static GLuint  triangledata[2][M][N][3][2];

static int Xangle = 0, Yangle = 0, Zangle = 0;

void init (void) 
{
  int i, j, m, n;
  float n_by_m;
  float delta, phi, theta;
  float dx_dphi, dy_dphi, dz_dphi;
  float normalx, normaly, normalz;

  /*Defining the light source color vectors.*/
  GLfloat ambient[] = { 0.1, 1.0, 0.5, 1.0 };
  GLfloat diffuse[] = { 0.1, 1.0, 0.5, 1.0 };
  GLfloat specular[] = { 0.1, 1.0, 0.5, 1.0 };
  GLfloat position[] = { 2.0, 2.0, 3.0, 0.0 };
    
  GLfloat lmodel_ambient[] = { 0.0, 0.8, 0.4, 1.0 };

  /* Define properties of the light source. */
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
  glLightfv(GL_LIGHT0, GL_POSITION, position);
    
  /* Define properties of the ambient light. */
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   
  glEnable(GL_DEPTH_TEST); 

  glClearColor (0.0, 0.05, 0.0, 0.0);
  glShadeModel (GL_SMOOTH);

  /*Get values for m and n. See comments made in printf. */
  printf("Enter two positive integer values that will specify the displayed torus knot.\n");
  printf("Enter a value for m:\n");
  scanf("%2d", &m);
  printf("Enter a value for n:\n");
  scanf("%2d", &n);

    n_by_m = (float)n/m;

  /* Define the mapping from grid points to points on the cylinder, 
   * and to corresponding normal vectors. 
   */
  for (i = 0; i < M; ++i)
    for (j = 0; j < N; ++j){
      /* 
       * The big torus is parametrized by phi and gamma, say. The knot is the image on the
       * big torus of the straight line from (0,0) to (2m*pi, 2n*pi) on the phi-gamma plane. 
       * In other words, the knot winds m times around the phi direction of the torus at the same time
       * that it winds n times around the gamma direction. The knot can therefore be
       * parametrized by phi (using the straight line equation to write gamma in terms of phi),
       * while the knotted torus which has the knot along its centre is parametrized by phi and theta.
       */
      phi =   ((float)i/M)*2*m*PI;
      theta = ((float)j/N)*2*PI;
      
      /* Direction of the tangent to the knot (which is parametrized by phi). */
      dx_dphi = (-r * sin(phi) * cos((n_by_m)*phi)) - (n_by_m * (R + r*cos(phi)) * sin((n_by_m)*phi));
      dy_dphi = (-r * sin(phi) * sin((n_by_m)*phi)) + (n_by_m * (R + r*cos(phi)) * cos((n_by_m)*phi));
      dz_dphi = r * cos(phi);

      delta = atan2(dx_dphi * cos(theta) + dy_dphi * sin(theta), -dz_dphi);

      /* 
       * We compute normals to the knot (knowing the tangent). As the normals at a given point vary with
       * theta the outer endpoint of the normal describes a circle on the surface of the knotted torus.
       */
      normalx = cos(delta) * cos(theta);
      normaly = cos(delta) * sin(theta);
      normalz = sin(delta);

      normaldata[i][j][0] =   normalx;
      normaldata[i][j][1] =   normaly;
      normaldata[i][j][2] =   normalz;

      /* 
       * The parametrizing function taking the a grid point to a point on the knotted torus
       * is computes as "point on knot + rad * unit offset along normal".
       */
      vertexdata[i][j][0] =   (R + r*cos(phi)) * cos((n_by_m)*phi) + rad * normalx;
      vertexdata[i][j][1] =   (R + r*cos(phi)) * sin((n_by_m)*phi) + rad * normaly;
      vertexdata[i][j][2] =   r * sin(phi) + rad * normalz;
	}

  /* triangledata[0][i][j][k][l] represents the lower triangle in the subrectangle
   * whose lower left corner is grid point (i,j). k runs through 0, 1, 2 corresponding
   * to the 3 vertices of the triangle and l runs through 0, 1 giving the grid 
   * co-ordinates of a vertex.
   * triangledata[1][i][j][k][l] similarly represents the upper triangle in the 
   * subrectangle whose lower left corner is grid point (i,j).
   */
  for (i = 0; i < M; ++i)
    for (j = 0; j < N; ++j){
      triangledata[0][i][j][0][0] = i;
      triangledata[0][i][j][0][1] = j;
      triangledata[0][i][j][1][0] = (i+1) % M;
      triangledata[0][i][j][1][1] = j;
      triangledata[0][i][j][2][0] = (i+1) % M;
      triangledata[0][i][j][2][1] = (j+1) % N;

      triangledata[1][i][j][0][0] = i;
      triangledata[1][i][j][0][1] = (j+1) % N;
      triangledata[1][i][j][1][0] = i;
      triangledata[1][i][j][1][1] = j;
      triangledata[1][i][j][2][0] = (i+1) % M;
      triangledata[1][i][j][2][1] = (j+1) % N;
    }

}

void display(void)
{
  int h, i, j;
  /* Defining the knots color vectors.*/
  GLfloat mat_specular1[] = { 0.0, 10.0, 0.0, 0.4 };
  GLfloat mat_shininess1[] = { 50.0 };
  GLfloat mat_diffuse1[] = {0.0, 10.0, 0.0};

  GLfloat mat_specular2[] = { 5.0, 0.0, 0.0, 0.4 };
  GLfloat mat_shininess2[] = { 50.0 };
  GLfloat mat_diffuse2[] = {5.0, 0.0, 0.0};

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  /* Defining the knots color properties.*/

  glRotatef ((GLfloat) Zangle, 0.0, 0.0, 1.0);
  glRotatef ((GLfloat) Yangle, 0.0, 1.0, 0.0);
  glRotatef ((GLfloat) Xangle, 1.0, 0.0, 0.0);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  glBegin(GL_TRIANGLES);
  for (h = 0; h < 2; ++h)
     for (i = 0; i < M; ++i)
       for (j = 0; j < N; ++j){
	 if (h == 0) {
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular1);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess1);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse1);}
	 else {
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular2);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess2);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse2);}


         glNormal3fv( &normaldata[ triangledata[h][i][j][0][0] ][ triangledata[h][i][j][0][1] ][0] );
	 glVertex3fv( &vertexdata[ triangledata[h][i][j][0][0] ][ triangledata[h][i][j][0][1] ][0] );
	 glNormal3fv( &normaldata[ triangledata[h][i][j][1][0] ][ triangledata[h][i][j][1][1] ][0] );
	 glVertex3fv( &vertexdata[ triangledata[h][i][j][1][0] ][ triangledata[h][i][j][1][1] ][0] );
	 glNormal3fv( &normaldata[ triangledata[h][i][j][2][0] ][ triangledata[h][i][j][2][1] ][0] );
	 glVertex3fv( &vertexdata[ triangledata[h][i][j][2][0] ][ triangledata[h][i][j][2][1] ][0] );
       }
  glEnd();


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
   gluLookAt (0.0, 0.0, 13.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
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
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (1000, 1000); 
   glutInitWindowPosition (50, 50);
   glutCreateWindow ("Torus Knot");
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;  
}






