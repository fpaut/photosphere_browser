#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/time.h>
#include "glwin.h"


//-----------------------------------------------------------------------------

/// check() - Check for GL errors, and report any queued
static void check( const char hdr[])
{
  int err;

  while ( ( err = glGetError() ) != GL_NO_ERROR )
    fprintf( stderr, "OpenGL Error at %s: %s\n", hdr, gluErrorString(err) );
}

//----------------------------------------------------------------------------

static double elapsedMsec( struct timeval *start, struct timeval *stop )
{
  return ( ( stop->tv_sec  - start->tv_sec  ) * 1000.0 +
           ( stop->tv_usec - start->tv_usec ) / 1000.0 );
}

//----------------------------------------------------------------------------

static double elapsedUsec( const struct timeval *start, const struct timeval *stop )
{
  return ( ( stop->tv_sec  - start->tv_sec  ) * 1000000.0 +
           ( stop->tv_usec - start->tv_usec ) );
}
//----------------------------------------------------------------------------

static void processXEvents(MyWin *win, Atom wm_protocols, Atom wm_delete_window )
{
  short setting_change = false;

  while ( XEventsQueued( win->dpy, QueuedAfterFlush ) )
  {
    XEvent    event;

    XNextEvent( win->dpy, &event );

    if( event.xany.window != win->win )
      continue;

    switch ( event.type )
    {
    	case Expose:
    	{
//            XConfigureEvent *cevent = &event.xconfigure;
//            if (win->OnResize != NULL)
//            	win->OnResize(cevent->width, cevent->height );
            win->displayed = true;
    	}
        break;
    	case MapNotify:
        {
          win->displayed = true;
          break;
        }
    	case ConfigureNotify:
        {
          XConfigureEvent *cevent = &event.xconfigure;
          if (win->OnResize != NULL)
        	  win->OnResize(cevent->width, cevent->height );
          break;
        }
    	case KeyPress:
        {
          char      chr;
          KeySym    symbol;
          XComposeStatus status;

          XLookupString( &event.xkey, &chr, 1, &symbol, &status );
          if (win->OnKeyboard != NULL)
        	  win->OnKeyboard( symbol, chr, event.xkey.x, event.xkey.y, setting_change );
          break;
        }
    	case ButtonPress:
   	case ButtonRelease:
    	case MotionNotify:
            if (win->OnMouse != NULL)
            	win->OnMouse( event.xmotion.x, event.xmotion.y, event.xmotion.state );
        break;
    	case ClientMessage:
        {
          if ( event.xclient.message_type      == wm_protocols &&
               (unsigned long)( event.xclient.data.l[0] ) == wm_delete_window )
          {
            //printf( "Received WM_DELETE_WINDOW\n" );
            exit(0);
          }
          break;
        }
    }
  }
}

//----------------------------------------------------------------------------

void WinGL_setOnResizeCB(MyWin *win, OnResize *OnResizeCB)
{
	if (win)
		win->OnResize = OnResizeCB;
}

//----------------------------------------------------------------------------

void WinGL_setDisplayCB(MyWin *win, display *displayCB)
{
	if (win)
		win->display = displayCB;
}

//----------------------------------------------------------------------------

void WinGL_setOnKeyboardCB(MyWin *win, OnKeyboard *OnKeyboardCB)
{
	if (win)
		win->OnKeyboard = OnKeyboardCB;
}

//----------------------------------------------------------------------------

void WinGL_setOnMouseCB(MyWin *win, OnMouse *OnMouseCB)
{
	if (win)
		win->OnMouse = OnMouseCB;
}

//----------------------------------------------------------------------------

MyWin *WinGL_create(int x, int y, int width, int height)
{
	int ret = 0;
	static MyWin        win;
//	GLint        att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
	GLint        att[] = { GLX_RGBA, GLX_DOUBLEBUFFER, None };

	win.x		= x;
	win.y		= y;
	win.width	= width;
	win.height	= height;

	win.dpy = XOpenDisplay("");

	if(win.dpy == NULL) {
		printf("\n\tcannot connect to X server\n\n");
		exit(0);
	}

	win.win = DefaultRootWindow(win.dpy);

	win.xvi = glXChooseVisual(win.dpy, 0, att);

	if(win.xvi == NULL) {
		printf("\n\tno appropriate visual found\n\n");
		exit(0);
	}
	else {
		printf("\n\tvisual %p selected\n", (void *)win.xvi->visualid); /* %p creates hexadecimal output like in glxinfo */
	}


	win.cmap = XCreateColormap(win.dpy, win.win, win.xvi->visual, AllocNone);

	win.swa.colormap = win.cmap;

//	 win.swa.event_mask = ExposureMask | KeyPressMask;
	win.swa.event_mask = 	ExposureMask | KeyPressMask | StructureNotifyMask | KeyPressMask | KeyReleaseMask |
						PointerMotionMask | ButtonPressMask | ButtonReleaseMask | ExposureMask |
						FocusChangeMask | VisibilityChangeMask | EnterWindowMask | LeaveWindowMask | PropertyChangeMask;

	win.win = XCreateWindow(win.dpy, win.win, 0, 0, win.width, win.height, 0, win.xvi->depth, InputOutput, win.xvi->visual, CWColormap | CWEventMask, &win.swa);

	ret = XMapWindow(win.dpy, win.win);
	printf ("XMapWindow return %d\n", ret);
	ret = XStoreName(win.dpy, win.win, "VERY SIMPLE APPLICATION");
	printf ("XStoreName return %d\n", ret);

	win.glc = glXCreateContext(win.dpy, win.xvi, NULL, GL_TRUE);
	glXMakeCurrent(win.dpy, win.win, win.glc);

    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)

    glEnable(GL_TEXTURE_2D); // This Enable the Texture mapping


	check( "createWindow()" );
	printf( "Window Size    = %d x %d\n", win.width, win.height );

	return &win;
}

//----------------------------------------------------------------------------

void WinGL_mainLoop(MyWin *win)
{
  static struct timeval last_xcheck   = {0,0};
  struct timeval now;

  // Register to receive window close events (the "X" window manager button)
  Atom wm_protocols     = XInternAtom( win->dpy, "WM_PROTOCOLS"    , False);
  Atom wm_delete_window = XInternAtom( win->dpy, "WM_DELETE_WINDOW", False);
  XSetWMProtocols( win->dpy, win->win, &wm_delete_window, True );


  while (1)
  {
    // Redraw window (after it's mapped)
    if ( win->displayed && win->display != NULL)
      win->display();

    // Update frame rate
    gettimeofday( &now, 0 );

    // Check X events every 1/10 second
    if ( elapsedMsec( &last_xcheck, &now ) > 100 )
    {
      processXEvents( win, wm_protocols, wm_delete_window );
      last_xcheck = now;
    }
  }
}


