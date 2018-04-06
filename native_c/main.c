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
#include "3ds.h"
#include "bmp.h"
#include "wingl.h"
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
//Camera       MyCam = {100.0, 300.0, 30.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0};
Camera       MyCam = {-1.0, -1.0, -1.0, 0.0, -0.0, 0.0, 0.0, 0.0, 1.0};

// 3DS Obj3ds
obj_3ds Obj3ds;
 
/* XXX fonts are represented by the opaque struct dtx_font type, so you
 * need to create at least one with dtx_open_font (see main).
 */
struct dtx_font *font;
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

//static void draw3DRectangle(double dMinX_kls, double dMaxX_kls, double dMinY_kls, double dMaxY_kls, double dMinZ_kls, double dMaxZ_kls)
//{ // werkt goed!!
//
//  double MinX = fabs(dMinX_kls);
//  double MaxX = fabs(dMaxX_kls);
//  double MinY = fabs(dMinY_kls);
//  double MaxY = fabs(dMaxY_kls);
//  double MinZ = fabs(dMinZ_kls);
//  double MaxZ = fabs(dMaxZ_kls);
//
//  double sizeX = fabs( fabs(dMaxX_kls)-fabs(dMinX_kls) );
//  double sizeY = fabs( fabs(dMaxY_kls)-fabs(dMinY_kls) );
//  double sizeZ = fabs( fabs(dMaxZ_kls)-fabs(dMinZ_kls) );
//
//  GLdouble V0[] = { 0.0, 0.0, 0.0};
//  GLdouble V1[] = { sizeX, 0.0, 0.0};
//  GLdouble V2[] = { sizeX, sizeY, 0.0};
//  GLdouble V3[] = { 0.0, sizeY, 0.0};
//  GLdouble V4[] = { 0.0, 0.0, sizeZ};
//  GLdouble V5[] = { sizeX, 0.0, sizeZ};
//  GLdouble V6[] = { sizeX, sizeY, sizeZ};
//  GLdouble V7[] = { 0.0, sizeY, sizeZ};
//
//  glPushMatrix();
//  glTranslatef(dMinX_kls, dMinY_kls, dMinZ_kls);
//
//  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
//  glBegin(GL_QUADS);
//	glVertex3dv(V0); glVertex3dv(V1); glVertex3dv(V2); glVertex3dv(V3);        // Surface 1
//	glVertex3dv(V1); glVertex3dv(V5); glVertex3dv(V6); glVertex3dv(V2);        // Surface 2
//	glVertex3dv(V5); glVertex3dv(V4); glVertex3dv(V7); glVertex3dv(V6);        // Surface 3
//	glVertex3dv(V4); glVertex3dv(V0); glVertex3dv(V3); glVertex3dv(V7);        // Surface 4
//	glVertex3dv(V3); glVertex3dv(V2); glVertex3dv(V6); glVertex3dv(V7);        // Surface 5
//	glVertex3dv(V0); glVertex3dv(V4); glVertex3dv(V5); glVertex3dv(V1);        // Surface 6
//  glEnd();
//
//  glPopMatrix();
//
//}
//
//----------------------------------------------------------------------------

void display3DSobj(obj_3ds_ptr pObj3ds)
{
    int l_index;


    glBindTexture(GL_TEXTURE_2D, pObj3ds->id_texture); // We set the active texture

    glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
    for (l_index=0;l_index<pObj3ds->polygons_qty;l_index++)
    {
        //----------------- FIRST VERTEX -----------------
        // Texture coordinates of the first vertex
        glTexCoord2f( pObj3ds->mapcoord[ pObj3ds->polygon[l_index].a ].u,
                      pObj3ds->mapcoord[ pObj3ds->polygon[l_index].a ].v);
        // Coordinates of the first vertex
        glVertex3f( pObj3ds->vertex[ pObj3ds->polygon[l_index].a ].x,
                    pObj3ds->vertex[ pObj3ds->polygon[l_index].a ].y,
                    pObj3ds->vertex[ pObj3ds->polygon[l_index].a ].z); //Vertex definition

        //----------------- SECOND VERTEX -----------------
        // Texture coordinates of the second vertex
        glTexCoord2f( pObj3ds->mapcoord[ pObj3ds->polygon[l_index].b ].u,
                      pObj3ds->mapcoord[ pObj3ds->polygon[l_index].b ].v);
        // Coordinates of the second vertex
        glVertex3f( pObj3ds->vertex[ pObj3ds->polygon[l_index].b ].x,
                    pObj3ds->vertex[ pObj3ds->polygon[l_index].b ].y,
                    pObj3ds->vertex[ pObj3ds->polygon[l_index].b ].z);

        //----------------- THIRD VERTEX -----------------
        // Texture coordinates of the third vertex
        glTexCoord2f( pObj3ds->mapcoord[ pObj3ds->polygon[l_index].c ].u,
                      pObj3ds->mapcoord[ pObj3ds->polygon[l_index].c ].v);
        // Coordinates of the Third vertex
        glVertex3f( pObj3ds->vertex[ pObj3ds->polygon[l_index].c ].x,
                    pObj3ds->vertex[ pObj3ds->polygon[l_index].c ].y,
                    pObj3ds->vertex[ pObj3ds->polygon[l_index].c ].z);
    }
    glEnd();

    glFlush(); // This force the execution of OpenGL commands
}

void drawaxes(void)
{
    // X
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
    // Y
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
    // Z
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
    static float rot =0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    gluLookAt(MyCam.eyeX, MyCam.eyeY, MyCam.eyeZ, MyCam.centerX, MyCam.centerY, MyCam.centerZ, MyCam.upX, MyCam.upY, MyCam.upZ);
//    printf("LookAt eye position X %f,Y %f,Z %f\n,eye look X %f, Y %f, Z %f\n\n"	, MyCam.eyeX, MyCam.eyeY, MyCam.eyeZ
//                                                                                , MyCam.centerX, MyCam.centerY, MyCam.centerZ);
	glColor3f(0.0, 1.0, 0.0);

  	drawaxes();
      glPolygonMode (GL_FRONT_AND_BACK, GL_LINE); // Polygon rasterization mode (polygon outlined)

        
	glMatrixMode(GL_MODELVIEW);
 	glPushMatrix();
        rot +=1;  printf("rot = %f\n", rot);
        glRotatef(rot, 1, 0, 0);
        
	glTranslatef(-200, 1, 0);
//	drawaxes();
 	glColor3f(1, 1, 1);
	/* XXX call dtx_string to draw utf-8 text.
	 * any transformations and the current color apply
	 */
	dtx_string("TEST");
	glPopMatrix();

//        display3DSobj(&Obj3ds);


	glXSwapBuffers( Win->dpy, Win->win );
}

void reshapeCB(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-4, 4, -0.5, 4, -10, 1000.0);
    gluPerspective(60.0, width/height, 0.1, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    displayCB();
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
