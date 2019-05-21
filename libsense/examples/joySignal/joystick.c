#include "sense.h"
#include <linux/input.h>
#include <stdio.h>
#include <signal.h>

int running=1;
void callbackFunc(unsigned int code) {
    printf("code: %u\t",code);
    if(code == KEY_UP) {
        printf("up");
    }else if(code == KEY_DOWN) {
        printf("down");
    }else if(code == KEY_RIGHT) {
        printf("right");
    }else if(code == KEY_LEFT) {
        printf("left");
    }else if(code == KEY_ENTER) {
        printf("enter");
    }
    printf("\n");
}

void signalHandler(int sig) {
    printf("Handling: %d\n",sig);
    running = 0;
}

int main(void) {
    signal(SIGINT,signalHandler);
    pi_joystick_t* joystick=getJoystickDevice();
    while(running){
        pollJoystick(joystick,callbackFunc,1000);
    }
    printf("Looks like 'running' is zero!\n");
    freeJoystick(joystick);
}

