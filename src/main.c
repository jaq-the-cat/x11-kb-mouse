#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <unistd.h>

#define MOVE 5

void move_mouse(Display *display, int x, int y) {
    XTestFakeRelativeMotionEvent(display, x, y, 0);
    XFlush(display);
}

void set_mouse(Display *display, int x, int y) {
    XTestFakeMotionEvent(display, 0, x, y, 0);
    XFlush(display);
}

int main(){
    Display *display = XOpenDisplay(NULL);
    for (int i=0; i<MOVE; i++) {
        move_mouse(display, i, 0);
        usleep(15000);
    }
    return 0;
}

