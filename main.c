//  *****************************************************************************
//   						main.c
// 
//     Demonstration program for Atmel AT91SAM7S256-EK Evaluation Board
//
//     blinks LED0 (pin PA0) with an endless loop
//     blinks LED1 (pin PA1) using timer0 interrupt (200 msec rate)
//	   switch SW1 (PA19) triggers FIQ interrupt, turns on LED2 (Pin PA2)
//     plenty of variables for debugger practice
//
//  Author:  James P Lynch  May 12, 2007
//  *****************************************************************************
 
//  *******************************************************
//                Header Files
//  *******************************************************
#include "AT91SAM7S256.h"
#include "board.h"
#include "math.h"
#include "stdlib.h"
#include "string.h"
#include "usb.h"
#include "timerisr.h"
#include "joypad.h"

//  *******************************************************
//                Function Prototypes
//  *******************************************************
void Timer0IrqHandler(void);
void FiqHandler(void);

//  *******************************************************
//                External References
//  *******************************************************
extern	void LowLevelInit(void);
extern	void TimerSetup(void);
extern	unsigned enableIRQ(void);
extern	unsigned enableFIQ(void);

//  *******************************************************
//               Global Variables
//  *******************************************************
unsigned int	FiqCount = 0;		// global uninitialized variable		


void setup() {
	// Set up the LEDs (PA0 - PA3)
	volatile AT91PS_PIO	pPIO = AT91C_BASE_PIOA;			// pointer to PIO data structure
	pPIO->PIO_PER = (PA_INPUTS|PA_OUTPUTS);
	pPIO->PIO_OER = PA_OUTPUTS;							// PIO Output Enable Register - sets pins P0 - P3 to outputs
	pPIO->PIO_OWER = PA_OUTPUTS;
	pPIO->PIO_MDER = PA_OUTPUTS;
	pPIO->PIO_IDR = 0xFFFFFFFF;							// Disable interrupts for all pins
	pPIO->PIO_IFDR = 0xFFFFFFFF;						// Disable glitch filtering on all inputs

	LowLevelInit();

	// Setup timer0 to generate a 10 msec periodic interrupt
	TimerSetup();

	// Set up the AIC  registers for Timer 0  
	volatile AT91PS_AIC	pAIC = AT91C_BASE_AIC;			// pointer to AIC data structure
	pAIC->AIC_IDCR = (1<<AT91C_ID_TC0);					// Disable timer 0 interrupt in AIC Interrupt Disable Command Register			
	pAIC->AIC_SVR[AT91C_ID_TC0] =						// Set the TC0 IRQ handler address in AIC Source 
    	(unsigned int)Timer0IrqHandler;        			// Vector Register[12]
	pAIC->AIC_SMR[AT91C_ID_TC0] =						// Set the interrupt source type and priority 
   		(AT91C_AIC_SRCTYPE_INT_HIGH_LEVEL | 0x4 ); 		// in AIC Source Mode Register[12]
	pAIC->AIC_ICCR = (1<<AT91C_ID_TC0); 				// Clear the TC0 interrupt in AIC Interrupt Clear Command Register
	pAIC->AIC_IDCR = (0<<AT91C_ID_TC0);					// Remove disable timer 0 interrupt in AIC Interrupt Disable Command Reg			
	pAIC->AIC_IECR = (1<<AT91C_ID_TC0); 				// Enable the TC0 interrupt in AIC Interrupt Enable Command Register
	

	// enable the Timer0 peripheral clock
	volatile AT91PS_PMC	pPMC = AT91C_BASE_PMC;				// pointer to PMC data structure
	pPMC->PMC_PCER = (1<<AT91C_ID_TC0)|(1<<AT91C_ID_PIOA);	// enable Timer0 peripheral clock


	// enable interrupts
	enableIRQ();
	enableFIQ();

	timerStart();
}


int	main (void) {
	gamepad_t	pad, next_pad;

	setup();
	usb_start();
	initSixPad();

	pad = readSixPad();
	while (1) {
		usb_send(0);
		mdelay(1000);
		usb_send(0xab);
		mdelay(1000);
	}

	while (1) {
		unsigned char up_down;
		unsigned char left_right;
		unsigned char a, b, c, start;

		mdelay(10);

		next_pad = readSixPad();
		if (memcmp(&next_pad, &pad, sizeof(pad)) == 0)
			continue;

		if (next_pad.up)
			AT91C_BASE_PIOA->PIO_SODR = LED_MASK;							// PIO Set Output Data Register - turns off the four LEDs
		else
			AT91C_BASE_PIOA->PIO_CODR = LED_MASK;							// PIO Set Output Data Register - turns off the four LEDs

		up_down = 0;
		left_right = 0;
		a = 0;
		b = 0;
		c = 0;
		start = 0;

		if (next_pad.up)
			up_down = W_SCAN_CODE;
		if (next_pad.down)
			up_down = S_SCAN_CODE;
		if (next_pad.left)
			left_right = A_SCAN_CODE;
		if (next_pad.right)
			left_right = D_SCAN_CODE;
		if (next_pad.a)
			a = Z_SCAN_CODE;
		if (next_pad.b)
			b = X_SCAN_CODE;
		if (next_pad.c)
			c = C_SCAN_CODE;
		if (next_pad.start)
			start = ENTER_SCAN_CODE;

		usb_send_joypad(up_down, left_right, a, b, c, start);

		memcpy(&pad, &next_pad, sizeof(pad));
	}

}

