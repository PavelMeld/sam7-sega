#ifndef __JOYPAD_H
#define __JOYPAD_H

typedef union gamepad_u {
	unsigned int data;
	struct {
		unsigned int up:1;
		unsigned int down:1;
		unsigned int left:1;
		unsigned int right:1;
		unsigned int a:1;
		unsigned int b:1;
		unsigned int c:1;
		unsigned int x:1;
		unsigned int y:1;
		unsigned int z:1;
		unsigned int start:1;
		unsigned int md:1;
	};
} gamepad_t;

gamepad_t readSixPad();
void select_low();
void select_high();


#endif
