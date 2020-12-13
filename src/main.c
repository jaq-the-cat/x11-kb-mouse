#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>
#include <unistd.h>
#include <stdio.h>

#define MOVE 10

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

void move_mouse(Display *display, int x, int y) {
    XTestFakeRelativeMotionEvent(display, x, y, 0);
    XFlush(display);
}

void set_mouse(Display *display, int x, int y) {
    XTestFakeMotionEvent(display, 0, x, y, 0);
    XFlush(display);
}

void do_control(Display *display) {
    XTestFakeKeyEvent(display, XK_Control_R, 1, 0);
    XTestFakeKeyEvent(display, XK_Control_R, 0, 0);
    XFlush(display);
}

void do_shift(Display *display) {
    XTestFakeKeyEvent(display, XK_Shift_R, 1, 0);
    XTestFakeKeyEvent(display, XK_Shift_R, 0, 0);
    XFlush(display);
}

void print_bits(char b) {
    for (int bit=0; bit<8; bit++) {
        printf("%i ", b & 0x01);
        b >>= 1;
    }
}

int main(){
    const char SHIFT = REVERSE_BITS(0x02); // 7
    const char UP = REVERSE_BITS(0x01); // 13
    const char CTRL = REVERSE_BITS(0x40); //13
    const char LEFT = REVERSE_BITS(0x40); // 14
    const char DOWN = REVERSE_BITS(0x08); // 14
    const char RIGHT = REVERSE_BITS(0x20); // 14

    Display *display = XOpenDisplay(NULL);
    char keys_return[32];

    while (1) {
        printf("\e[1;1H\e[2J");
        XQueryKeymap(display, keys_return);
        for (int i=0; i<32; i++) {
            print_bits(keys_return[i]);
            printf(" <- %d", i);
            printf("\n");
        }
        if ((keys_return[13] & UP) == UP)
            move_mouse(display, 0, -MOVE);
        if ((keys_return[14] & LEFT) == LEFT)
            move_mouse(display, -MOVE, 0);
        if ((keys_return[14] & DOWN) == DOWN)
            move_mouse(display, 0, MOVE);
        if ((keys_return[14] & RIGHT) == RIGHT)
            move_mouse(display, MOVE, 0);
        if ((keys_return[7] & SHIFT) == SHIFT)
            do_control(display);
        if ((keys_return[13] & CTRL) == CTRL)
            do_shift(display);
        printf("\n");
        usleep(10000);
    }
    return 0;
}

