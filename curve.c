/*
 * curve.c
 */
#include <GL/glut.h>
#include <math.h>

#define PI 3.14159265

void display(void)
{
   int i;
   glClear (GL_COLOR_BUFFER_BIT);
  
   glColor3f (1.0, 1.0, 1.0);

   glBegin(GL_LINE_STRIP);
   for (i = 0; i <= 100; i++)
     glVertex3f( 0.5*PI + ((float)i/100)*2.0*PI, sin( 0.5*PI + ((float)i/100)*2.0*PI ), 0.0 );
   glEnd();

   glBegin(GL_LINE_STRIP);
   for (i = 0; i <= 100; i++)
     glVertex3f( 2.5*PI + ( 1.0 - ((float)i/100)*0.5 ) * sin( ((float)i/100)*6*PI ), 
                          ( 1.0 - ((float)i/100)*0.5 ) * cos( ((float)i/100)*6*PI ), 0.0  );
   glEnd();

   glFlush();
}

void init (void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 10.0, -5.0, 5.0, -1.0, 1.0);
}

/* the following defines keyboard input */
void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case 'e':
    exit(0);
    break;
  case 'q':
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
   glutCreateWindow ("A curve");
   init ();
   glutDisplayFunc(display); 
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;  
}
