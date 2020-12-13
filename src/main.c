#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>

void move_mouse(Display *display, int x, int y) {
    XTestFakeRelativeMotionEvent(display, x, y, 0);
    XFlush(display);
}

void set_mouse(Display *display, int x, int y) {
    XTestFakeMotionEvent(display, 0, x, y, 0);
    XFlush(display);
}

void button_make(Display *display, unsigned int button) {
    XTestFakeButtonEvent(display, button, True, 0);
    XFlush(display);
}

void button_break(Display *display, unsigned int button) {
    XTestFakeButtonEvent(display, button, False, 0);
    XFlush(display);

}

int main(){
    Display *display = XOpenDisplay(NULL);
    move_mouse(display, 5, 5);
    button_make(display, 1);
    button_break(display, 1);
    return 0;
}

