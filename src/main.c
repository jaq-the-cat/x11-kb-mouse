#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>

#include <unistd.h>

#define MOVE 3
#define REVERSE_BITS(b) ({\
    char reverse_num = 0;\
    do {\
    unsigned int bit_num = 8;\
    char i, temp;\
    for (i = 0; i < bit_num; i++) {\
        temp = (b & (1 << i));\
        if (temp)\
            reverse_num |= (1 << ((bit_num - 1) - i));\
    }} while (0);\
    reverse_num;\
})

Display *display;

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

void print_bits(char b) {
    for (int bit=0; bit<8; bit++) {
        printf("%i ", b & 0x01);
        b >>= 1;
    }
}

void print_stuff(char keys_return[32]) {
    printf("\e[1;1H\e[2J"); // clear screen
    for (int i=0; i<32; i++) {
        print_bits(keys_return[i]);
        printf(" | %d\n", i);
    }
}

void control_c_handler(int s) {
    XCloseDisplay(display);
    exit(1);
}

int key_is_pressed(KeySym ks) {
    char keys_return[32];
    XQueryKeymap(display, keys_return);
    KeyCode kc2 = XKeysymToKeycode(display, ks);
    return !!(keys_return[kc2 >> 3] & (1 << (kc2 & 7)));
}

int main() {
    signal(SIGINT, control_c_handler);

    int left = 0;
    int right = 0;
    int was_scroll_up = 0;
    int was_scroll_down = 0;

    const int RIGHT_CLICK = XK_F;
    const int LEFT_CLICK = XK_C;
    const int SCROLL_UP = XK_C;
    const int SCROLL_DOWN = XK_F;

    display = XOpenDisplay(NULL);
    char keys_return[32];

    while (1) {
        XQueryKeymap(display, keys_return);
        if (key_is_pressed(XK_Up))
            move_mouse(display, 0, -MOVE);
        if (key_is_pressed(XK_Left))
            move_mouse(display, -MOVE, 0);
        if (key_is_pressed(XK_Down))
            move_mouse(display, 0, MOVE);
        if (key_is_pressed(XK_Right))
            move_mouse(display, MOVE, 0);

        /*if (key_is_pressed(SCROLL_UP)) {*/
            /*if (!was_scroll_up) {*/
                /*was_scroll_up = 1;*/
                /*do_btn(display, Button4);*/
            /*}*/
        /*} else {*/
            /*was_scroll_up = 0;*/
            /*undo_btn(display, Button4);*/
        /*}*/
        /*if (key_is_pressed(SCROLL_DOWN)) {*/
            /*if (!was_scroll_down) {*/
                /*was_scroll_down = 1;*/
                /*do_btn(display, Button5);*/
            /*}*/
        /*} else {*/
            /*was_scroll_down = 0;*/
            /*undo_btn(display, Button5);*/
        /*}*/

        if (key_is_pressed(LEFT_CLICK))
            left = 1;
        else
            left = 0;
        if (key_is_pressed(RIGHT_CLICK))
            right = 1;
        else
            right = 0;

        if (left)
            do_btn(display, Button1);
        else
            undo_btn(display, Button1);
        if (right)
            do_btn(display, Button3);
        else
            undo_btn(display, Button3);
        usleep(5000);
    }
    end:
    return 0;
}

