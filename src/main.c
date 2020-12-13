#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <unistd.h>
#include <stdio.h>

#define MOVE 5

void move_mouse(Display *display, int x, int y) {
    XTestFakeRelativeMotionEvent(display, x, y, 0);
    XFlush(display);
}

void set_mouse(Display *display, int x, int y) {
    XTestFakeMotionEvent(display, 0, x, y, 0);
    XFlush(display);
}

void print_bits(char b) {
    for (int bit=0; bit<8; bit++) {
        printf("%i ", b & 0x01);
        b >>= 1;
    }
}

int main(){
    Display *display = XOpenDisplay(NULL);
    char keys_return[32];
    while (1) {
        printf("\e[1;1H\e[2J");
        XQueryKeymap(display, keys_return);
        for (int i=0; i<32; i++) {
            print_bits(keys_return[i]);
            printf("\n");
        }
        usleep(10000);
    }
    return 0;
}

