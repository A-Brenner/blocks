// Defines all functions that output to the LED array
#include "project.h"


// GLOBAL VARIABLES (only accessible within file, available to all functions within)
uint16_t BLOCK_COLOR;// = getColor(95,25,65); // pink / purple
uint16_t USER_COLOR; // = getColor(14,122,200); // pretty blue :)
uint16_t RED_COLOR; // = getColor(255,0,0); // used for when user is hit
uint16_t DARK_COLOR; // = getColor(0,0,0); // used to erase previous posn from LED array

int user_x_prev;
int user_y_prev;





Block* spawn_block(char block_id){
	pi_framebuffer_t *fb=getFBDevice();
	srand(time(NULL)); // seed rand() with time
	if(block_id == 'L'){ // Block on Left wall
		Block *bL = malloc(sizeof(Block));
		bL->x = 0; // left wall
		bL->y = (abs((rand()*2))%8); // random posn on left wall
		bL->id = 'L';
		fb->bitmap->pixel[bL->x][bL->y] = BLOCK_COLOR;
		return bL;
	}else if(block_id == 'R'){ // Block on Right wall
		Block *bR = malloc(sizeof(Block));	
		bR->x = 7; // right wall
		bR->y = (abs((rand()*3))%8); // random posn on right wall
		bR->id = 'R';
		fb->bitmap->pixel[bR->x][bR->y] = BLOCK_COLOR;
		return bR;
	}else if(block_id == 'T'){ // Block on Top wall
		Block *bT = malloc(sizeof(Block));
		bT->x = (abs((rand()*5))%8); //random posn on top wall
		bT->y = 0; // top wall 
		bT->id = 'T';
		fb->bitmap->pixel[bT->x][bT->y] = BLOCK_COLOR;
		return bT;
	}else if(block_id == 'B'){ // Block on Bottom wall
		Block *bB = malloc(sizeof(Block));
		bB->x = (abs((rand()*7))%8); // random posn on bottom wall
		bB->y = 7; // bottom wall
		bB->id = 'B';
		fb->bitmap->pixel[bB->x][bB->y] = BLOCK_COLOR;
		return bB;
	}else if(block_id == 'U'){ // creates user Block, places in center
		Block *user = malloc(sizeof(Block));
		user->x = 4; // ~center
		user->y = 4; // ~center
		user->id = 'U';
		fb->bitmap->pixel[user->x][user->y] = USER_COLOR;
		return user;
	}else{  // block_id did not match any conditions
		return NULL;
	}
}

// Consumes a pointer to Block, returns nothing
// changes property of given block, increases either x or y posn by one depending on direction of movement needed(b->id)
void fall(Block *b){
	if(b->id == 'L'){
		b->x = ((b->x + 1) % 8); // safety precaution
	} else if (b->id == 'R'){
		b->x = abs((b->x - 1) % 8);
	} else if(b->id == 'T'){
		b->y = ((b->y + 1) % 8);
	} else if(b->id == 'B'){
		b->y = abs((b->y - 1) % 8);
	}
}


// used for main.c
// consumes framebuffer for LED acces and all blocks on LED, returns nothing
// updates the LED array with the corresponding x & y posns of each block
void updateMap(pi_framebuffer_t *fb, Block *bL, Block *bR, Block *bT, Block *bB, Block *user){
	
	usleep(200000); // sleep for 0.5 seconds (microseconds)
	fb->bitmap->pixel[user_x_prev][user_y_prev] = DARK_COLOR;
	go_dark(fb, bL, bR, bT, bB); // makes current posns go away on LED array
	fall(bL);
	fall(bR);
	fall(bT);
	fall(bB);
	fb->bitmap->pixel[user->x][user->y] = USER_COLOR;
	fb->bitmap->pixel[bL->x][bL->y] = BLOCK_COLOR;
	fb->bitmap->pixel[bR->x][bR->y] = BLOCK_COLOR;
	fb->bitmap->pixel[bT->x][bT->y] = BLOCK_COLOR;
	fb->bitmap->pixel[bB->x][bB->y] = BLOCK_COLOR;

}

// used for outputtest.c
// consumes framebuffer for LED access, and all blocks on LED, returns nothing
// updates the LED array with he corresponding x & y posns of each block 
void update_map(pi_framebuffer_t *fb, Block *bL, Block *bR, Block *bT, Block *bB, Block *user){
	int hit = 0;
	while(!(hit)){
		for(int i = 0; i < 7; i++){
			usleep(800000); // sleep for 0.2 seconds (microseconds))
			
			go_dark(fb, bL, bR, bT, bB); // makes current posns go away on LED array
			fall(bL); // increas posn by one
			fall(bR);
			fall(bT);
			fall(bB);
			fb->bitmap->pixel[user->x][user->y] = USER_COLOR;
			fb->bitmap->pixel[bL->x][bL->y] = BLOCK_COLOR; // paint on map
			fb->bitmap->pixel[bR->x][bR->y] = BLOCK_COLOR;
			fb->bitmap->pixel[bT->x][bT->y] = BLOCK_COLOR;
			fb->bitmap->pixel[bB->x][bB->y] = BLOCK_COLOR;
			hit = is_user_hit(bL,bR,bT,bB,user);
			if(hit){
				break; // user has been hit, GAMEOVER	
			}
		}
		if(hit){
			break; // user has been hit, GAMEOVER
		}
		
		go_dark(fb, bL, bR, bT, bB); // makes currents posns go away from LED array

		bL = spawn_block('L');
		bR = spawn_block('R');
		bT = spawn_block('T');
		bB = spawn_block('B');
	}

	if(hit){
		user_dead(fb, user);
	}
}

// consumes fb for access to LED array, and enemy blocks, returns nothing
// makes current posns of blocks "dark" on LED array
void go_dark(pi_framebuffer_t *fb, Block *bL, Block *bR, Block *bT, Block *bB){
	fb->bitmap->pixel[bL->x][bL->y] = DARK_COLOR;
	fb->bitmap->pixel[bR->x][bR->y] = DARK_COLOR;
	fb->bitmap->pixel[bT->x][bT->y] = DARK_COLOR;
	fb->bitmap->pixel[bB->x][bB->y] = DARK_COLOR;
}

// consumes fb for LED access, and Block user, returns nothing
// paints the users posns red since user has been hit
void user_dead(pi_framebuffer_t *fb, Block *user){
	fb->bitmap->pixel[user->x][user->y] = RED_COLOR;
}

// consumes all blocks on map, returns integer of 1 or 0
// compares posns of each enemy block to user, if they are in the same posn, return 1 : user is hit
// if user has a unique posn, return 0 : user is NOT hit
int is_user_hit(Block *bL, Block *bR, Block *bT, Block *bB, Block *user){

	if((bL->x == user->x && bL->y == user->y) || (bR->x == user->x && bR->y == user->y) || (bT->x == user->x && bT->y == user->y) || (bB->x == user->x && bB->y == user->y)){
		return 1; // user is hit by a block
	}else{
		return 0; // user is untouched
	}
}


// consumes 3 integers, returns nothing
// changes the color of BLOCK_COLOR using given values
void update_block_color(int x, int y, int z){
	x = (abs(x * 25) % 255);
	y = (abs(y * 25) % 255);
	z = (abs(z * 25) % 255);
	BLOCK_COLOR = getColor(x,y,z); 
}
	
// up : 105
// // right : 103
// // left : 108
// // down : 106
// // enter : 28
// consumes an unsigned integer representing the outputted joystick code, returns nothing
// moves user in corresponding direction by 1
void update_user_posn(Block *user, unsigned int code){
	user_x_prev = user->x;
	user_y_prev = user->y;
	if(code == 105){ // user moves up
		if(user->y <= 0){ // user on top edge
			user->y = 7; // jump to bottom
		}else{
			user->y = (abs(user->y - 1) % 8); // move up by 1
		}
	}else if(code == 103){ // user moves right
		if(user->x <= 0){ // user is on right edge
			user->x = 7; //jump to left side
		}else{
			user->x = ((user->x - 1) % 8); // move right by 1
		}
	} else if(code == 108){ // user moves left
		if(user->x >= 7){ // user is on left edge
			user->x = 0; // jump to right side
		}else{
			user->x = (abs(user->x + 1) % 8); // move left by 1
		}
	}else if(code == 106){ // user moves down
		if(user->y >= 7){ // user is on bottom edge
			user->y = 0; // jump to top side
		}else{
			user->y = ((user->y + 1) % 8); // user moves down by one
		}
	}
}

/*
// consumes fb for access to LED array, and Block user , returns nothing
// erases previous posn of user from LED array
void dark_user(pi_framebuffer_t *fb, Block *user){
	fb->bitmap->pixel[user->x][user->y] = DARK_COLOR;
}
*/

// consumes 3 integers, returns nothing
// sets global variable 'USER_COLOR' 
void set_user_color(int x, int y, int z){
	USER_COLOR = getColor(x,y,z);
}

// consumes 3 integers, return nothing
// // sets global variable 'BLOCK_COLOR'
void set_block_color(int x,int y,int z){
	BLOCK_COLOR = getColor(x,y,z);
}

// consumes 3 integers, returns nothing
// sets global variable 'USER_COLOR' 
 void set_dark_color(int x, int y, int z){
 	DARK_COLOR = getColor(x,y,z);
 }

// consumes 3 integers, return nothing
 // sets global variable 'BLOCK_COLOR'
 void set_red_color(int x,int y,int z){
 	RED_COLOR = getColor(x,y,z);
 }





