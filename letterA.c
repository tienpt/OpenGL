/* letterA.c
 *
 * Modified by Sumanta from Letter.c of the OpenGL SuperBible
 */

#include <GL/glut.h>
#include <stdio.h>

/*
 * Globals...
 */

int     Width;          /* Width of window */
int     Height;         /* Height of window */
int     isWire = 0;     /* Boolean to indicate if wireframe is drawn */
/*
 * Functions...
 */

void   Redraw(void);
void   Resize(int width, int height);
void   Keyboard(unsigned char key, int x, int y);

/*
 * 'main()' - Open a window and display a pencil.
 */

int                /* O - Exit status */
main(int  argc,    /* I - Number of command-line arguments */
     char *argv[]) /* I - Command-line arguments */
    {
    glutInit(&argc, argv);
    printf("Press space to toggle between wireframe and filled letter.\n");
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(792, 573);
    glutCreateWindow("Letter A Using GLU Polygon Tessellator");

    glutDisplayFunc(Redraw);
    glutReshapeFunc(Resize);
	glutKeyboardFunc(Keyboard);

    glutMainLoop();
    return (0);
    }

/*
 * 'Redraw()' - Redraw the window...
 */

void
Redraw(void)
    {
	//  Create a pointer to a tesselation object.
    GLUtesselator   *tess;

    static GLdouble outside[7][3] =
        {
        { 0.0, 2.0, 0.0 },
        { -1.5, -2.0, 0.0 },
        { -1.0, -2.0, 0.0 },
        { -0.3, 0.0, 0.0 },
        { 0.3, 0.0, 0.0 },
        { 1.0, -2.0, 0.0 },
        { 1.5, -2.0, 0.0 }
        };
    static GLdouble inside[3][3] =
        {
        { 0.0, 1.0, 0.0 },
        { -0.3, 0.2, 0.0 },
        { 0.3, 0.2, 0.0 }
        };

    /* Clear the color and depth buffers... */
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);


    // Draw the letter A
    glPushMatrix();
    glTranslatef(0.0, 0.0, -15.0);

    glColor3f(0.0, 1.0, 0.0);
    
	// Create the tesselation object.
    tess = gluNewTess();

	// Define the call back functions to be used through the tesselation.
    gluTessCallback(tess, GLU_TESS_BEGIN, glBegin);
    gluTessCallback(tess, GLU_TESS_VERTEX, glVertex3dv);
    gluTessCallback(tess, GLU_TESS_END, glEnd);

	if (isWire) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Specify the letter A as a polygon with an outside and inside boundary -
	// the outer boundary is concave with 7 vertices and the inside bounday
	// is a triangle.
    gluTessBeginPolygon(tess, (GLvoid *)0);

    // The outside vertices of the A starting from the top going counter-clockwise.
    gluTessBeginContour(tess);
      gluTessVertex(tess, outside[0], outside[0]);
      gluTessVertex(tess, outside[1], outside[1]);
      gluTessVertex(tess, outside[2], outside[2]);
      gluTessVertex(tess, outside[3], outside[3]);
      gluTessVertex(tess, outside[4], outside[4]);
      gluTessVertex(tess, outside[5], outside[5]);
      gluTessVertex(tess, outside[6], outside[6]);
    gluTessEndContour(tess);
	
	// The inside vertices of the A - vertices of the black triangle.
    gluTessBeginContour(tess);
        gluTessVertex(tess, inside[0], inside[0]);
        gluTessVertex(tess, inside[1], inside[1]);
        gluTessVertex(tess, inside[2], inside[2]);
    gluTessEndContour(tess);
    gluTessEndPolygon(tess);
    gluDeleteTess(tess);

    glPopMatrix();

    /* Finish up */
    glFlush();
    }


/*
 * 'Resize()' - Resize the window...
 */

void
Resize(int width,  /* I - Width of window */
       int height) /* I - Height of window */
    {
    /* Save the new width and height */
    Width  = width;
    Height = height;

    /* Reset the viewport... */
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)width / (float)height, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    }


void Keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case ' ':
         if (isWire == 0) isWire = 1;
         else isWire = 0;
         glutPostRedisplay();
         break;	  
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}
