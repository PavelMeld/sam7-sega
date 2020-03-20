#ifndef __USB_H
#define __USB_H

#define W_SCAN_CODE		0x1A
#define S_SCAN_CODE		0x16
#define A_SCAN_CODE		0x04
#define B_SCAN_CODE		0x05
#define D_SCAN_CODE		0x07
#define Z_SCAN_CODE		0x1d
#define X_SCAN_CODE		0x1b
#define C_SCAN_CODE		0x06
#define V_SCAN_CODE		0x19
#define ENTER_SCAN_CODE	0x28

int		usb_start ( void );
void	usb_send(unsigned char key);
void usb_send_joypad(
		unsigned char up_down,
		unsigned char left_right,
		unsigned char a,
		unsigned char b,
		unsigned char c,
		unsigned char start);
#endif
