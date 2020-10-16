// composeTransformations.c
// By Sumanta
// Shows composition of transformations and the relative
// transformation of one object w.r.t another.

#include <math.h>
#include <gl\glut.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#define PI 3.14159265
void key(unsigned char, int, int);
void display(void);
void myReshape(GLsizei, GLsizei);
void drawMan(void);
void writeBlueManStatement(void);
void writeRedManStatement(void);
void writeTranslateStatement(void);
void writeRotateStatement(void);
void myinit(void);

GLuint theMan;
GLsizei wh = 500, ww = 500; 
int count = 0;
int font=(int)GLUT_BITMAP_8_BY_13;

void myReshape(GLsizei w, GLsizei h)
{

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity(); 
   glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity(); 

   glViewport(0,0,w,h);
   glClearColor (0.8, 0.8, 0.8, 1.0);
   glClear(GL_COLOR_BUFFER_BIT);
   display();
   glFlush();

   ww = w;
   wh = h; 
}

void myinit(void)
{
   theMan = glGenLists(1);
   glNewList(theMan, GL_COMPILE);
   drawMan();
   glEndList();

   glViewport(0,0,ww,wh);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity(); 
   glOrtho(0.0, (GLdouble) ww , 0.0, (GLdouble) wh , -1.0, 1.0);

   glClearColor (0.8, 0.8, 0.8, 1.0);
   glClear(GL_COLOR_BUFFER_BIT);
   glFlush();
}

// Draw stick figure.
static void drawMan(void)
{   
   GLdouble angle;
   int i;

   glBegin(GL_LINE_LOOP);
   for(i = 0; i < 20; ++i){
    angle = 2 * PI * i / 20;
    glVertex2f(0.0 + cos(angle) * 3.0, 7 + sin(angle) * 3.0);
   }
   glEnd();
   glBegin(GL_LINES);
    glVertex2f(0.0, 4.0);
	glVertex2f(0.0, -4.0);
	glVertex2f(0.0, -4.0);
	glVertex2f(6.0, -10.0);
	glVertex2f(0.0, -4.0);
	glVertex2f(-6.0, -10.0);
	glVertex2f(-6.0, 0.0);
	glVertex2f(6.0, 0.0);
   glEnd();
}

// Draw text.
void writeBitmapString(void *font, char *string, int rasterx, int rastery) 
{  
		int i = 0, rx = rasterx, ry = rastery;
		glRasterPos2i(rx, ry);
        while (string[i] != '\0') { 
                glutBitmapCharacter(font, string[i]); 
				
				rx+=glutBitmapWidth(font, string[i]);

				i++;
        } 
} 

void display(void)
{
   char theStringDrawBlueMan[] = "drawBlueMan;";
   char theStringDrawRedMan[] = "drawRedMan;";
   char theStringTranslate[] = "glTranslatef(20.0, 0.0, 0.0);";
   char theStringRotate[] = "glRotatef(30.0, 0.0, 0.0, 1.0);";
   
   glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();
   glColor3f(0.0, 0.0, 0.0);

   switch (count) {
  case 0:	
    goto step0;
    break;
  case 1:
	goto step1;
    break;
  case 2:
	goto step2;
    break;
  case 3:
	goto step3;
    break;
  case 4:
	goto step4;
    break;
  case 5:
	goto step5;
    break;
  case 6:
	goto step6;
    break;
  default:
    break;
  }

step6:
   // Rotate. 
   // Text drawing statements are all enclosed within push/pop pairs
   // so that the raster position is always w.r.t the identity transform.
   glPushMatrix();
   glLoadIdentity();
   writeBitmapString((void*)font, theStringRotate, -40, -20);
   glPopMatrix();
   glRotatef(30, 0.0, 0.0, 1.0);

step5:
   // Translate.
   glPushMatrix();
   glLoadIdentity();
   writeBitmapString((void*)font, theStringTranslate, -40, -23);
   glPopMatrix();
   glTranslatef(20.0, 0.0, 0.0);

step4:
   // Draw red man.
   glPushMatrix();
   glLoadIdentity();
   writeBitmapString((void*)font, theStringDrawRedMan, -40, -26);
   glPopMatrix();
   glColor3f(1.0, 0.0, 0.0);
   glCallList(theMan);

   glColor3f(0.0, 0.0, 0.0);

step3:
   // Rotate.
   glPushMatrix();
   glLoadIdentity();
   writeBitmapString((void*)font, theStringRotate, -40, -29);
   glPopMatrix();
   glRotatef(30, 0.0, 0.0, 1.0);

step2:
   // Translate.
   glPushMatrix();
   glLoadIdentity();
   writeBitmapString((void*)font, theStringTranslate, -40, -32);
   glPopMatrix();
   glTranslatef(20.0, 0.0, 0.0);

step1:
   // Draw blue man.
   glPushMatrix();
   glLoadIdentity();
   writeBitmapString((void*)font, theStringDrawBlueMan, -40, -35);
   glPopMatrix();
   glColor3f(0.0, 0.0, 1.0);
   glCallList(theMan);

step0:
   glFlush();
}

void key(unsigned char key, int x, int y)
{
   switch (key) {
   case 27:	
    exit(0);
    break;
  case ' ':
	 if (count < 6) count++;
	 else count = 0;
    glutPostRedisplay();
    break;
  default:
    break;
  }
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    printf("Press the shift key to successively compose transformations.\n");
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
    glutCreateWindow("Transformations");
    glutDisplayFunc(display);
	myinit ();
    glutReshapeFunc (myReshape); 
	glutKeyboardFunc(key);
    glutMainLoop();
   return 0;   
}
