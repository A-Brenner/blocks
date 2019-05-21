// defines a main() that demonstrates how the display should work using the functons defined in output.c
#include "project.h"

int main(void){

	set_user_color(14,122,200);
	set_block_color(95,25,65);
	set_red_color(255,0,0);
	set_dark_color(0,0,0);

	Block *bL = spawn_block('L');
	Block *bR = spawn_block('R');
	Block *bT = spawn_block('T');
	Block *bB = spawn_block('B');
	Block *user = spawn_block('U');
	

	pi_framebuffer_t *fb=getFBDevice();
	update_map(fb, bL, bR, bT, bB, user);


		 printf("Hit enter to continue.");
		char garbage; // Just used so the scanf has something to chew on

		scanf("%c",&garbage);
		clearBitmap(fb->bitmap,0);

		

		return 0;
}
