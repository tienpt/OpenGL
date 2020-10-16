/*
 *  bSplines.c
 *
 *  This program displays B-spline functions of orders 1, 2, 3 and 4.
 *
 *  Interaction:
 *  Press the up/down arrow keys to cycle between order 1 through 4.
 *  Press space to select a knot points.
 *  Press the left/right arrow keys to move the selected knot point.
 *  Press delete to reset.
 */

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static int countKnots = 0, splineOrder = 1;
int font=(int)GLUT_BITMAP_8_BY_13;

GLfloat knots[9] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};

// Separate integer array to store 10 times the knot values. The values in
// this array are then increased/decreased by 1 using the arrow keys. Using
// integer values avoids round-off error problems in the increaseKnot and
// decreaseKnot routines.
GLint knotsTimes10[9] ={ 0, 10, 20, 30, 40, 50, 60, 70, 80}; 		

void init(void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
}

// Draw text.
void writeBitmapString(void *font, char *string, float rasterx, float rastery) 
{  
		int i = 0; 
		float rx = rasterx, ry = rastery;
		glRasterPos2f(rx, ry);
        while (string[i] != '\0') { 
                glutBitmapCharacter(font, string[i]); 
				
				rx+=glutBitmapWidth(font, string[i]);

				i++;
        } 
} 

// Changes knots array values according to the knotTimes10 array values.
void changeKnots(void)
{
	int i;
    for (i = 0; i < 9; i++) 
		knots[i] = ((float)knotsTimes10[i])/10.0;
}

// Function to increase value of a knot.
// Increments are made first to knotsTimes10 to work with integers and
// avoid round-off error problems.
void increaseKnot(int i)
{
	if ( (i < 8) )
	{
		if (knotsTimes10[i] < knotsTimes10[i+1]) knotsTimes10[i] += 1;
		else 
		{
			increaseKnot(i+1);
			if (knotsTimes10[i] < knotsTimes10[i+1]) knotsTimes10[i] += 1;
		}
	}
	if ( (i == 8 )  && ( knotsTimes10[i] < 80) ) knotsTimes10[i] += 1;
	changeKnots();
}

// Function to decrease value of a knot.
// Decrements are made first to knotsTimes10 to work with integers and
// avoid round-off error problems.
void decreaseKnot(int i)
{
	if ( (i > 0) )
	{
		if (knotsTimes10[i] > knotsTimes10[i-1]) knotsTimes10[i] -= 1;
		else 
		{
			decreaseKnot(i-1);
			if (knotsTimes10[i] > knotsTimes10[i-1]) knotsTimes10[i] -= 1;
		}
	}
	if ( (i == 0 )  && ( knotsTimes10[i] > 0) ) knotsTimes10[i] -= 1;
    changeKnots();
}

void resetKnots(void)
{
	int i;
    for (i = 0; i < 9; i++) 
		knotsTimes10[i] = 10*i;
	changeKnots();
    countKnots = 0;
}

// Recursive computation of B-spline functions.
float Bspline(int i, int m, float u)
{
	float coef1, coef2;
	if ( m == 1 )
	{
		if ( ( knots[i] < u ) && ( u <= knots[i+1] ) ) return 1.0;
		else return 0.0;
	}
	else
	{
		if ( knots[i+m-1] == knots[i] ) coef1 = 0;
		else coef1 = (u - knots[i])/(knots[i+m-1] - knots[i]);
		if ( knots[i+m] == knots[i+1] ) coef2 = 0;
		else coef2 = (knots[i+m] - u)/(knots[i+m] - knots[i+1]);
		
		return ( coef1 * Bspline(i, m-1, u) + coef2 * Bspline(i+1 ,m-1 ,u) );
	}
}

// Draw a B-spline function
void drawSpline(int i, int m)
{
	float x;   

	// Drawing are scaled by factor of 3 in the y-direction.
	// Special case to handle order 1 to avoid vertical edges.
	if (m == 1)
	{
	   glBegin(GL_LINE_STRIP);
	      for ( x = knots[i]; x < knots[i+1]; x+=0.005 )
		     glVertex3f( -4.0 + x, 1.0, 0.0 );	
	   glEnd();
	   }
	else
    {
	glBegin(GL_LINE_STRIP);
	   for ( x = knots[i]; x <= knots[i+m]; x+=0.005 )
		 glVertex3f( -4.0 + x, 3*Bspline(i, m, x) - 2.0, 0.0 );	
	glEnd();
	}
}

void display(void)
{
   int i;

   char theStringOrder1[] = "Order 1 B-splines";
   char theStringOrder2[] = "Order 2 B-splines";
   char theStringOrder3[] = "Order 3 B-splines";
   char theStringOrder4[] = "Order 4 B-splines";

   char theString0[] = "0";
   char theString1[] = "1";
   char theString2[] = "2";
   char theString3[] = "3";
   char theString4[] = "4";
   char theString5[] = "5";
   char theString6[] = "6";
   char theString7[] = "7";
   char theString8[] = "8";

   char theStringKnotValues[] = "Knot Values";

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glPushMatrix();

   glTranslatef(0.0, 0.5, 0.0);

   // Write spline order.
   glColor3f(1.0, 1.0, 1.0);
   switch (splineOrder) 
   {
      case 1:
	     writeBitmapString((void*)font, theStringOrder1, -1.05, 3.5);
	  break;
      case 2:
	     writeBitmapString((void*)font, theStringOrder2, -1.05, 3.5);
	  break;
      case 3:
	     writeBitmapString((void*)font, theStringOrder3, -1.05, 3.5);
	  break;
      case 4:
	     writeBitmapString((void*)font, theStringOrder4, -1.05, 3.5);
	  break;
      default:
      break;
   }

   // Draw successive B-spline functions for the chosen order.
   glEnable (GL_LINE_SMOOTH);
   glEnable (GL_BLEND);
   glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);
   for (i = 0; i < 9 - splineOrder; i++ )
   {
	  switch (i) 
	  {     
         case 0:
	       glColor3f(1.0, 0.0, 0.0);
	     break;
         case 1:
	       glColor3f(0.0, 1.0, 0.0);
	     break;
         case 2:
	       glColor3f(0.0, 0.0, 1.0);
	     break;
         case 3:
	       glColor3f(1.0, 0.0, 1.0);
	     break;
         case 4:
	       glColor3f(0.0, 1.0, 1.0);
	     break;
         case 5:
	       glColor3f(1.0, 1.0, 0.0);
	     break;
         case 6:
	       glColor3f(1.0, 1.0, 1.0);
	     break;
         case 7:
	       glColor3f(1.0, 0.0, 0.0);
	     break;
         default:
         break;
	  }
       drawSpline(i, splineOrder);
   }

   // Draw the x-axis.
   glColor3f(1.0, 1.0, 1.0);
   glBegin(GL_LINES);
      glVertex3f(-4.0, -2.0, 0.0);
      glVertex3f( 4.0, -2.0, 0.0);  
   glEnd();

   // Draw points on the x-axis.
   glPointSize(5.0);
   glBegin(GL_POINTS);
      for (i = 0; i < 9; i++) 
         glVertex3f(-4.0 + (float)i, -2.0, 0.0);
   glEnd();
 
   // Label the points on the x-axis.
   writeBitmapString((void*)font, theString0, -4.05, -2.3);
   writeBitmapString((void*)font, theString1, -3.05, -2.3);
   writeBitmapString((void*)font, theString2, -2.05, -2.3);
   writeBitmapString((void*)font, theString3, -1.05, -2.3);
   writeBitmapString((void*)font, theString4, -0.05, -2.3);
   writeBitmapString((void*)font, theString5,  0.95, -2.3);
   writeBitmapString((void*)font, theString6,  1.95, -2.3);
   writeBitmapString((void*)font, theString7,  2.95, -2.3);
   writeBitmapString((void*)font, theString8,  3.95, -2.3);

   // Draw the y-axis.
   glBegin(GL_LINES);
      glVertex3f(-4.0, -2.0, 0.0);
      glVertex3f(-4.0, 4.0, 0.0);  
   glEnd();

   // Draw points on the y-axis.
   glBegin(GL_POINTS);
         glVertex3f(-4.0, 1.0, 0.0);
         glVertex3f(-4.0, 4.0, 0.0);
   glEnd();

   // Label the points on the y-axis.
   writeBitmapString((void*)font, theString0, -4.25, -2.05);
   writeBitmapString((void*)font, theString1, -4.25,  0.95);
   writeBitmapString((void*)font, theString2, -4.25,  3.95); 

   // Draw horizontal bars corresponding to knot points.
   glBegin(GL_LINES);
      for (i = 0; i < 9; i++) 
	  {
         glVertex3f(-4.0, -3.5 + (float)i * 0.1, 0.0);
         glVertex3f( 4.0, -3.5 + (float)i * 0.1, 0.0);
	  }
   glEnd();

   // Draw the knot points as dots on their respective bars.
   glColor3f(0.0, 1.0, 0.0);
   glBegin(GL_POINTS);
      for (i = 0; i < 9; i++) 
         glVertex3f( -4.0 + knots[i], -3.5 + (float)i * 0.1, 0.0);
   glEnd();

   // Highlight the selected knot point.
   glColor3f(1.0, 0.0, 0.0);
   glBegin(GL_POINTS);
      glVertex3f( -4.0 + knots[countKnots], 
		          -3.5 + (float)countKnots * 0.1, 0.0); 
   glEnd();

   // Lable the knot bars.
   glColor3f(1.0, 1.0, 1.0);
   writeBitmapString((void*)font, theStringKnotValues, -0.7, -4.0);
   
   glPopMatrix();
   glFlush();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho(-5.0, 5.0, -5.0*(GLfloat)h/(GLfloat)w, 
               5.0*(GLfloat)h/(GLfloat)w, -5.0, 5.0);
   else
      glOrtho(-5.0*(GLfloat)w/(GLfloat)h, 
               5.0*(GLfloat)w/(GLfloat)h, -5.0, 5.0, -5.0, 5.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) 
   {
      case 27:	
         exit(0);
         break;
      case ' ':
         if (countKnots < 8) countKnots++; 
		 else countKnots = 0;
         glutPostRedisplay();
		 break;
      case 127:	
         resetKnots();
		 glutPostRedisplay();
         break;
      default:
         break;
  }
}

void SpecialKeys(int key, int x, int y)
{
   if(key == GLUT_KEY_LEFT) decreaseKnot(countKnots);
   if(key == GLUT_KEY_RIGHT) increaseKnot(countKnots);
   if(key == GLUT_KEY_UP) 
   {
	   if (splineOrder < 4) splineOrder++;
   }
   if(key == GLUT_KEY_DOWN) 
   {
	   if (splineOrder > 1) splineOrder--;
   }
   glutPostRedisplay();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (600, 600);
   glutInitWindowPosition (100, 100);
   glutCreateWindow(argv[0]);
   init();
   glutReshapeFunc(reshape);
   glutDisplayFunc(display);
   glutKeyboardFunc (keyboard);
   glutSpecialFunc(SpecialKeys);
   glutMainLoop();
   return 0; 
}
