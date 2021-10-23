#include <X11/Xlib.h>

void draw(Display *display, Window window)
{
  XClearWindow(display, window);
}
