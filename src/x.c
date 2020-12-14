#include "x.h"

void move_mouse(Display *display, int x, int y) {
    XTestFakeRelativeMotionEvent(display, x, y, 0);
    XFlush(display);
}

void set_mouse(Display *display, int x, int y) {
    XTestFakeMotionEvent(display, 0, x, y, 0);
    XFlush(display);
}

void do_btn(Display *display, int button) {
    XTestFakeButtonEvent(display, button, 1, 0);
    XFlush(display);
}

void undo_btn(Display *display, int button) {
    XTestFakeButtonEvent(display, button, 0, 0);
    XFlush(display);
}

int key_is_pressed(KeySym ks) {
    char keys_return[32];
    XQueryKeymap(display, keys_return);
    KeyCode kc2 = XKeysymToKeycode(display, ks);
    return !!(keys_return[kc2 >> 3] & (1 << (kc2 & 7)));
}
