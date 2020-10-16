
/*  environmentBox.c
 *
 *  A 5-sided environment box with textured sides.
 *
 *  IMPORTANT: Project -> Settings -> Link -> add glaux.lib.
 */

#include <GL/glut.h>					
#include <gl/glaux.h>
#include <stdlib.h>
#include <stdio.h>

GLuint texture[5];

AUX_RGBImageRec *LoadBMP(char *Filename)			
{
   FILE *File = NULL;								
   if (!Filename)									
   {
      return NULL;									
   }

   File = fopen(Filename,"r");					
   if (File)										
   {
	  fclose(File);								
	  return auxDIBImageLoad(Filename);			
   }
   return NULL;								
}

// Load five different textures
void LoadTextures()			
{
   AUX_RGBImageRec *TextureImage[5];				
   memset(TextureImage,0,sizeof(void *)*1);         
   glGenTextures(5, texture);		

   TextureImage[0]=LoadBMP("Data/trees.bmp"); 
   glBindTexture(GL_TEXTURE_2D, texture[0]);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
   free(TextureImage[0]->data);					    
   free(TextureImage[0]);	
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);   

   TextureImage[1]=LoadBMP("Data/forest.bmp"); 
   glBindTexture(GL_TEXTURE_2D, texture[1]);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[1]->sizeX, TextureImage[1]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[1]->data);
   free(TextureImage[1]->data);					    
   free(TextureImage[1]);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

   TextureImage[2]=LoadBMP("Data/bricks.bmp"); 
   glBindTexture(GL_TEXTURE_2D, texture[2]);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[2]->sizeX, TextureImage[2]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[2]->data);
   free(TextureImage[2]->data);					    
   free(TextureImage[2]);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

   TextureImage[3]=LoadBMP("Data/clouds.bmp");   
   glBindTexture(GL_TEXTURE_2D, texture[3]);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[3]->sizeX, TextureImage[3]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[3]->data);
   free(TextureImage[3]->data);					    
   free(TextureImage[3]);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

   TextureImage[4]=LoadBMP("Data/NeHe.bmp"); 
   glBindTexture(GL_TEXTURE_2D, texture[4]);
   glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[4]->sizeX, TextureImage[4]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[4]->data);
   free(TextureImage[4]->data);					    
   free(TextureImage[4]);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
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
   glEnable(GL_TEXTURE_2D);	                       
   glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); 
  
   /*  5-sided environment box - each side textured differently.
    *  The front of the box is open and exactly matches the front face of the viewing frustum.
	*/
   glBindTexture(GL_TEXTURE_2D, texture[0]);
   glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0, -1.0, -5.0);
      glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0, 1.0, -5.0);
      glTexCoord2f(3.0f, 1.0f); glVertex3f(-1.0, 1.0, -25.0);
      glTexCoord2f(3.0f, 0.0f); glVertex3f(-1.0, -1.0, -25.0);
   glEnd();

   glBindTexture(GL_TEXTURE_2D, texture[1]);
   glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0, -1.0, -5.0);
      glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0, 1.0, -5.0);
      glTexCoord2f(3.0f, 1.0f); glVertex3f(1.0, 1.0, -25.0);
      glTexCoord2f(3.0f, 0.0f); glVertex3f(1.0, -1.0, -25.0);
   glEnd();

   glBindTexture(GL_TEXTURE_2D, texture[2]);
   glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0, -1.0, -5.0);
      glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0, -1.0, -5.0);
      glTexCoord2f(5.0f, 1.0f); glVertex3f(1.0, -1.0, -25.0);
      glTexCoord2f(5.0f, 0.0f); glVertex3f(-1.0, -1.0, -25.0);
   glEnd();

   glBindTexture(GL_TEXTURE_2D, texture[3]);
   glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0, 1.0, -5.0);
      glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0, 1.0, -5.0);
      glTexCoord2f(5.0f, 1.0f); glVertex3f(1.0, 1.0, -25.0);
      glTexCoord2f(5.0f, 0.0f); glVertex3f(-1.0, 1.0, -25.0);
   glEnd();
  
   glBindTexture(GL_TEXTURE_2D, texture[4]);
   glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0, -1.0, -25.0);
      glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0, -1.0, -25.0);
      glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0, 1.0, -25.0);
      glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0, 1.0, -25.0);
   glEnd();

   glFlush();	
   glDisable(GL_TEXTURE_2D);                        
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustum (-1.0, 1.0, -1.0, 1.0, 5.0, 26.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
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
   glutInitWindowSize(700, 700);
   glutInitWindowPosition(100, 100);
   glutCreateWindow(argv[0]);
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0; 
}
