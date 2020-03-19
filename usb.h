#ifndef __USB_H
#define __USB_H

#define A_SCAN_CODE	0x4
#define B_SCAN_CODE	0x5

int		usb_start ( void );
void	usb_send(unsigned char key);
#endif
