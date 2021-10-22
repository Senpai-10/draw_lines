#include <iostream>
#include <X11/Xlib.h>

void close_window(Display *display, Window window, GC gc) 
{
  XFreeGC(display, gc);
  XDestroyWindow(display, window);
  XCloseDisplay(display);
  exit(0);
}