#include "sense.h"
#include <stdio.h>
#include <unistd.h>

int run=1;
void zero(unsigned int code) { run=!run; printf("no\n"); }
void one(unsigned int code) { run=!run; printf("yes\n"); }

int main(void) {
    printf("starting\n");
    pi_joystick_t* joystick=getJoystickDevice();
    printf("got joystick,starting first loop\n");
    int count = 0;
    while(run){
        count++;
        pollJoystick(joystick,one,1000);
        printf("first loop %d\n",count);
        printf("sleeping\n");
        sleep(5);
        printf("not sleeping\n");
    }
    printf("Count: %d\n",count);
    count=0;
    while(!run){ count++;  pollJoystick(joystick,zero,100); printf("second loop %d\n",count);}
    printf("done\n");
    freeJoystick(joystick);
}
