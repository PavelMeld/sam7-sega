//*----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : cdc_enumerate.h
//* Object              : Handle HID enumeration
//*
//* 1.0 Sept 05 2004 	: ODi Creation
//*----------------------------------------------------------------------------
#ifndef CDC_ENUMERATE_H
#define CDC_ENUMERATE_H


typedef struct _AT91S_HID
{
	// Private members
	AT91PS_UDP pUdp;
	unsigned char currentConfiguration;
	// Public Methods:
	unsigned char (*IsConfigured) (struct _AT91S_HID *pCdc);
	void (*SendReport)(struct _AT91S_HID *pCdc, char button, char x, char y);
	void (*SendKey)(struct _AT91S_HID *pCdc, unsigned char button);
	void (*SendJoypad)(struct _AT91S_HID *pCdc, 
			unsigned char up_down, unsigned char left_right,
			unsigned char a, unsigned char b, unsigned char c,
			unsigned char start);
} AT91S_HID, *AT91PS_HID;

//* external function description

AT91PS_HID AT91F_HID_Open(AT91PS_HID pHid, AT91PS_UDP pUdp);

#endif // CDC_ENUMERATE_H

