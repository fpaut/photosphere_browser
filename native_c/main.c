//------------------------------------------------------------------------------
// glx_simple_new - Shows how to create an X window and a new-style 
//   GL context without GLUT or any helper libraries.
//
//   COMPILE WITH:
//       g++ -g -o glx_simple_new glx_simple_new.cxx -lGLU -lGL -lX11
 
//------------------------------------------------------------------------------
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include "3ds.h"
#include "bmp.h"
#include "glwin.h"
#include "glmodels.h"
#include "font_truetype/src/drawtext.h"

 
//----------------------------------------------------------------------------
 
const int   WIN_XPOS    = 0;
const int   WIN_YPOS    = 0;
const int   WIN_XRES    = 640;
const int   WIN_YRES    = 480;

//----------------------------------------------------------------------------
 
typedef struct Camera
{
	GLdouble eyeX;
	GLdouble eyeY;
	GLdouble eyeZ;
	GLdouble centerX;
	GLdouble centerY;
	GLdouble centerZ;
	GLdouble upX;
	GLdouble upY;
	GLdouble upZ;
} Camera;

//----------------------------------------------------------------------------
 
MyWin        *Win;
// Camera       MyCam = {-30.0, 0.0, -10.0, 0.0, -0.0, 0.0, 0.0, 1.0, 0.0};
Camera       MyCam = {-0.0, -0.0, 1000.0, 0.0, -0.0, 0.0, 0.0, 1.0, 0.0};
float       CameraStep = 5.0;


// 3DS Obj3ds
obj_3ds Obj3ds;
 
/* XXX fonts are represented by the opaque struct dtx_font type, so you
 * need to create at least one with dtx_open_font (see main).
 */
struct dtx_font *font;
//----------------------------------------------------------------------------

 

void displayCB(void)
{
/* ADDED */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glLoadIdentity();
  

/* gluLookAt(30, -0, 20, 0, 0, 0, 0, 1, 0);*/
   gluLookAt(MyCam.eyeX, MyCam.eyeY, MyCam.eyeZ, 0, 0, 0, 0, 1, 0);
 	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

        drawaxes(100.0);
       dtx_prepare(font, 32);
        dtx_use_font(font, 32);
     glColor3f(1, 0, 0);
    gl_printf(40, 10, "X");
    
    glColor3f(0, 1, 0);
    gl_printf(-30, 40, "Y");
    
    glColor3f(0, 0, 1);
    gl_printf(5, 5, "Z");
    
        dtx_prepare(font, 24);
        dtx_use_font(font, 24);
        	glColor3f(1, 1, 1);
//        gl_printf(0, 10, "TEST2");
//	glPushMatrix();
//	glTranslatef(0, -10, 0);
//	/* XXX call dtx_string to draw utf-8 text.
//	 * any transformations and the current color apply
//	 */
//	dtx_string("TEST");
//  	glPopMatrix();
 	glXSwapBuffers( Win->dpy, Win->win );
}

void reshapeCB(int width, int height)
{
    Win->width = width;
    Win->height = height;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0,0, width, height);

    gluPerspective(45.0, width/height, 0.1, 1000.0);

    displayCB();
}

//----------------------------------------------------------------------------


/** chooseFBConfig() - Try to find a framebuffer config that matches
 *    the specified pixel requirements.
 */

GLXFBConfig chooseFBConfig( Display *display, int screen )
{
  GLXFBConfig ret = 0;

  return ret;
}

//----------------------------------------------------------------------------
 
GLXContext createContext( Display *display, int screen,
                          GLXFBConfig fbconfig, XVisualInfo *visinfo,
                          Window window )
{
GLXContext context = NULL;


  return context;
}

//----------------------------------------------------------------------------

static void mouseCB	( int x/* pointer x coordinates in event window */
					, int y/* pointer y coordinates in event window */
					, unsigned int state /* key or button mask */)
{
    if (state & Button1Mask)
    {
                /* No button pressed */
                MyCam.eyeZ = (Win->height / 2) - y;
    } else
    {
        if (state & Button2Mask)
        {
            printf("Button2 !");
        } else
        {
            if (state & Button3Mask)
            {
                printf("Button3 !");
                printf("MyCam.eyeX %f\t", MyCam.eyeX);
                printf("MyCam.eyeY %f\t", MyCam.eyeY);
                printf("MyCam.eyeZ %f\t", MyCam.eyeZ);
                printf("MyCam.centerX %f\t", MyCam.centerX);
                printf("MyCam.centerY %f\t", MyCam.centerY);
                printf("MyCam.centerZ %f\t", MyCam.centerZ);
                printf("\n");
            } else
            {
            }  
        }
    }
    // Update view
    reshapeCB(Win->width, Win->height);
}
//----------------------------------------------------------------------------

static void keyboardCB( KeySym sym, unsigned char key, int x, int y,
                 short setting_change )
{
	switch ( tolower( key ) )
	{
            case 'k':
                printf( "You hit the 'k' key\n" );
            break;

            default:
                switch ( sym )
		{
                    case XK_Escape:
                        // ESCape - We're done!
			exit (0);
                    break;
                    case XK_Left  :
			MyCam.eyeX -= CameraStep;
                    break;
                    case XK_Right :
			MyCam.eyeX += CameraStep;
                    break;
                    case XK_Up  :
                    	MyCam.eyeY += CameraStep;
                    break;
                    case XK_Down  :
                        MyCam.eyeY -= CameraStep;
                    break;
                }
            break;
	}
        
        // Update view
        reshapeCB(Win->width, Win->height);
}
 
//----------------------------------------------------------------------------

int main( int argc, char *argv[] )
{

  // Create context and window
  Win = WinGL_create(WIN_XPOS, WIN_YPOS, WIN_XRES, WIN_YRES);

  // Go
  printf( "Valid keys: Left, Right, k, ESC\n" );
  printf( "Press ESC to quit\n" );

  WinGL_setOnResizeCB(Win, reshapeCB);
  WinGL_setDisplayCB(Win, displayCB);
  WinGL_setOnKeyboardCB(Win, keyboardCB);
  WinGL_setOnMouseCB(Win, mouseCB);

//  Load3DS (&Obj3ds,"./spaceship.3ds");
//  Obj3ds.id_texture=LoadBMP("./spaceshiptexture.bmp"); // The Function LoadBitmap() return the current texture ID
//  // If the last function returns -1 it means the file was not found so we exit from the program
//  if (Obj3ds.id_texture==-1)
//  {
//  	printf("Image file: spaceshiptexture.bmp not found\n");
//      //MessageBox(NULL,"Image file: spaceshiptexture.bmp not found", "Zetadeck",MB_OK | MB_ICONERROR);
//      exit (0);
//  }

  	/* XXX dtx_open_font opens a font file and returns a pointer to dtx_font */
	if(!(font = dtx_open_font("serif.ttf", 32))) {
		fprintf(stderr, "failed to open font\n");
		return 1;
	}
	/* XXX select the font and size to render with by calling dtx_use_font
	 * if you want to use a different font size, you must first call:
	 * dtx_prepare(font, size) once.
	 */
	dtx_use_font(font, 32);

  WinGL_mainLoop(Win);
 
  return 0;
}
