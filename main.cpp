#include "main.h"

#include <iostream>

class EventContainer
{
  
  Display* eDpy;
  XEvent event;
public :
  EventContainer(Display* dpy)
  {
    eDpy = dpy;
    
  }

  int keyUpper(int inKey)
  {
    if (inKey>='a' && inKey<='z')
      inKey^=('a'^'A');
    return(inKey);
  }
  
  DKeysym::e_DKeysym translateKeySym(int inKey)
  {
    switch (inKey)
      {
      case XK_Escape:
	return DKeysym::DK_Escape;
	break;
      case XK_A:
	return DKeysym::DK_Key_a;
	break;
      case XK_B:
	return DKeysym::DK_Key_b;
	break;
      case XK_C:
	return DKeysym::DK_Key_c;
	break;
      case XK_D:
	return DKeysym::DK_Key_d;
	break;
      case XK_E:
	return DKeysym::DK_Key_e;
	break;
      case XK_F:
	return DKeysym::DK_Key_f;
	break;
      case XK_G:
	return DKeysym::DK_Key_g;
	break;
      case XK_H:
	return DKeysym::DK_Key_h;
	break;
      case XK_I:
	return DKeysym::DK_Key_i;
	break;
      case XK_J:
	return DKeysym::DK_Key_j;
	break;
      case XK_K:
	return DKeysym::DK_Key_k;
	break;
      case XK_L:
	return DKeysym::DK_Key_l;
	break;
      case XK_M:
	return DKeysym::DK_Key_m;
	break;
      case XK_N:
	return DKeysym::DK_Key_n;
	break;
      case XK_O:
	return DKeysym::DK_Key_o;
	break;
      case XK_P:
	return DKeysym::DK_Key_p;
	break;
      case XK_Q:
	return DKeysym::DK_Key_q;
	break;
      case XK_R:
	return DKeysym::DK_Key_r;
	break;
      case XK_S:
	return DKeysym::DK_Key_s;
	break;
      case XK_T:
	return DKeysym::DK_Key_t;
	break;
      case XK_U:
	return DKeysym::DK_Key_u;
	break;
      case XK_V:
	return DKeysym::DK_Key_v;
	break;
      case XK_W:
	return DKeysym::DK_Key_w;
	break;
      case XK_X:
	return DKeysym::DK_Key_x;
	break;
      case XK_Y:
	return DKeysym::DK_Key_y;
	break;
      case XK_Z:
	return DKeysym::DK_Key_z;
	break;
      case XK_1:
	return DKeysym::DK_Key_1;
	break;
      case XK_2:
	return DKeysym::DK_Key_2;
	break;
      case XK_3:
	return DKeysym::DK_Key_3;
	break;
      case XK_4:
	return DKeysym::DK_Key_4;
	break;
      case XK_5:
	return DKeysym::DK_Key_5;
	break;
      case XK_6:
	return DKeysym::DK_Key_6;
	break;
      case XK_7:
	return DKeysym::DK_Key_7;
	break;
      case XK_8:
	return DKeysym::DK_Key_8;
	break;
      case XK_9:
	return DKeysym::DK_Key_9;
	break;
      case XK_0:
	return DKeysym::DK_Key_0;
	break;
      }
  }
  
  input::s_mouseEvent translateMotionEvent(XMotionEvent* event)
  {
    input::s_mouseEvent mEvent;
    mEvent.type = input::e_mMotion;
    mEvent.xPos = event->x;
    mEvent.yPos = event->y;
    return mEvent;
  }
  
  input::s_mouseEvent translateButtonEvent(XButtonEvent* event)
  {
    input::s_mouseEvent mEvent;
    switch (event->type)
      {
      case ButtonPress:
	mEvent.type = input::e_mButtonPress;
	break;
      case ButtonRelease:
	mEvent.type = input::e_mButtonRelease;
	break;
      default:
	std::cout << "Error: Not mouse event passed to Diabolical.cpp/translateButtonEvent" << std::endl;
	break;
      }
    mEvent.xPos = event->x;
    mEvent.yPos = event->y;
    mEvent.button = event->button;
    return mEvent;
  }

  input::s_DEvent pollEvent()
  {
    input::s_DEvent result;

    if (XPending(eDpy))
      {
	XNextEvent(eDpy,&event);
	switch(event.type)
	  {
	  case KeyPress:
	    {
	      XKeyEvent* keyEvent;
	      keyEvent = &event.xkey;
	      result.type = input::e_keyEvent;
	      result.key = translateKeySym(keyUpper(XLookupKeysym(keyEvent,0)));
	      return result;
	    }
	    break;
	  case KeyRelease:
	    break;
	  case MotionNotify:
	    break;
	  case ButtonPress:
	    break;
	  case ButtonRelease:
	    break;
	  }
      }
  }
};

int singleBufferAttributes[] = 
  {
    GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
    GLX_RENDER_TYPE, GLX_RGBA_BIT,
    GLX_RED_SIZE, 1,
    GLX_GREEN_SIZE, 1,
    GLX_BLUE_SIZE, 1,
    None
  };

int doubleBufferedAttributes[]  = 
  {
    GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
    GLX_RENDER_TYPE, GLX_RGBA_BIT,
    GLX_DOUBLEBUFFER, True,
    GLX_RED_SIZE, 1,
    GLX_GREEN_SIZE, 1,
    GLX_BLUE_SIZE, 1,
    None
  };

static Bool WaitForNotify(Display *dpy, XEvent *event, XPointer arg)
{
  return (event->type == MapNotify) && (event->xmap.window == (Window) arg);
}



int main(int argc, char** argv)
{
  Display *dpy;
  Window xWin;
  XEvent event;
  XVisualInfo *vInfo;
  XSetWindowAttributes swa;
  GLXFBConfig *fbConfigs;
  GLXContext context;
  GLXWindow glxWin;
  int swaMask;
  int numReturned;
  int swapFlag = True;
  bool running = true;

  /* Open the connection to the X server */
  dpy = XOpenDisplay(NULL);
  if (dpy == NULL)
    {
      std::cout << "Unable to open connection to X Server" << std::endl;
      exit(EXIT_FAILURE);
    }

  /* Request suitable framebuffer configuration */
  fbConfigs = glXChooseFBConfig(dpy, DefaultScreen(dpy), doubleBufferedAttributes, &numReturned);
  if (fbConfigs == NULL) // Couldn't get a double buffer
    {
      fbConfigs = glXChooseFBConfig(dpy, DefaultScreen(dpy), singleBufferAttributes, &numReturned);
      swapFlag = false;
    }

  /* Create an X Colormap and window with a visual */
  vInfo = glXGetVisualFromFBConfig(dpy, fbConfigs[0]);

  swa.border_pixel = 0;
  swa.event_mask = StructureNotifyMask;
  swa.colormap = XCreateColormap(dpy, RootWindow(dpy, vInfo->screen),vInfo->visual,AllocNone);

  swaMask = CWBorderPixel | CWColormap | CWEventMask;

  xWin = XCreateWindow(dpy, RootWindow(dpy,vInfo->screen),0,0,800,600,0,vInfo->depth,InputOutput,
		       vInfo->visual,swaMask,&swa);

  /* Create a GLX context for OpenGL rendering */
  context = glXCreateNewContext(dpy, fbConfigs[0], GLX_RGBA_TYPE, NULL, True);
  
  /* Createa a GLX window to associate the frame buffer configuration */
  glxWin = glXCreateWindow(dpy, fbConfigs[0], xWin, NULL);

  /* Map lthe window to the screen and wait for it to appear */
  XMapWindow(dpy, xWin);
  XIfEvent(dpy, &event, WaitForNotify, (XPointer) xWin);

  /* Bind the GLX context to the window */
  glXMakeContextCurrent(dpy, glxWin, glxWin, context);
  
  XSelectInput(dpy, xWin, InputOutput | PointerMotionMask | ButtonPressMask | ButtonReleaseMask);

  EventContainer container(dpy);

  //glEnable(GL_TEXTURE_2D);
  //sleep(10);
  
  while (application.isRunning())
    {
      if (XPending(dpy))
	{
	  application.addEvent(container.pollEvent());
	}      
      application.onExecute();
    }
  exit(EXIT_SUCCESS);

}
