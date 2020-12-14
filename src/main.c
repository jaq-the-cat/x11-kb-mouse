#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include "x.h"

#include <unistd.h>

#define POINTER_SPEED 3

Display *display;

void control_c_handler(int s) {
    XCloseDisplay(display);
    exit(1);
}

int main() {
    signal(SIGINT, control_c_handler);

    int left = 0;
    int right = 0;
    /*int was_scroll_up = 0;*/
    /*int was_scroll_down = 0;*/

    const int LEFT_CLICK = XK_KP_7;
    const int RIGHT_CLICK = XK_KP_9;
    /*const int SCROLL_UP = XK_C;*/
    /*const int SCROLL_DOWN = XK_F;*/

    display = XOpenDisplay(NULL);
    char keys_return[32];

    while (1) {
        XQueryKeymap(display, keys_return);
        if (key_is_pressed(XK_KP_8))
            move_mouse(display, 0, -POINTER_SPEED);
        if (key_is_pressed(XK_KP_4))
            move_mouse(display, -POINTER_SPEED, 0);
        if (key_is_pressed(XK_KP_5))
            move_mouse(display, 0, POINTER_SPEED);
        if (key_is_pressed(XK_KP_6))
            move_mouse(display, POINTER_SPEED, 0);

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

