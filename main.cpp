#include <stdio.h>
#include <stdlib.h>
#include <string>

// include X11 files
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

Display *display;

int screen;
Window window;
GC gc;
unsigned long black, white, red, blue;

void init();
void close();
void draw();
void clear_screen();
unsigned long RGB(int r, int g, int b);
struct coord 
{
  int x, y;
  
} dot;


int main() 
{
  init();
  XEvent event;
  KeySym key;
  char text[255];

  while (1) 
  {
    XNextEvent(display, &event);
    if (event.type==Expose && event.xexpose.count==0) {
      draw();
    }

    if (event.type==KeyPress && XLookupString(&event.xkey, text, 255, &key, 0)==1) {
      if (text[0] == 'c') {
        clear_screen();
      }
      if (text[0] == 'q') {
        close();
      }
    } 
    if (event.type==ButtonPress) {
      int x = event.xbutton.x, y = event.xbutton.y;

      XSetForeground(display, gc, red);
      XDrawLine(display, window, gc, dot.x, dot.y, x, y);
      
      // XSetForeground(display, gc, white);
      // strcpy(text, " ");
      // XDrawString(display, window, gc, x, y, text, strlen(text));

      dot.x=x; dot.y=y;
    }
  }
  return 0;
}

void init() 
{
  dot.x=100; dot.y=100;

  display=XOpenDisplay((char *)0);
  screen=DefaultScreen(display);
  black=BlackPixel(display, screen);
  white=WhitePixel(display, screen);
  red=RGB(255,0,0);
  blue=RGB(0,0,255);

  int height = 300;
  int width = 300;
  
  const char * window_name = "x11";
  const char * window_icon_name = "icon";

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
}

void close() 
{
  XFreeGC(display, gc);
  XDestroyWindow(display, window);
  XCloseDisplay(display);
  exit(0);
}

void draw()
{
  XClearWindow(display, window);
}

void clear_screen() 
{
  XClearWindow(display, window);
  dot.x = 100; dot.y = 100;
}

unsigned long RGB(int r, int g, int b) 
{
  return b + (g<<8) + (r<<16);
}