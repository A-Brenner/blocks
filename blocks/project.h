// Contains prototypes for all functions (other than main()), structure definitions and included libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <linux/input.h>
#include "framebuffer.h"
#include "sense.h"




// struct of type Block
// x & y coordinates for LED array, char to identify which block
typedef struct{
	int x; // x coordinate on 8x8 LED grid
	int y; // y coordinate on 8x8 LED grid
	char id; // Help determine which block, should consist of 'L', 'R', 'T', 'B', 'U'
	// Left, Right, Top, Bottom, & User
} Block;



// **** input.c functions ****
int get_joy_code(); // returns global variable 'joy_code'
void reset_joy_code();
void joy_callback(unsigned int code); // assignes new value to 'joy_code'
void joy_endgame(unsigned int code); // officially ends the game
void assign_magnet(pi_i2c_t* main_magnet); // assigns magnet in input.c to magnet in main
int get_mag_x();
int get_mag_y();
int get_mag_z();
void set_mag_x(int x);
void set_mag_y(int x);
void set_mag_z(int x);
int* get_end();
void set_end(int x);


// **** output.c functions ****

// consumes a char 'block_id' to identify which block is being produced
// returns a pointer to a Block
// depending on input, Block will get attributes x & y which correspond to the side of the LED array it will be placed on
// EX: input of 'L' will produce a block with x: 0, y: (rand()%8) and will be located somewhere on the Left wall of the LED array
Block* spawn_block(char block_id);


// used for main.c
void updateMap(pi_framebuffer_t *fb, Block *bL, Block *bR, Block *bT, Block *bB, Block *user);

// used for outputtest.c 
void update_map(pi_framebuffer_t *fb, Block *bL, Block *bR, Block *bT, Block *bB, Block *user);

// consumes a pointer to Block, returns nothing 
// increases posn of block by one in the corresponding direction
void fall(Block *b);

void go_dark(pi_framebuffer_t *fb, Block *bL, Block *bR, Block *bT, Block *bB);
void user_dead(pi_framebuffer_t *fb, Block *user);

// consumes all computer blocks and the user Block, returns an integer
// return 1 if user has been hit -> GAMEOVER ....  return 0 if user is safe -> Game ongoing still
// compares the x & y coordinates of each block to the user posn
int is_user_hit(Block *bL, Block *bR, Block *bT, Block *bB, Block *user);
void update_block_color(int x, int y, int z);
void update_user_posn(Block *user, unsigned int code);
void dark_user(pi_framebuffer_t *fb, Block *user);
void set_user_color(int x, int y, int z);
void set_block_color(int x, int y, int z);
void set_red_color(int x, int y, int z);
void set_dark_color(int x, int y, int z);







