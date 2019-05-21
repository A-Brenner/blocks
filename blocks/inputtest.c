// Defines a main() that demonstrates the functions defined in input.c
#include "project.h"

int main(void){
	


	
	pi_joystick_t* joystick = getJoystickDevice();
	
	pi_i2c_t* main_magnet = geti2cDevice();
	assign_magnet(main_magnet);
	printf("12c : %s\n", main_magnet->name);
	configureMag(main_magnet);
	


	int* p2end = get_end();
	printf("%d\n", *p2end);	

	while(!(*p2end)){
		pollJoystick(joystick,joy_endgame,1000);
	}

	printf("Out of first loop!\n");

	while(1){
		pollJoystick(joystick,joy_callback,1000);
	}

	

	freeJoystick(joystick);

	printf("x: %d, y: %d, z: %d\n", get_mag_x(), get_mag_y(), get_mag_z());

	return 0;
}




