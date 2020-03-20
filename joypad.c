#include "board.h"
#include "timerisr.h"
#include "joypad.h"

#define IS_SET(A) (A) ? 1 : 0;

unsigned int loops_per_ms;

void select_low() {
	AT91C_BASE_PIOA->PIO_CODR = DB9_7_SELECT;
}

void select_high() {
	AT91C_BASE_PIOA->PIO_SODR = DB9_7_SELECT;
}

unsigned int readPio() {
	return AT91C_BASE_PIOA->PIO_PDSR;
}

void initSixPad() {
	unsigned long long start_ticks = tickcount;
	unsigned int k = 0, max = 0;

	while (tickcount == start_ticks);

	start_ticks = tickcount;
	while (tickcount == start_ticks)
		max++;

	start_ticks = tickcount;
	for (k=0;k<10 * max;k++);
	loops_per_ms = (10 * max) / (tickcount - start_ticks);

	// Calibrate delay
	select_high();
	mdelay(1000);
}

void usleep(unsigned int us) {
	int k;
	for (k=0;k<loops_per_ms * us / 1000;k++);
}

gamepad_t readSixPad() {
	gamepad_t		pad;
	unsigned int	pio;

	pad.data = 0;

	// 0 Low   UP DW LO LO (A  ST)
	select_low();
	usleep(2);

	pio			= readPio();
	pad.a		= IS_SET(pio & DB9_6_AB);
	pad.start	= IS_SET(pio & DB9_9_START_C);

	// 1 High  UP DW LF RG B  C
	usleep(2);
	select_high();
	usleep(2);
	pio			= readPio();
	pad.up		= IS_SET(pio & DB9_1_UP_Z);

	// 2 Low   UP DW LO LO A  ST	- Skip
	usleep(2);
	select_low();
	usleep(2);

 	// 3 High  UP DW LF RG B  C 
	usleep(2);
	select_high();
	usleep(2);

	pio			= readPio();
	pad.down	= IS_SET(pio & DB9_2_DOWN_Y);
	pad.left	= IS_SET(pio & DB9_3_LEFT_X);
	pad.right	= IS_SET(pio & DB9_4_RIGHT_MD);
	pad.b		= IS_SET(pio & DB9_6_AB);
	pad.c		= IS_SET(pio & DB9_9_START_C);
	
 	// 4  Low   LO LO LO LO A  ST  - Skip
	usleep(2);
	select_low();
	usleep(2);
	
 	// 5  High  Z  Y  X  MD HI HI  # Make Sel High and read D0 - D3.
	usleep(2);
	select_high();
	usleep(2);

	pio			= readPio();
	pad.z		= IS_SET(pio & DB9_1_UP_Z);
	pad.y		= IS_SET(pio & DB9_2_DOWN_Y);
	pad.x		= IS_SET(pio & DB9_3_LEFT_X);
	pad.md		= IS_SET(pio & DB9_4_RIGHT_MD);

 	// 6  Low   HI HI HI HI A  ST  - Skip
	usleep(2);
	select_low();
	usleep(2);
	
 	// 7  High  UP DW LF RG B  C   - Skip
	select_high();
	mdelay(2);

	pad.data = ~pad.data;

	return pad;
}
