#include "sense.h"
#include <linux/input.h>
#include <stdio.h>

int running=1;
pi_i2c_t* magnet=NULL;

void callbackFunc(unsigned int code) {
    if(code == KEY_ENTER) {
        running=0;
    } else if(magnet) {
        coordinate_t data;
        getMagData(magnet,&data);
        printf("%f %f %f\n",data.x,data.y,data.z);
    }
}

int main(void) {
    pi_joystick_t* joystick=getJoystickDevice();
    magnet=geti2cDevice();
    printf("i2c: %s\n",magnet->name);
    configureMag(magnet);
    while(running){
        pollJoystick(joystick,callbackFunc,1000);
    }
    freeJoystick(joystick);
}

