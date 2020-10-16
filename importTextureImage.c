
/*  importTextureImage.c
 *
 *  This program is checker.c of the red book modified by Sumanta,
 *  based on NeHe's Lesson 6, to show how to import a texture image.
 *
 *  IMPORTANT: Project -> Settings -> Link -> add glaux.lib.
 */

#include <GL/glut.h>					
#include <gl/glaux.h>                               // Header file for the GLaux library
#include <stdlib.h>
#include <stdio.h>

GLuint texture[1];

AUX_RGBImageRec *LoadBMP(char *Filename)			// Loads a bitmap image
{
   FILE *File = NULL;								// File handle
   if (!Filename)									// Make sure a filename was given
   {
      return NULL;									// If not return NULL
   }

   File = fopen(Filename,"r");						// Check to see if the file exists
   if (File)										
   {
	  fclose(File);									// Close the handle
	  return auxDIBImageLoad(Filename);				// Load the bitmap and return a pointer
   }
   return NULL;										// If load failed return NULL
}

void LoadTextures()			
{
   AUX_RGBImageRec *TextureImage[1];				// Create storage space for the Texture
   memset(TextureImage,0,sizeof(void *)*1);         // Set the pointer to NULL
   glGenTextures(1, texture);				        // Return name for texture

   
   TextureImage[0]=LoadBMP("Data/trees.bmp");       // Load the bitmap
   glBindTexture(GL_TEXTURE_2D, texture[0]);        // Activate a texture

   /* Define the 2D texture */
   glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
  
   /* Set texture parameters for wrapping */
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

   /* Set texture parameters for filtering */
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

   free(TextureImage[0]->data);					    // Free the texture image memory
   free(TextureImage[0]);							// Free the image structure
  }

void init(void)
{    
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_FLAT);
   glEnable(GL_DEPTH_TEST);

   LoadTextures();
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glEnable(GL_TEXTURE_2D);	                        // Turn on OpenGL texturing.

   /* Specify how texture values combine with existing object color values */
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); 

   glBindTexture(GL_TEXTURE_2D, texture[0]);        // Activate a texture

   /* Specify two quadrilaterals - for each vertex its position and texture co-ordinates */
   glBegin(GL_QUADS);
      glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -1.0, 0.0);
      glTexCoord2f(0.0, 1.0); glVertex3f(-2.0, 1.0, 0.0);
      glTexCoord2f(1.0, 1.0); glVertex3f(0.0, 1.0, 0.0);
      glTexCoord2f(1.0, 0.0); glVertex3f(0.0, -1.0, 0.0);

      glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, 0.0);
      glTexCoord2f(0.0, 1.0); glVertex3f(1.0, 1.0, 0.0);
      glTexCoord2f(1.0, 1.0); glVertex3f(2.41421, 1.0, -1.41421);
      glTexCoord2f(1.0, 0.0); glVertex3f(2.41421, -1.0, -1.41421);
   glEnd();
   glFlush();	
   glDisable(GL_TEXTURE_2D);                        // Turn off OpenGL texturing
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 30.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(0.0, 0.0, -3.6);
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
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
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(250, 250);
   glutInitWindowPosition(100, 100);
   glutCreateWindow(argv[0]);
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0; 
}
