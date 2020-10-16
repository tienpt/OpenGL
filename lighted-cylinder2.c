/*
 * lighted-cylinder2.c
 * Here we compute the vertex normals by averaging the normals
 * to the triangles surrounding each vertex.
 *
 * From the output the program seems to have a bug.
 */

/* Use the x, X, y, Y, z, Z keys to turn the cylinder. */

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
 
#define PI 3.14159265358979324

#define M  25  
#define N  15

/* Define the parametrizing fuction that maps the parameter point (i/M, j/N)
 * on the plane square to the point (FNX(i,j), FNY(i,j), FNZ(i,j)) on the cylinder.
 */
 #define FNX(i,j) ( cos( ( (float) i/M ) * 2 * PI) )
 #define FNY(i,j) ( sin( ( (float) i/M ) * 2 * PI) ) 
 #define FNZ(i,j) ( 3.0 * (float) j/N )

// Vertex array: the x,y,z co-ordinates of the points to which the grid points 
// are mapped. 
static GLfloat vdata[3*(M+1)*(N+1)];

// Normal array.
static GLfloat ndata[3*(M+1)*(N+1)];

// Angles used to rotate the cylinder with keyboard entry.
static int Xangle = 0, Yangle = 0, Zangle = 0;

// The normal to a triangle whose vertices are v0, v1, v2 are added
// component-wise to the vector n.
normalToTriangle(float* v0, float* v1, float* v2, float* n)
{
  n[0] += (v1[1]-v0[1])*(v2[2]-v0[2]) - (v2[1]-v0[1])*(v1[2]-v0[2]);
  n[1] += (v2[0]-v0[0])*(v1[2]-v0[2]) - (v1[0]-v0[0])*(v2[2]-v0[2]);
  n[2] += (v1[0]-v0[0])*(v2[1]-v0[1]) - (v2[0]-v0[0])*(v1[1]-v0[1]);
}

// The normal to a vertex is obtained by adding successively the normals
// to each of the surrounding triangles. These normals are finally normalized
// to unit length.
normalToVertex(int i, int j, float* n)
{
  GLfloat length;
  n[0] = 0;
  n[1] = 0;
  n[2] = 0;

  if (j==0) 
    {
      normalToTriangle(vdata+(3*(j*(M+1)+i)), vdata+(3*(j*(M+1)+i+1)), vdata+(3*((j+1)*(M+1)+i+1)), n);
      normalToTriangle(vdata+(3*(j*(M+1)+i)), vdata+(3*((j+1)*(M+1)+i+1)), vdata+(3*((j+1)*(M+1)+i)), n);
      normalToTriangle(vdata+(3*(j*(M+1)+i)), vdata+(3*((j+1)*(M+1)+i)), vdata+(3*(j*(M+1)+i-1)), n);
    }
  else if (j==N)
    {
      normalToTriangle(vdata+(3*(j*(M+1)+i)), vdata+(3*(j*(M+1)+i-1)), vdata+(3*((j-1)*(M+1)+i-1)), n);
      normalToTriangle(vdata+(3*(j*(M+1)+i)), vdata+(3*((j-1)*(M+1)+i-1)), vdata+(3*((j-1)*(M+1)+i)), n);
      normalToTriangle(vdata+(3*(j*(M+1)+i)), vdata+(3*((j-1)*(M+1)+i)), vdata+(3*(j*(M+1)+i+1)), n);
    }
  else
    {    
      normalToTriangle(vdata+(3*(j*(M+1)+i)), vdata+(3*(j*(M+1)+i+1)), vdata+(3*((j+1)*(M+1)+i+1)), n);
      normalToTriangle(vdata+(3*(j*(M+1)+i)), vdata+(3*((j+1)*(M+1)+i+1)), vdata+(3*((j+1)*(M+1)+i)), n);
      normalToTriangle(vdata+(3*(j*(M+1)+i)), vdata+(3*((j+1)*(M+1)+i)), vdata+(3*(j*(M+1)+i-1)), n);
      normalToTriangle(vdata+(3*(j*(M+1)+i)), vdata+(3*(j*(M+1)+i-1)), vdata+(3*((j-1)*(M+1)+i-1)), n);
      normalToTriangle(vdata+(3*(j*(M+1)+i)), vdata+(3*((j-1)*(M+1)+i-1)), vdata+(3*((j-1)*(M+1)+i)), n);
      normalToTriangle(vdata+(3*(j*(M+1)+i)), vdata+(3*((j-1)*(M+1)+i)), vdata+(3*(j*(M+1)+i+1)), n);
    }
  length = sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
  // Dangerous! No check for 0 length.
  n[0] /= length; n[1] /= length; n[2] /= length; 
}

void init (void) 
{
  int i, j, k;

  GLfloat ambient[] = { 0.8, 0.8, 0.8, 1.0 };
  GLfloat diffuse[] = { 1.0, 1.0, 0.0, 1.0 };
  GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat position[] = { 0.0, 1.0, 3.0, 0.0 };    
  GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
 
  glClearColor (0.0, 0.0, 0.0, 0.0);

  // The vertex array is filled.
  k = 0;
  for (j = 0; j <= N; j++)
    for (i = 0; i <= M; i++){
      vdata[k++] = FNX(i,j); 
      vdata[k++] = FNY(i,j);
      vdata[k++] = FNZ(i,j); 
	}  

  // The normal array is filled.
  for (j = 0; j <= N; j++)
    for (i = 0; i <= M; i++){
      normalToVertex(i, j, ndata+(3*(j*(M+1)+i)));
	}  
     
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_NORMAL_ARRAY);

   glVertexPointer(3, GL_FLOAT, 0, vdata);
   glNormalPointer(GL_FLOAT, 0, vdata);

/* Define properties of the light source */
   glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
   glLightfv(GL_LIGHT0, GL_POSITION, position);
    
/* Define properties of the ambient light */
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

/* Enable two-sided lighting */
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST); 
}

void display(void)
{
   int  i, j;
  
   GLfloat mat_specular1[] = { 1.0, 0.0, 0.0, 1.0 };
   GLfloat mat_shininess1[] = { 50.0 };
   GLfloat mat_diffuse1[] = {0.9, 0.0, 0.0};  
   
   GLfloat mat_specular2[] = { 0.0, 1.0, 0.0, 1.0 };
   GLfloat mat_shininess2[] = { 50.0 };
   GLfloat mat_diffuse2[] = {0.0, 0.9, 0.0};

   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glColor3f (1.0, 1.0, 1.0);
  
   glRotatef ((GLfloat) Zangle, 0.0, 0.0, 1.0);
   glRotatef ((GLfloat) Yangle, 0.0, 1.0, 0.0);
   glRotatef ((GLfloat) Xangle, 1.0, 0.0, 0.0);

/* Material lighting properties are specified for the cylinder */
   for(j = 0; j < N; j++){
     if (j%2 == 0)
       {
	 glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular1);
	 glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess1);
	 glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse1);
       }
     else
       {
	 glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular2);
	 glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess2);
	 glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse2);
       }
     glBegin(GL_TRIANGLE_STRIP);
     for(i = 0; i <= M; i++){
       // The order of the glArrayElement() statements have been
       // reversed from lighted-cylinder1.c
       glArrayElement( (j+1)*(M+1) + i );
       glArrayElement( j*(M+1) + i );
     }
   glEnd();
   }

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
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); 
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
