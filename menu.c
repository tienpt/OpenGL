/*
 * menu.c
 * This program shows a simple implementation 
 * of a pop-up menu (with sub-menu) using the GLUT library.
 *
 * Click right mouse button.
 */
#include <GL/glut.h>

void sub_menu(int);

static GLfloat square_color[3] = {1.0, 1.0, 1.0};

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);

   glColor3fv (square_color);
   glBegin(GL_POLYGON);
      glVertex3f (0.25, 0.25, 0.0);
      glVertex3f (0.75, 0.25, 0.0);
      glVertex3f (0.75, 0.75, 0.0);
      glVertex3f (0.25, 0.75, 0.0);
   glEnd();

   glFlush ();
}

void init (void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}

// The top menu callback function.
void top_menu(int id)
{
   if (id==1) exit(0);
}

// The sub-menu callback function.
void color_menu(int id)
{
  if (id==2) 
     {
      square_color[0] = 1.0; square_color[1] = 0.0; square_color[2] = 0.0; 
     }
  if (id==3) 
     {
      square_color[0] = 0.0; square_color[1] = 0.0; square_color[2] = 1.0; 
     }
   glutPostRedisplay();
}

int main(int argc, char** argv)
{  
   int sub_menu;

   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (250, 250); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("menu");
   init ();
   glutDisplayFunc(display); 

/* The sub-menu is created first because it must be visible when 
   the top menu is created, and its callback function registered. */
   sub_menu = glutCreateMenu(color_menu);
   glutAddMenuEntry("Red", 2);
   glutAddMenuEntry("Blue",3);

/* The top menu is created and its callback function registered. */
   glutCreateMenu(top_menu);
   glutAddMenuEntry("Quit",1);
   glutAddSubMenu("Change Color", sub_menu);

   /* The menu is attached to a button. */
   glutAttachMenu(GLUT_RIGHT_BUTTON);

   glutMainLoop();
   return 0;   /* ANSI C requires main to return int. */
}
