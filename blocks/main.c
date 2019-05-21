// main.c
// May not (directly) perform any I/O, though it mau use printf for debugging
#include "project.h"

int main(void){

	// CONFIGURE SENSE HAT
	pi_framebuffer_t* fb = getFBDevice(); // connect to LED array
	pi_joystick_t* joystick = getJoystickDevice();	// connect to joystick
	pi_i2c_t* main_magnet = geti2cDevice();
	assign_magnet(main_magnet); // assign global variable 'magnet' to i2c device
	configureMag(main_magnet);

	// SET DEFAULT COLORS
	set_user_color(14,122,200);
	set_block_color(95,25,65);
	set_red_color(255,0,0);
	set_dark_color(0,0,0);
	
	// SET DEFAULT MAGNET DATA VALUES
	set_mag_x(5);
	set_mag_y(13);
	set_mag_z(41);	
	update_block_color(get_mag_x(), get_mag_y(), get_mag_z());
	
	// SPAWN BLOCKS ON LED ARRAY
	Block *bL = spawn_block('L');
	Block *bR = spawn_block('R');
	Block *bT = spawn_block('T');
	Block *bB = spawn_block('B');
	Block *user = spawn_block('U');

	int running = 1; // is running
	int LED = 0; // counts where blocks are on LED array
	int hit = 0; // user is hit
	int* p2end = get_end(); // used for when game is over, user must hit enter to clear the screen and end program
	while(running){
		pollJoystick(joystick, joy_callback, 100);
		update_user_posn(user, get_joy_code()); // move user
		reset_joy_code();
		update_block_color(get_mag_x(), get_mag_y(), get_mag_z()); // update color
		updateMap(fb, bL, bR, bT, bB, user); // place block into updated posns
		LED++;
		if(LED >= 7){ // blocks have reached the end of LED array
			go_dark(fb, bL, bR, bT, bB); // erase current posns from LED array
			// spawn new blocks at beginning of each side
			bL = spawn_block('L');
			bR = spawn_block('R');
			bT = spawn_block('T');
			bB = spawn_block('B');	
			LED = 0;
		}
		
		hit = is_user_hit(bL, bR, bT, bB, user); // hit will be 1 if user has been hit
		if(hit){
			user_dead(fb, user);
			break; // user has been hit :(
		}
	}

	
	while(!(*p2end)){
		pollJoystick(joystick,joy_endgame,1000);
	}

	freeJoystick(joystick);

	// TESTING PURPOSES ********8**********
	/*char c;
	printf("press enter to continue.\n");
	scanf("%c", &c);
	*/


	clearBitmap(fb->bitmap, 0);	



	return 0;

}

