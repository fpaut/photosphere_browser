#include<X11/X.h>
#include<X11/Xlib.h>
#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>

/* requests a change to the size of the current window */
typedef void (OnResize)(int width, int height);
/* display callback for the current window */
typedef void (display)(void);
/* Keyboard events */
typedef void (OnKeyboard)( KeySym sym, unsigned char key, int x, int y, short setting_change );
/* Mouse events */
typedef void (OnMouse)	( int x/* pointer x coordinates in event window */
						, int y/* pointer y coordinates in event window */
						, unsigned int state /* key or button mask */);


typedef struct MyWin
{
    Display                 *dpy;
    Window                  win;
    int                     displayed;
    int                     x;
    int                     y;
    int                     width;
    int                     height;
    XVisualInfo *xvi;
    Colormap                cmap;
    XSetWindowAttributes    swa;
    GLXContext              glc;
    XWindowAttributes       gwa;
    XEvent                  xev;

    // Callback functions
    OnResize 				*OnResize;
    OnKeyboard				*OnKeyboard;
    OnMouse					*OnMouse;
    display					*display;
} MyWin;


//----------------------------------------------------------------------------

extern MyWin *WinGL_create(int x, int y, int width, int height);
extern void WinGL_mainLoop(MyWin *win);
extern void WinGL_setOnResizeCB(MyWin *win, OnResize *OnResizeCB);
extern void WinGL_setDisplayCB(MyWin *win, display *displayCB);
extern void WinGL_setOnKeyboardCB(MyWin *win, OnKeyboard *OnKeyboardCB);
extern void WinGL_setOnMouseCB(MyWin *win, OnMouse *OnMouseCB);
