// defines all functions which obtain and process input from Raspberry Pi Sense Hat. Joystick & Magnet

#include "project.h"

// GLOBAL VARIABLES (Only accessible by this file but to all functions within)
int joy_code; // "Global Variable" declared, used for holding joystick codes
pi_i2c_t* magnet;
int magnet_x;
int magnet_y;
int magnet_z;
int end;

// callback function for joystick, consumes code given from joystick
//  returns nothing, assigns corresponding code from joystick to global variable 'joy_code'
void joy_callback(unsigned int code){
// up : 105
// right : 103
// down : 106
// left : 108
// enter : 28
	printf("code: %u\n", code);
	if(code == 105){ // move up
		joy_code = code;
	} else if(code == 103){ // move right
		joy_code = code;
	} else if(code == 106){ // move down
		joy_code = code;
	} else if(code == 108){ // move left
		joy_code = code;
	} else if(code == 28){ // enter
		// MAGNET -> CHANGE COLORS
		joy_code = code;
		if(magnet){
			coordinate_t data;
			getMagData(magnet,&data);
			printf("%f, %f, %f\n", data.x, data.y, data.z);
			magnet_x = (int)data.x;
			magnet_y = (int)data.y;
			magnet_z = (int)data.z;
		} 
	}
}

// consumes code from joystick, returns nothing
// callback function for joystick 
// keeps screen frozen until user hits 'enter'
void joy_endgame(unsigned int code){
	if(code == 28){
		end = 1;
	}
}



// consumes nothing, returns "Global variable" 'joy_code'
int get_joy_code(){
	return joy_code;
}

//resets joy_code to 0
void reset_joy_code(){
	joy_code = 0;
}


// consumes a pointer to i2c device, returns nothing
// used to assign the global variable 'magnet' to the actual magnet which is configured in main
void assign_magnet(pi_i2c_t* main_magnet){
	magnet = main_magnet;
}



// MAGNET DATA GETTERS
// returns global variable 'magnet_x'
int get_mag_x(){
	return magnet_x;
}

// returns global variable 'magnet_y'
int get_mag_y(){
	return magnet_y;
}

// returns global varibale 'magnet_z'
int get_mag_z(){
	return magnet_z;
}

// MAGNET DATA SETTERS
// sets value for global variable 'magnet_x'
void set_mag_x(int x){
	magnet_x = x;
}

// sets value for global variable 'magnet_x'
void set_mag_y(int x){
	magnet_y = x;
}
// sets value for global variable 'magnet_x'
void set_mag_z(int x){
	magnet_z = x;
}

// returns the address of global variable end
int* get_end(){
	return &end;
}


// sets value for global variable 'end'
void set_end(int x){
	end = x;
}






