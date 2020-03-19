#include "board.h"
#include "timerisr.h"
#include "joypad.h"


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
	select_high();
	msleep(1000);
}


gamepad_t readSixPad() {
	gamepad_t		pad;
	unsigned int	pio;


	select_low();
	msleep(10);

	pio			= readPio();
	pad.a		= pio & DB9_6_AB;
	pad.start	= pio & DB9_9_START_C;

	select_high();
	msleep(10);

	pad.up		= pio & DB9_1_UP_Z;
	pad.down	= pio & DB9_2_DOWN_Y;
	pad.left	= pio & DB9_3_LEFT_X;
	pad.right	= pio & DB9_4_RIGHT;
	pad.b		= pio & DB9_6_AB;
	pad.c		= pio & DB9_9_START_C;

	select_low();
	msleep(10);

	pad.up		= pio & DB9_1_UP_Z;
	pad.down	= pio & DB9_2_DOWN_Y;
	pad.left	= pio & DB9_3_LEFT_X;

	select_high();
	msleep(10);

	return pad;
}
