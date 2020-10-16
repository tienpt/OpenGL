/*
 *  manipulateMatrix.c
 *  Modified from cube.c by Sumanta to show manipulation
 *  and access of the modelview matrix stack.
 */

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

#define X  0.70710678 /* one divided by root two */

// Matrix corresponding to rotation by 45 degrees about the z-axis -
// stored in an array in column-major order.
static GLfloat matrixData[16] = {
X, X, 0.0, 0.0, -X, X, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0
};

// Array to store the current modelview matrix in column-major order.
static GLfloat modelviewMatrixData[16];

// Print the matrix in usual rectangular form.
void displayModelviewMatrix(void)
{
   printf("The current modelview matrix:\n");
   printf("%f  ", modelviewMatrixData[0]);
   printf("%f  ", modelviewMatrixData[4]);
   printf("%f  ", modelviewMatrixData[8]);
   printf("%f\n", modelviewMatrixData[12]);
   printf("%f  ", modelviewMatrixData[1]);
   printf("%f  ", modelviewMatrixData[5]);
   printf("%f  ", modelviewMatrixData[9]);
   printf("%f\n", modelviewMatrixData[13]);
   printf("%f  ", modelviewMatrixData[2]);
   printf("%f  ", modelviewMatrixData[6]);
   printf("%f  ", modelviewMatrixData[10]);
   printf("%f\n", modelviewMatrixData[14]);
   printf("%f  ", modelviewMatrixData[3]);
   printf("%f  ", modelviewMatrixData[7]);
   printf("%f  ", modelviewMatrixData[11]);
   printf("%f\n", modelviewMatrixData[15]);
}

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

   // Read and print the current modelview matrix.
   glGetFloatv(GL_MODELVIEW_MATRIX, modelviewMatrixData);
   displayModelviewMatrix();

   gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   // Read and print the current modelview matrix.
   glGetFloatv(GL_MODELVIEW_MATRIX, modelviewMatrixData);
   displayModelviewMatrix();

   // Multiply the current modelview matrix on the right by the
   // matrix corresponding to rotation by 45 degrees about the z-axis.
   glMultMatrixf(matrixData);

   // Read and print the current modelview matrix.
   glGetFloatv(GL_MODELVIEW_MATRIX, modelviewMatrixData);
   displayModelviewMatrix();

   glScalef (1.0, 2.0, 1.0);  
   
   // Read and print the current modelview matrix.
   glGetFloatv(GL_MODELVIEW_MATRIX, modelviewMatrixData);
   displayModelviewMatrix();

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
