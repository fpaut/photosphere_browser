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
#include "wingl.h"

 
//----------------------------------------------------------------------------
 
const int   WIN_XPOS    = 50;
const int   WIN_YPOS    = 50;
const int   WIN_XRES    = 1280;
const int   WIN_YRES    = 960;
const int   NUM_SAMPLES = 4;

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
//Camera       MyCam = {100.0, 300.0, 30.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0};
Camera       MyCam = {5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0};
 
//----------------------------------------------------------------------------

 
void redraw()
{
//	static float r = 0.0;
//
//	    glRotated(r,0,0,1);
//	    glRotated(r,0,1,0);
//	    glRotated(r,1,0,0);
//	    r = r + 1.0;
//        printf("\n\r=%f\n\n", r);

	    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
	      // Top face (y = 1.0f)
	      // Define vertices in counter-clockwise (CCW) order with normal pointing out
	      glColor3f(0.0f, 1.0f, 0.0f);     // Green
	      glVertex3f( 1.0f, 1.0f, -1.0f);
	      glVertex3f(-1.0f, 1.0f, -1.0f);
	      glVertex3f(-1.0f, 1.0f,  1.0f);
	      glVertex3f( 1.0f, 1.0f,  1.0f);

	      // Bottom face (y = -1.0f)
	      glColor3f(1.0f, 0.5f, 0.0f);     // Orange
	      glVertex3f( 1.0f, -1.0f,  1.0f);
	      glVertex3f(-1.0f, -1.0f,  1.0f);
	      glVertex3f(-1.0f, -1.0f, -1.0f);
	      glVertex3f( 1.0f, -1.0f, -1.0f);

	      // Front face  (z = 1.0f)
	      glColor3f(1.0f, 0.0f, 0.0f);     // Red
	      glVertex3f( 1.0f,  1.0f, 1.0f);
	      glVertex3f(-1.0f,  1.0f, 1.0f);
	      glVertex3f(-1.0f, -1.0f, 1.0f);
	      glVertex3f( 1.0f, -1.0f, 1.0f);

	      // Back face (z = -1.0f)
	      glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
	      glVertex3f( 1.0f, -1.0f, -1.0f);
	      glVertex3f(-1.0f, -1.0f, -1.0f);
	      glVertex3f(-1.0f,  1.0f, -1.0f);
	      glVertex3f( 1.0f,  1.0f, -1.0f);

	      // Left face (x = -1.0f)
	      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	      glVertex3f(-1.0f,  1.0f,  1.0f);
	      glVertex3f(-1.0f,  1.0f, -1.0f);
	      glVertex3f(-1.0f, -1.0f, -1.0f);
	      glVertex3f(-1.0f, -1.0f,  1.0f);

	      // Right face (x = 1.0f)
	      glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
	      glVertex3f(1.0f,  1.0f, -1.0f);
	      glVertex3f(1.0f,  1.0f,  1.0f);
	      glVertex3f(1.0f, -1.0f,  1.0f);
	      glVertex3f(1.0f, -1.0f, -1.0f);
	   glEnd();  // End of drawing color-cube

	   // Render a pyramid consists of 4 triangles
//	   glLoadIdentity();                  // Reset the model-view matrix
	   glTranslatef(-1.5f, 0.0f, -6.0f);  // Move left and into the screen

	   glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
	      // Front
	      glColor3f(1.0f, 0.0f, 0.0f);     // Red
	      glVertex3f( 0.0f, 1.0f, 0.0f);
	      glColor3f(0.0f, 1.0f, 0.0f);     // Green
	      glVertex3f(-1.0f, -1.0f, 1.0f);
	      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	      glVertex3f(1.0f, -1.0f, 1.0f);

	      // Right
	      glColor3f(1.0f, 0.0f, 0.0f);     // Red
	      glVertex3f(0.0f, 1.0f, 0.0f);
	      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	      glVertex3f(1.0f, -1.0f, 1.0f);
	      glColor3f(0.0f, 1.0f, 0.0f);     // Green
	      glVertex3f(1.0f, -1.0f, -1.0f);

	      // Back
	      glColor3f(1.0f, 0.0f, 0.0f);     // Red
	      glVertex3f(0.0f, 1.0f, 0.0f);
	      glColor3f(0.0f, 1.0f, 0.0f);     // Green
	      glVertex3f(1.0f, -1.0f, -1.0f);
	      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
	      glVertex3f(-1.0f, -1.0f, -1.0f);

	      // Left
	      glColor3f(1.0f,0.0f,0.0f);       // Red
	      glVertex3f( 0.0f, 1.0f, 0.0f);
	      glColor3f(0.0f,0.0f,1.0f);       // Blue
	      glVertex3f(-1.0f,-1.0f,-1.0f);
	      glColor3f(0.0f,1.0f,0.0f);       // Green
	      glVertex3f(-1.0f,-1.0f, 1.0f);
	   glEnd();   // Done drawing the pyramid
}

static void draw3DRectangle(double dMinX_kls, double dMaxX_kls, double dMinY_kls, double dMaxY_kls, double dMinZ_kls, double dMaxZ_kls)
{ // werkt goed!!

  double MinX = fabs(dMinX_kls);
  double MaxX = fabs(dMaxX_kls);
  double MinY = fabs(dMinY_kls);
  double MaxY = fabs(dMaxY_kls);
  double MinZ = fabs(dMinZ_kls);
  double MaxZ = fabs(dMaxZ_kls);

  double sizeX = fabs( fabs(dMaxX_kls)-fabs(dMinX_kls) );
  double sizeY = fabs( fabs(dMaxY_kls)-fabs(dMinY_kls) );
  double sizeZ = fabs( fabs(dMaxZ_kls)-fabs(dMinZ_kls) );

  GLdouble V0[] = { 0.0, 0.0, 0.0};
  GLdouble V1[] = { sizeX, 0.0, 0.0};
  GLdouble V2[] = { sizeX, sizeY, 0.0};
  GLdouble V3[] = { 0.0, sizeY, 0.0};
  GLdouble V4[] = { 0.0, 0.0, sizeZ};
  GLdouble V5[] = { sizeX, 0.0, sizeZ};
  GLdouble V6[] = { sizeX, sizeY, sizeZ};
  GLdouble V7[] = { 0.0, sizeY, sizeZ};

  glPushMatrix();
  glTranslatef(dMinX_kls, dMinY_kls, dMinZ_kls);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  glBegin(GL_QUADS);
	glVertex3dv(V0); glVertex3dv(V1); glVertex3dv(V2); glVertex3dv(V3);        // Surface 1
	glVertex3dv(V1); glVertex3dv(V5); glVertex3dv(V6); glVertex3dv(V2);        // Surface 2
	glVertex3dv(V5); glVertex3dv(V4); glVertex3dv(V7); glVertex3dv(V6);        // Surface 3
	glVertex3dv(V4); glVertex3dv(V0); glVertex3dv(V3); glVertex3dv(V7);        // Surface 4
	glVertex3dv(V3); glVertex3dv(V2); glVertex3dv(V6); glVertex3dv(V7);        // Surface 5
	glVertex3dv(V0); glVertex3dv(V4); glVertex3dv(V5); glVertex3dv(V1);        // Surface 6
  glEnd();

  glPopMatrix();

}

void drawaxes(void)
{
    glColor3ub(255, 0, 0);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    glVertex3f(0.75, 0.25, 0.0);
    glVertex3f(0.75, -0.25, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    glVertex3f(0.75, 0.0, 0.25);
    glVertex3f(0.75, 0.0, -0.25);
    glVertex3f(1.0, 0.0, 0.0);
    glEnd();
    glColor3ub(0, 255, 0);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.75, 0.25);
    glVertex3f(0.0, 0.75, -0.25);
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(0.25, 0.75, 0.0);
    glVertex3f(-0.25, 0.75, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glEnd();
    glColor3ub(0, 0, 255);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 1.0);
    glVertex3f(0.25, 0.0, 0.75);
    glVertex3f(-0.25, 0.0, 0.75);
    glVertex3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.25, 0.75);
    glVertex3f(0.0, -0.25, 0.75);
    glVertex3f(0.0, 0.0, 1.0);
    glEnd();

//    glColor3ub(255, 255, 0);
//    glRasterPos3f(1.1, 0.0, 0.0);
////    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'x');
//    glRasterPos3f(0.0, 1.1, 0.0);
////    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'y');
//    glRasterPos3f(0.0, 0.0, 1.1);
////    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'z');
}
 
void displayCB(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(MyCam.eyeX, MyCam.eyeY, MyCam.eyeZ, MyCam.centerX, MyCam.centerY, MyCam.centerZ, MyCam.upX, MyCam.upY, MyCam.upZ);
	glColor3f(0.0, 1.0, 0.0);

//	// rotate complete axis system
//	glRotatef(-90, 1.0, 0.0, 0.0); // rotate around x axis
//	glRotatef(90, 0.0, 0.0, 1.0); // rotate around z axis
//
	drawaxes();


	glXSwapBuffers( Win->dpy, Win->win );
}

//void displayCB()
//{
//
//	 glMatrixMode(GL_MODELVIEW);
////	 gluPerspective (GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
////	 redraw();
//
//
//	   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
//	   glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
//
//		 gluLookAt(MyCam.eyeX, MyCam.eyeY, MyCam.eyeZ, MyCam.centerX, MyCam.centerY, MyCam.centerZ, MyCam.upX, MyCam.upY, MyCam.upZ);
//	   // Render a color-cube consisting of 6 quads with different colors
//	   glLoadIdentity();                 // Reset the model-view matrix
//	   glTranslatef(1.5f, 0.0f, -7.0f);  // Move right and into the screen
//	  glBegin(GL_QUADS);
//	   glColor3f(1., 0., 0.); glVertex3f(-.75, -.75, 0.);
//	   glColor3f(0., 1., 0.); glVertex3f( .75, -.75, 0.);
//	   glColor3f(0., 0., 1.); glVertex3f( .75,  .75, 0.);
//	   glColor3f(1., 1., 0.); glVertex3f(-.75,  .75, 0.);
//	  glEnd();
//
//
//	 // Display it
//	  glXSwapBuffers( Win->dpy, Win->win );
//}

//void reshapeCB( int width, int height )
//{
//  Win->width = width;
//  Win->height = height;
//  glViewport(0, 0, Win->width, Win->height);
//  glMatrixMode(GL_PROJECTION);
//  glLoadIdentity();
////  glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
//  gluPerspective(60.0, Win->width/Win->height, 1.0, 20.0);
//  glMatrixMode(GL_MODELVIEW);
//}

void reshapeCB(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(60.0, width/height, 0.1, 10.0);

	glOrtho(-4, 4, -0.5, 4, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glEnable(GL_DEPTH_TEST);

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
	printf("MOUSE x %d, y %d, state %d\n", x, y, state);
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
  Win = WinGL_create(0, 0, WIN_XRES, WIN_YRES);

  // Go
  printf( "Valid keys: Left, Right, k, ESC\n" );
  printf( "Press ESC to quit\n" );

  WinGL_setOnResizeCB(Win, reshapeCB);
  WinGL_setDisplayCB(Win, displayCB);
  WinGL_setOnKeyboardCB(Win, keyboardCB);
  WinGL_setOnMouseCB(Win, mouseCB);

  WinGL_mainLoop(Win);
 
  return 0;
}
