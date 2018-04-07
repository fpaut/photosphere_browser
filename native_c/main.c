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
const int   WIN_XRES    = 641;
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
Camera       MyCam = {00.0, 0.0, 10.0, 0.0, -0.0, 0.0, 0.0, 1.0, 0.0};

// 3DS Obj3ds
obj_3ds Obj3ds;
 
/* XXX fonts are represented by the opaque struct dtx_font type, so you
 * need to create at least one with dtx_open_font (see main).
 */
struct dtx_font *font;
//----------------------------------------------------------------------------

 
void gl_printf(float x, float y, const char *fmt, ...)
{
	va_list ap;
	int buf_size;
	char *buf, tmp;

	va_start(ap, fmt);
	buf_size = vsnprintf(&tmp, 0, fmt, ap);
	va_end(ap);

	if(buf_size == -1) {
		buf_size = 512;
	}

	buf = alloca(buf_size + 1);
	va_start(ap, fmt);
	vsnprintf(buf, buf_size + 1, fmt, ap);
	va_end(ap);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
 	glPushMatrix();
        {
            static float rot = 0;
            
//            rot +=1;  printf("rot = %f\n", rot);
//            glRotatef(rot, 1, 0, 0);
            glRotatef(90, 0, 1, 0);

            glTranslatef(x, y, 0);
            glColor3f(1, 1, 1);
            /* XXX call dtx_string to draw utf-8 text.
             * any transformations and the current color apply
             */
            dtx_string(buf);
        }
	glPopMatrix();
}



void displayCB(void)
{
    static float rot =0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glLoadIdentity();
    gluLookAt(MyCam.eyeX, MyCam.eyeY, MyCam.eyeZ, MyCam.centerX, MyCam.centerY, MyCam.centerZ, MyCam.upX, MyCam.upY, MyCam.upZ);
//    printf("LookAt eye position X %f,Y %f,Z %f\n,eye look X %f, Y %f, Z %f\n\n"	, MyCam.eyeX, MyCam.eyeY, MyCam.eyeZ
//                                                                                , MyCam.centerX, MyCam.centerY, MyCam.centerZ);
	glColor3f(0.0, 1.0, 0.0);

  	drawaxes();
        
        glPolygonMode (GL_FRONT_AND_BACK, GL_LINE); // Polygon rasterization mode (polygon outlined)
//        quad();

        
        gl_printf(0, 1, "TEST");


	glXSwapBuffers( Win->dpy, Win->win );
}

void reshapeCB(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

//    glOrtho(-4, 4, -0.5, 4, -10, 1000.0);
    gluPerspective(45.0, width/height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(-width/2, width/2, -height/2, height/2, -1, 1);
}

//----------------------------------------------------------------------------

static void mouseCB	( int x/* pointer x coordinates in event window */
					, int y/* pointer y coordinates in event window */
					, unsigned int state /* key or button mask */)
{
    if (state & Button1Mask)
    {
        printf("Button1 !");
    }
    if (state & Button2Mask)
    {
        printf("Button2 !");
    }
    if (state & Button3Mask)
    {
        printf("Button3 !");
    }
//	printf("MOUSE x %d, y %d, state %d\n", x, y, state);
//	MyCam.eyeX = x; printf("MyCam.eyeX %f\t", MyCam.eyeX);
//	MyCam.eyeY = x; printf("MyCam.eyeY %f\t", MyCam.eyeY);
//	MyCam.eyeZ = x; printf("MyCam.eyeZ %f\t", MyCam.eyeZ);
//	MyCam.centerX = -x/10; printf("MyCam.centerX %f\t", MyCam.centerX);
//	MyCam.centerY = x/10; printf("MyCam.centerY %f\t", MyCam.centerY);
//	MyCam.centerZ = x/10; printf("MyCam.centerZ %f\t", MyCam.centerZ);
	printf("\n");
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

static void keyboardCB( KeySym sym, unsigned char key, int x, int y,
                 short setting_change )
{
	float step = 5.0;

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
				MyCam.eyeX -= step;
				printf( "CameraX = %f\n", MyCam.eyeX );
			break;
			case XK_Right :
				MyCam.eyeX += step;
				printf( "CameraX = %f\n", MyCam.eyeX );
			break;
			case XK_Up  :
				MyCam.eyeY += step;
				printf( "CameraY = %f\n", MyCam.eyeY );
			break;
			case XK_Down  :
				MyCam.eyeY -= step;
				printf( "CameraY = %f\n", MyCam.eyeY );
			break;
	  }
	  break;
	}
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

  Load3DS (&Obj3ds,"./spaceship.3ds");
  Obj3ds.id_texture=LoadBMP("./spaceshiptexture.bmp"); // The Function LoadBitmap() return the current texture ID
  // If the last function returns -1 it means the file was not found so we exit from the program
  if (Obj3ds.id_texture==-1)
  {
  	printf("Image file: spaceshiptexture.bmp not found\n");
      //MessageBox(NULL,"Image file: spaceshiptexture.bmp not found", "Zetadeck",MB_OK | MB_ICONERROR);
      exit (0);
  }

  	/* XXX dtx_open_font opens a font file and returns a pointer to dtx_font */
	if(!(font = dtx_open_font("serif.ttf", 24))) {
		fprintf(stderr, "failed to open font\n");
		return 1;
	}
	/* XXX select the font and size to render with by calling dtx_use_font
	 * if you want to use a different font size, you must first call:
	 * dtx_prepare(font, size) once.
	 */
	dtx_use_font(font, 24);

  WinGL_mainLoop(Win);
 
  return 0;
}
