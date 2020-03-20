//----------------------------------------------------------------------------------------------------
//         ATMEL Microcontroller Software Support  -  ROUSSET  -
//----------------------------------------------------------------------------------------------------
// The software is delivered "AS IS" without warranty or condition of any
// kind, either express, implied or statutory. This includes without
// limitation any warranty or condition with respect to merchantability or
// fitness for any particular purpose, or against the infringements of
// intellectual property rights of others.
//----------------------------------------------------------------------------------------------------
// File Name: 	Board.h
// Object: 		AT91SAM7S Evaluation Board Features Definition File.
//
// Creation:	JPP   16/June/2004
//----------------------------------------------------------------------------------------------------   
#ifndef Board_h
#define Board_h

#include "AT91SAM7S256.h"
#define __inline inline

#define true	-1
#define false	0

//----------------------------------------------- 
// SAM7Board Memories Definition   
//-----------------------------------------------  
// The AT91SAM7S64 embeds a 16-Kbyte SRAM bank, and 64 K-Byte Flash

#define  INT_SRAM			0x00200000
#define  INT_SRAM_REMAP		0x00000000

#define  INT_FLASH			0x00000000
#define  INT_FLASH_REMAP	0x00100000

#define  FLASH_PAGE_NB		512
#define  FLASH_PAGE_SIZE	128

//------------------------  
// Leds Definition   
//------------------------  
// Inputs
#define DB9_1_UP_Z		(1U<<0)
#define DB9_2_DOWN_Y	(1U<<2)
#define DB9_3_LEFT_X	(1U<<4)
#define DB9_4_RIGHT_MD	(1U<<6)
#define DB9_6_AB		(1U<<8)
#define DB9_7_SELECT	(1U<<10)
#define DB9_9_START_C	(1U<<12)

#define LED1			(1<<14)						// PA8
#define NB_LEB			3
#define LED_MASK		(LED1)

#define PA_INPUTS  (DB9_1_UP_Z|DB9_2_DOWN_Y|DB9_3_LEFT_X|DB9_4_RIGHT_MD|DB9_6_AB|DB9_9_START_C)
#define PA_OUTPUTS (DB9_7_SELECT|LED1)


//----------------------------------  
// Push Buttons Definition   
//-----------------------------------  
#define SW1_MASK	(1<<19)							// PA19   
#define SW2_MASK	(1<<20)							// PA20   
#define SW_MASK		(SW1_MASK|SW2_MASK)

#define SW1			(1<<19)	   						// PA19
#define SW2			(1<<20)	    					// PA20

//-------------------------  
// USART Definition   
//-------------------------  
// SUB-D 9 points J3 DBGU
#define DBGU_RXD		AT91C_PA9_DRXD				// JP11 must be close   
#define DBGU_TXD		AT91C_PA10_DTXD				// JP12 must be close   
#define AT91C_DBGU_BAUD	115200						// Baud rate
#define US_RXD_PIN		AT91C_PA5_RXD0				// JP9 must be close   
#define US_TXD_PIN		AT91C_PA6_TXD0				// JP7 must be close   
#define US_RTS_PIN		AT91C_PA7_RTS0				// JP8 must be close   
#define US_CTS_PIN		AT91C_PA8_CTS0				// JP6 must be close   

//--------------  
// Master Clock   
//--------------  
#define EXT_OC		18432000						// Exetrnal ocilator MAINCK
#define MCK			47923200						// MCK (PLLRC div by 2)
#define MCKKHz		(MCK/1000)     					//

#endif   // Board_h     
