#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>

extern Display *display;

void move_mouse(Display*, int, int);
void set_mouse(Display*, int, int);
void do_btn(Display*, int);
void undo_btn(Display*, int);
int key_is_pressed(KeySym, char[32]);
