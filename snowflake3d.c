/* snowflake3d.c
 * Sumanta
 * 3d Koch snowflake - see snowflake.c for the 2d version.
 *
 * Interaction: Press 's' to add a layer.
 *
 * Comments: (a) Blending has been enabled.
 *           (b) Normals are not accurate! The tetrahedron is 
 *               positioned with its center (CG) at the origin,
 *               so that, for "most" (??) vertices v, v itself is a
 *               reasonable approximation to the normal direction.
 *               Normals really need to be fixed!
 *           (c) There are two light sources, one directional, and
 *               one positional at the origin.
 *           (d) Materials are emissive with emission RGB one-fifth
 *               of ambient/diffuse RGBs. 
 */

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define ROOT3 1.732050807568877294 
#define ROOT2 1.41421356237309505  

void display();
void drawtriangle(float* v0, float* v1, float* v2);
void addtetra (float* v0, float* v1, float* v2, int depth, float length);
void normalize(float* v);
void crossproduct (float* vec0, float* vec1, float *result);

/* The following give the vertices of an equilateral tetrahedron
 * with side length 1 centered at the origin.
 */
static GLfloat vdata[4][3] = {
  {-0.5, -1.0/(2.0 * ROOT3), -ROOT2/(4.0*ROOT3)}, 
  {0.5,  -1.0/(2.0 * ROOT3), -ROOT2/(4.0*ROOT3)}, 
  {0.0, 1/ROOT3 , -ROOT2/(4.0*ROOT3)}, 
  {0.0, 0.0, ROOT2/ROOT3 - ROOT2/(4.0*ROOT3)}
};

int depth = 0;
float triang_no = 0.0;
GLfloat mat_amb_and_diffuse[] = { 0.5, 1.0, 0.0, 0.3 };
GLfloat mat_specular[] = { 0.2, 0.2, 0.2, 1.0 };     
GLfloat mat_emission[] = { 0.1, 0.2, 0.0, 0.1 };

void display(){

  glClear (GL_COLOR_BUFFER_BIT);

  addtetra(&vdata[0][0], &vdata[2][0], &vdata[1][0], depth, 1.0);
  addtetra(&vdata[1][0], &vdata[2][0], &vdata[3][0], depth, 1.0);
  addtetra(&vdata[2][0], &vdata[0][0], &vdata[3][0], depth, 1.0);
  addtetra(&vdata[0][0], &vdata[1][0], &vdata[3][0], depth, 1.0);

  glFlush();

}

void normalize(float* v){

  GLfloat d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

  if (d == 0.0){
    printf("zero length vector\n");
    exit(-1);
  }

  v[0] /= d;  v[1] /= d;  v[2] /= d;

}

void drawtriangle(float* v0, float* v1, float* v2){

  GLfloat normal0[3], normal1[3], normal2[3];
  int i;

  /* The vertices themselves are used as normal directions. */
  for (i=0; i < 3; i++){
    normal0[i] = v0[i];
  }
  normalize(normal0);

  for (i=0; i < 3; i++){
    normal1[i] = v1[i];
  }
  normalize(normal1);

  for (i=0; i < 3; i++){
    normal2[i] = v2[i];
  }
  normalize(normal2);

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_amb_and_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);

    glBegin(GL_TRIANGLES);
      glNormal3fv(normal0);
      glVertex3fv(v0);
      glNormal3fv(normal1);
      glVertex3fv(v1);
      glNormal3fv(normal2);
      glVertex3fv(v2);
    glEnd();

    /* Updates the current triangle number.*/
    triang_no++;

    /* A trigonometric function, based on the current triangle number,
     * determines the current drawing colors
     */
    mat_amb_and_diffuse[0] = 0.5 + sin(triang_no)/2;
    mat_amb_and_diffuse[1] = 0.5 + cos(triang_no)/2;
    mat_amb_and_diffuse[2] = 0.5 - sin(triang_no)/2;  
    
    mat_emission[0] = 0.2 * mat_amb_and_diffuse[0];
    mat_emission[1] = 0.2 * mat_amb_and_diffuse[1];
    mat_emission[2] = 0.2 * mat_amb_and_diffuse[2];
}

void crossproduct(float* vec0, float* vec1, float *result){
  
  result[0] = vec0[1]*vec1[2] - vec1[1]*vec0[2];
  result[1] = vec1[0]*vec0[2] - vec0[0]*vec1[2];
  result[2] = vec0[0]*vec1[1] - vec1[0]*vec0[1];
 
}

/* Given an equilateral triangle T with vertices at v0, v1, v2, 
 * places an equilateral tetrahedron with its base on the subtriangle
 * T' of T whose vertices are at the midpoints of the edges of T.
 * T' itself is not drawn again. So a total of 6 new triangles are
 * drawn: 3 subtriangles of T and 3 faces of the the tetrahedron.
 * The "length" variable stores the current side length of T.
 */
void addtetra(float* v0, float* v1, float* v2, int depth, float length){

  GLfloat v3[3], v4[3], v5[3], v6[3], 
          vec1[3], vec2[3], vecn[3], center[3];
  GLint i;

  if (depth == 0){
      drawtriangle(v0, v1, v2);
      return;
  }

  for(i=0; i < 3; i++){
    v3[i]     = (v0[i] + v1[i])/2.0;
    v4[i]     = (v1[i] + v2[i])/2.0;
    v5[i]     = (v2[i] + v0[i])/2.0;  
    vec1[i]   =  v1[i] - v0[i];
    vec2[i]   =  v2[i] - v0[i];
    center[i] = (v0[i] + v1[i] + v2[i])/3.0;
  }

  crossproduct(vec1, vec2, vecn);
  normalize(vecn);

  for(i=0; i < 3; i++){
    v6[i] = center[i] + (length/2.0) * (ROOT2/ROOT3)* vecn[i];
      }

  addtetra(v0, v3, v5, depth-1, length/2.0);
  addtetra(v3, v1, v4, depth-1, length/2.0);
  addtetra(v4, v2, v5, depth-1, length/2.0);
  addtetra(v4, v5, v6, depth-1, length/2.0);
  addtetra(v3, v6, v5, depth-1, length/2.0);
  addtetra(v4, v6, v3, depth-1, length/2.0);

}

void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case 'e':
    exit(0);
    break;
  case 's':
    ++depth;
    printf("The snowflake level has %d levels.\n", depth);
    glutPostRedisplay();
    break;
  }
}

void init (void) 
{
   GLfloat ambient[] = { 0.1, 0.1, 0.1, 1.0 };
   GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat position0[] = { 0.0, 1.0, 3.0, 0.0 };
   GLfloat position1[] = { 0.0, 0.0, 0.0, 1.0 };

   GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };

   glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
   glLightfv(GL_LIGHT0, GL_POSITION, position0);

/* */
   glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
   glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
   glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
   glLightfv(GL_LIGHT1, GL_POSITION, position1);

   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
   glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_LIGHT1);
   glEnable (GL_BLEND);

   glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);

   printf("The snowflake level has 0 levels.\n");
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(30.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (0.0, 0.0, 2.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

/*  Main Loop
 */

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (800, 800); 
   glutInitWindowPosition (50, 20);
   glutCreateWindow ("Koch snowflake3d");
   init ();
   glutReshapeFunc(reshape);
   glutDisplayFunc(display); 
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;   /* ANSI C requires main to return int. */
}
