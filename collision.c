#include <stdio.h>
#include <gb/gb.h>
#include "tiles.c"
#include "dungeon.c"
#include "sprites.c"
#include <rand.h>	
#include <gb/console.h>
#include <gb/drawing.h>
#include <time.h>

void init();
void checkInput();


UINT8 player[2];
UINT8 enemy[2], enemy2[2];
UINT8 i, x, flag1, flag2, flag3, f=0, current=2;
UINT8 enemy3[0], sfx=0;
int a;

void main() {

	
	printf(" \n");
	printf("  -MOVEMENT TEST-\n");
	printf("       -AND-\n");
	printf("  -COLLISION TEST-\n\n\n\n");
	printf("   <PRESS START>\n\n\n 2017\n\n Mateusz Zabczyk\n");
	waitpad(J_START);
	
	begin:
	init();
	
	
	while((flag1!=1) || (flag2!=1) || (flag3!=1)){
	
		
		checkInput();
		wait_vbl_done();	
		
		
	}
	
		HIDE_SPRITES;
		//HIDE_BKG;
		printf("     SUCCESS!!!!   ");
		printf("     <PRESS_START>   ");
		waitpad(J_START);
		SHOW_BKG;
		SHOW_SPRITES;
		flag1=0; flag2=0; flag3=0;
		goto begin;
		
}

void init() {
	
	DISPLAY_ON;			// Turn on the display
	NR52_REG = 0x8F;	// Turn on the sound
	NR51_REG = 0x11;	// Enable the sound channels
	NR50_REG = 0x77;	// Increase the volume to its max
	
	SHOW_SPRITES;
	SHOW_BKG;
	HIDE_WIN;
	
	
	set_bkg_data(0, 23, tiles);
	set_bkg_tiles(0,0,20,18, dungeon);
	set_sprite_data(0, 6, sprites);
	set_sprite_tile(0,2);
	set_sprite_tile(1,5);
	set_sprite_tile(2,5);
	set_sprite_tile(3,5);
	
	player[0] = 24;
	player[1] = 32;
	
	enemy[0] = 144;
	enemy[1] = 136;
	
	enemy2[0] = 100;
	enemy2[1] = 50;
	
	enemy3[0] = 50;
	enemy3[1] = 100;
	 
	

}

UINT8 collisionCheck(UINT8 x1, UINT8 y1, UINT8 w1, UINT8 h1, UINT8 x2, UINT8 y2, UINT8 w2, UINT8 h2) {

	if ((x1 < (x2+w2)) && ((x1+w1) > x2) && (y1 < (h2+y2)) && ((y1+h1) > y2)) {
		
		return 1;
	
	} else {
		
		return 0;
	
	}

}


void checkInput() {

    if (joypad() & J_B) {
		set_sprite_tile(0,3);
    }

	if (joypad() & J_A) {
		set_sprite_tile(0,2);
		
    }
	
	if (joypad() & J_UP) {
		player[1]--;
	
	}
			
	
	if (joypad() & J_DOWN) {
		player[1]++;
    }
	
	if (joypad() & J_LEFT) {
		player[0]--;
    }
	
	if (joypad() & J_RIGHT) {
		player[0]++;
    }
	
	if (joypad() & J_START) {
    }
	
	if (joypad() & J_SELECT) {
		
	}
	

	//player collision with walls
	if (player[0] < 24){player[0]=24;}
	if (player[0] > 144){player[0]=144;}
	if (player[1] < 32){player[1]=32;}
	if (player[1] > 136){player[1]=136;}
	
	move_sprite(0, player[0], player[1]);
	
	//enemy movement
	if(enemy2[0]<24){enemy2[0]=100;}
	
	
	//set enemy flag
	if(enemy[0]==24){f=1;}
	if(enemy[0]==144){f=0;}
	
	//patrol move pattern -faster to tight
	if(f==0){
		move_sprite(1, enemy[0]--, enemy[1]);
	}else{
	move_sprite(1, enemy[0]=enemy[0]+5, enemy[1]);}
	
	move_sprite(2, enemy2[0]--, enemy2[1]);
	move_sprite(3, enemy3[0], enemy3[1]);
	
	
	
	
	
	
	//colision with enemy
	if(collisionCheck(player[0], player[1], 8, 8, enemy[0], enemy[1], 8, 8) == 1) {
		set_sprite_tile(1,3);
		flag1=1;
		NR52_REG = 0x80;
		NR51_REG = 0x11;
NR50_REG = 0x77;

NR10_REG = 0x1E;
NR11_REG = 0x10;
NR12_REG = 0xF3;
NR13_REG = 0x00;
NR14_REG = 0x87;
	} 
	
	//colision with enemy
	if(collisionCheck(player[0], player[1], 8, 8, enemy2[0], enemy2[1], 8, 8) == 1) {
		set_sprite_tile(2,3);
		flag3=1;
		NR52_REG = 0x80;
		NR51_REG = 0x11;
NR50_REG = 0x77;

NR10_REG = 0x1E;
NR11_REG = 0x10;
NR12_REG = 0xF3;
NR13_REG = 0x00;
NR14_REG = 0x87;
	} 
	
	//colision with enemy
	if(collisionCheck(player[0], player[1], 8, 8, enemy3[0], enemy3[1], 8, 8) == 1) {
		set_sprite_tile(3,3);
		flag2=1;
		NR52_REG = 0x80;
		NR51_REG = 0x11;
NR50_REG = 0x77;

NR10_REG = 0x1E;
NR11_REG = 0x10;
NR12_REG = 0xF3;
NR13_REG = 0x00;
NR14_REG = 0x87;
	} 
	
	
	
	
}



