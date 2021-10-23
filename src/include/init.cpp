#include <iostream>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

#include "draw.h"
#include "close.h"

void clear_screen();
unsigned long RGB(int r, int g, int b);

Display *display;
int screen;
Window window;
GC gc;
unsigned long black, white, red, blue;

struct coord 
{
  int x, y;
} dot;

void init() 
{
  dot.x=0; dot.y=0;
  int height = 300;
  int width = 300;
  const char * window_name = "draw";
  const char * window_icon_name = "icon";

  display=XOpenDisplay((char *)0);
  screen=DefaultScreen(display);
  black=BlackPixel(display, screen);
  white=WhitePixel(display, screen);
  red=RGB(255,0,0);
  blue=RGB(0,0,255);

  struct Window_Colors
  {
    unsigned long Background = black;
    unsigned long Foreground = white;
  } window_colors;

  window=XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, height, width, 5, window_colors.Foreground, window_colors.Background);
  XSetStandardProperties(display, window, window_name, window_icon_name, None, NULL, 0, NULL); 
  XSelectInput(display, window, ExposureMask | ButtonPressMask | KeyPressMask);
  gc=XCreateGC(display, window, 0, 0);
  XSetBackground(display, gc, white);
  XSetForeground(display, gc, black);

  XClearWindow(display, window);
  XMapRaised(display, window);

  XEvent event;
  KeySym key;
  char text[255];

  while (1) 
  {
    XNextEvent(display, &event);
    if (event.type==Expose && event.xexpose.count==0) {
      draw(display, window);
    }

    if (event.type==KeyPress && XLookupString(&event.xkey, text, 255, &key, 0)==1) {
      if (text[0] == 'c') {
        clear_screen();
      }
      if (text[0] == 'q') {
        close_window(display, window, gc);
      }
    } 

    if (event.type==ButtonPress) {
      int x = event.xbutton.x, y = event.xbutton.y;

      if (dot.x != 0 && dot.y != 0) 
      {
        XSetForeground(display, gc, red);
        XDrawLine(display, window, gc, dot.x, dot.y, x, y);

        // XSetForeground(display, gc, white);
        // strcpy(text, " ");
        // XDrawString(display, window, gc, x, y, text, strlen(text));
      } else {
        /*
          Draw a dot to show the user where is the starting point
        */ 
        XSetForeground(display, gc, red);
        XDrawLine(display, window, gc, x, y, x, y);
      }
      
      dot.x=x; dot.y=y;
    }
  }
}

void clear_screen() 
{
  XClearWindow(display, window);
  dot.x = 0; dot.y = 0;
}

unsigned long RGB(int r, int g, int b) 
{
  return b + (g<<8) + (r<<16);
}