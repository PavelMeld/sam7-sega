//*--------------------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*--------------------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*--------------------------------------------------------------------------------------
//* File Name           : USB HID example
//* Object              :
//* Translator          :
//* 1.0 05/Oct/04 ODi	: CReation
//* 1.1 04/Nov/04 JPP	: Add led1 On at power supply
//*--------------------------------------------------------------------------------------

#include "board.h"
#include "hid_enumerate.h"

unsigned long i = 0;

struct _AT91S_HID 	HID;
extern volatile unsigned long	time;



//it's a simple delay
void Delay (unsigned long a) { while (--a!=0); }

//*----------------------------------------------------------------------------
//* \fn    AT91F_USB_Open
//* \brief This function Open the USB device
//*----------------------------------------------------------------------------
void AT91F_USB_Open(void)
{
    // Set the PLL USB Divider
    AT91C_BASE_CKGR->CKGR_PLLR |= AT91C_CKGR_USBDIV_1 ;

    // Specific Chip USB Initialisation
    // Enables the 48MHz USB clock UDPCK and System Peripheral USB Clock
    AT91C_BASE_PMC->PMC_SCER = AT91C_PMC_UDP;
    AT91C_BASE_PMC->PMC_PCER = (1 << AT91C_ID_UDP);


    // CDC Open by structure initialization
    AT91F_HID_Open(&HID, AT91C_BASE_UDP);
}

//*--------------------------------------------------------------------------------------
//* Function Name       : main
//* Object              :
//*--------------------------------------------------------------------------------------
int usb_start ( void )
{
	int x = 0, y = 0;
	unsigned long time_start;
 
     //AT91PS_SYSC pSysc=AT91C_BASE_SYSC;
     // pSysc->SYSC_RSTC_RMR |= 0xA5000001;// enable user reset 

    // Init USB device
    AT91F_USB_Open();

  
    // Wait for the end of enumeration
    while (!HID.IsConfigured(&HID));

    // Start waiting some cmd

	// Check enumeration
	while (HID.IsConfigured(&HID) == 0) ;

	//HID.SendKey(&HID, VOLUP_SCAN_CODE);
	time_start = time;
	while (time < time_start + 3);
	HID.SendKey(&HID, 0);

}

void usb_send(unsigned char key) {
	HID.SendKey(&HID, key);
}
