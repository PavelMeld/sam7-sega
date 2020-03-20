//*----------------------------------------------------------------------------
//*      ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : cdc_enumerate.c
//* Object              : Handle HID enumeration
//*
//* 1.0 Oct 05 2004 	: ODi Creation
//*----------------------------------------------------------------------------
#include "board.h"
#include "hid_enumerate.h"
#include "joypad.h"

typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define EP_NUMBER 1

const unsigned char langDescrID[] = {
	0x04, // bLength
	0x03, // Descriptor Type (3)
	0x09, // US 0x0409
	0x04
};

const unsigned char langDescrKeyboard[] = {
	0x1a, // bLength
	0x03, // Descriptor Type (3)
	'U', 0x00,
	'S', 0x00,
	'B', 0x00,
	' ', 0x00,
	'K', 0x00,
	'E', 0x00,
	'Y', 0x00,
	'B', 0x00,
	'O', 0x00,
	'A', 0x00,
	'R', 0x00,
	'D', 0x00,
};

const unsigned char langDescrKeyboardSino[] = {
	0x18, // bLength
	0x03, // Descriptor Type (3)
	'S', 0x00,
	'I', 0x00,
	'N', 0x00,
	'O', 0x00,
	' ', 0x00,
	'W', 0x00,
	'E', 0x00,
	'A', 0x00,
	'L', 0x00,
	'T', 0x00,
	'H', 0x00
};


char joypadDescriptor_mpv[] = {
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop) +

    0x09, 0x04,                    // USAGE (Joystick)	+
    0xa1, 0x01,                    // COLLECTION (Application) +

	0x85, 0x01,                    //   REPORT 1
    0xa1, 0x02,                    //     COLLECTION (Logical)
	0x75, 0x08,                    //       REPORT_SIZE (8)
    0x95, 0x02,                    //       REPORT_COUNT (2)
    0x15, 0x00,                    //         LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,              //         LOGICAL_MAXIMUM (255)
    0x35, 0x00,                    //         PHYSICAL_MINIMUM (0)
    0x46, 0xff, 0x00,              //         PHYSICAL_MAXIMUM (255)

    0x95, 0x02,                    //       REPORT_COUNT (2)
    0x09, 0x30,                    //         USAGE (X)
    0x09, 0x31,                    //         USAGE (Y)
    0x81, 0x02,                    //         INPUT (Data,Var,Abs)
	0x65, 0x00,                    //         UNITS (?)


// 8-bit buttons
	0x75, 0x01,                    //       REPORT_SIZE (1)
    0x95, 0x08,                    //       REPORT_COUNT (8)
	0x25, 0x01,                    //         LOGICAL_MAXIMUM (1)
    0x45, 0x01,                    //         PHYSICAL_MAXIMUM (1)
	0x05, 0x09,                    //         USAGE_PAGE (Button)
	0x19, 0x01,                    //         USAGE_MINIMUM (Button 1)
	0x29, 0x08,                    //         USAGE_MMAXIMUM (Button 8)
    0x81, 0x02,                    //         INPUT (Data,Var,Abs)

	0xC0,                          //     END COLLECTION
	0xC0                           //   END COLLECTION
};

char joypadDescriptor[] = {
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop) +

    0x09, 0x04,                    // USAGE (Joystick)	+
    0xa1, 0x01,                    // COLLECTION (Application) +

	0x85, 0x01,                    //   REPORT 1
    0xa1, 0x02,                    //     COLLECTION (Logical)
	0x75, 0x08,                    //       REPORT_SIZE (8)
    0x95, 0x02,                    //       REPORT_COUNT (2)
    0x15, 0x00,                    //         LOGICAL_MINIMUM (0)
    0x26, 0xff, 0x00,              //         LOGICAL_MAXIMUM (255)
    0x35, 0x00,                    //         PHYSICAL_MINIMUM (0)
    0x46, 0xff, 0x00,              //         PHYSICAL_MAXIMUM (255)

    0x95, 0x02,                    //       REPORT_COUNT (2)
	0x81, 0x01,                    //         Input (PADDING?)

    0x95, 0x02,                    //       REPORT_COUNT (2)
    0x09, 0x30,                    //         USAGE (X)
    0x09, 0x31,                    //         USAGE (Y)
    0x81, 0x02,                    //         INPUT (Data,Var,Abs)
	0x65, 0x00,                    //         UNITS (?)

// 4-bit padding
	0x75, 0x01,                    //       REPORT_SIZE (1)
    0x95, 0x04,                    //       REPORT_COUNT (4)
	0x25, 0x01,                    //         LOGICAL_MAXIMUM (1)
    0x45, 0x01,                    //         PHYSICAL_MAXIMUM (1)
	0x81, 0x01,                    //         Input (PADDING?)

// 10-bit buttons
	0x75, 0x01,                    //       REPORT_SIZE (1)
    0x95, 0x0A,                    //       REPORT_COUNT (10)
	0x25, 0x01,                    //         LOGICAL_MAXIMUM (1)
    0x45, 0x01,                    //         PHYSICAL_MAXIMUM (1)
	0x05, 0x09,                    //         USAGE_PAGE (Button)
	0x19, 0x01,                    //         USAGE_MINIMUM (Button 1)
	0x29, 0x0A,                    //         USAGE_MMAXIMUM (Button 10)
    0x81, 0x02,                    //         INPUT (Data,Var,Abs)

// 2-bit padding
	0x75, 0x01,                    //       REPORT_SIZE (1)
    0x95, 0x02,                    //       REPORT_COUNT (2)
	0x81, 0x01,                    //         Input (PADDING?)

// 8-bit ??
	0x06, 0x00, 0xff,              //       USAGE (0xFF 0x00)
	0x75, 0x01,                    //       REPORT_SIZE (1)
    0x95, 0x08,                    //       REPORT_COUNT (8)
	0x25, 0x01,                    //         LOGICAL_MAXIMUM (1)
    0x45, 0x01,                    //         PHYSICAL_MAXIMUM (1)
	0x09, 0x01,                    //         LOCAL USAGE (0xFF 0x01)
    0x81, 0x02,                    //         INPUT (Data,Var,Abs)
	0xC0,                          //     END COLLECTION
	0xC0                           //   END COLLECTION
};

// Check http://www.usb.org/developers/hidpage/#Class_Definition
const char devDescriptor[] = {
	/* Device descriptor */
	0x12,   // bLength
	0x01,   // bDescriptorType
	0x10,   // bcdUSBL
	0x01,   //
	0x00,   // bDeviceClass:
	0x00,   // bDeviceSubclass:
	0x00,   // bDeviceProtocol:
	0x08,   // bMaxPacketSize0
	0xFF,   // idVendorL
	0xFF,   //
	0x00,   // idProductL
	0x00,   //
	0x01,   // bcdDeviceL
	0x00,   //
	0x00,   // iManufacturer    // 0x01
	0x00,   // iProduct
	0x00,   // SerialNumber
	0x01    // bNumConfigs
};

const char cfgDescriptor[] = {
	/* ============== CONFIGURATION 1 =========== */
	/* Configuration 1 descriptor */
	0x09,   // CbLength
	0x02,   // CbDescriptorType
	0x22,   // CwTotalLength 2 EP + Control
	0x00,
	0x01,   // CbNumInterfaces
	0x01,   // CbConfigurationValue
	0x00,   // CiConfiguration
	0xA0,   // CbmAttributes Bus powered + Remote Wakeup
	0x32,   // CMaxPower: 100mA

	0x09, // bLength
	0x04, // bDescriptorType
	0x00, // bInterfaceNumber
	0x00, // bAlternateSetting
	0x01, // bNumEndpoints
	0x03, // bInterfaceClass: HID code
	0x00, // bInterfaceSubclass  @mpv : 00 - not subclass
	0x00, // bInterfaceProtocol: @mpv : 00 - none (as above is 00)
	0x00, // iInterface

	/* HID Descriptor */
	0x09, // bLength
	0x21, // bDescriptor type: HID Descriptor Type
	0x00, // bcdHID
	0x01,
	0x00, // bCountryCode @mpv 0 - not supported
	0x01, // bNumDescriptors
	0x22, // bDescriptorType (HID Report)
	sizeof(joypadDescriptor), // wItemLength
	0x00,

	/* Endpoint 1 descriptor */
	0x07,   // bLength
	0x05,   // bDescriptorType
	0x80 + EP_NUMBER,   // bEndpointAddress, Endpoint 01 - OUT
	0x03,   // bmAttributes      INT
	0x08,   // wMaxPacketSize: 8 bytes (Modifier, OEM + up to 6 scan codes)
	0x00,
	0x0A    // bInterval
};



/* USB standard request code */
#define STD_GET_STATUS_ZERO           0x0080
#define STD_GET_STATUS_INTERFACE      0x0081
#define STD_GET_STATUS_ENDPOINT       0x0082

#define STD_CLEAR_FEATURE_ZERO        0x0100
#define STD_CLEAR_FEATURE_INTERFACE   0x0101
#define STD_CLEAR_FEATURE_ENDPOINT    0x0102

#define STD_SET_FEATURE_ZERO          0x0300
#define STD_SET_FEATURE_INTERFACE     0x0301
#define STD_SET_FEATURE_ENDPOINT      0x0302

#define STD_SET_ADDRESS               0x0500
#define STD_GET_DESCRIPTOR            0x0680
#define STD_SET_DESCRIPTOR            0x0700
#define STD_GET_CONFIGURATION         0x0880
#define STD_SET_CONFIGURATION         0x0900
#define STD_GET_INTERFACE             0x0A81
#define STD_SET_INTERFACE             0x0B01
#define STD_SYNCH_FRAME               0x0C82

/* HID Class Specific Request Code */
#define STD_GET_HID_DESCRIPTOR        0x0681
#define STD_SET_IDLE                  0x0A21

static uchar AT91F_UDP_IsConfigured(AT91PS_HID);
static void AT91F_HID_SendReport(AT91PS_HID, char button, char x, char y);
static void AT91F_HID_Enumerate(AT91PS_HID);
static void AT91F_HID_SendJoypad( AT91PS_HID pHid, gamepad_t * pad);


//*----------------------------------------------------------------------------
//* \fn    AT91F_HID_Open
//* \brief
//*----------------------------------------------------------------------------
AT91PS_HID AT91F_HID_Open(AT91PS_HID pHid, AT91PS_UDP pUdp)
{
	pHid->pUdp = pUdp;
	pHid->currentConfiguration = 0;
	pHid->IsConfigured = AT91F_UDP_IsConfigured;
	pHid->SendReport   = AT91F_HID_SendReport;
	pHid->SendJoypad   = AT91F_HID_SendJoypad;
	return pHid;
}

//*----------------------------------------------------------------------------
//* \fn    AT91F_UDP_IsConfigured
//* \brief Test if the device is configured and handle enumeration
//*----------------------------------------------------------------------------
static uchar AT91F_UDP_IsConfigured(AT91PS_HID pHid)
{
	AT91PS_UDP pUDP = pHid->pUdp;
	AT91_REG isr = pUDP->UDP_ISR;

	if (isr & AT91C_UDP_ENDBUSRES) {
		pUDP->UDP_ICR = AT91C_UDP_ENDBUSRES;
		// reset all endpoints
		pUDP->UDP_RSTEP  = 0xf;
		pUDP->UDP_RSTEP  = 0;
		// Enable the function
		pUDP->UDP_FADDR = AT91C_UDP_FEN;
		// Configure endpoint 0
		pUDP->UDP_CSR[0] = (AT91C_UDP_EPEDS | AT91C_UDP_EPTYPE_CTRL);
	}
	else if (isr & AT91C_UDP_EPINT0) {
		pUDP->UDP_ICR = AT91C_UDP_EPINT0;
		AT91F_HID_Enumerate(pHid);
	}
	return pHid->currentConfiguration;
}


//*----------------------------------------------------------------------------
//* \fn    AT91F_HID_SendCoordinates
//* \brief Send Data through the control endpoint
//*----------------------------------------------------------------------------
static void AT91F_HID_SendReport(AT91PS_HID pHid, char button, char x, char y)
{
	AT91PS_UDP pUdp = pHid->pUdp;
	
	// Send report to the host
	pUdp->UDP_FDR[EP_NUMBER] = button;
	pUdp->UDP_FDR[EP_NUMBER] = x;
	pUdp->UDP_FDR[EP_NUMBER] = y;
	pUdp->UDP_CSR[EP_NUMBER] |= AT91C_UDP_TXPKTRDY;

	// Wait for the end of transmission
	while ( !(pUdp->UDP_CSR[EP_NUMBER] & AT91C_UDP_TXCOMP) )
		AT91F_UDP_IsConfigured(pHid);
		
	// Clear AT91C_UDP_TXCOMP flag
	if (pUdp->UDP_CSR[EP_NUMBER] & AT91C_UDP_TXCOMP) {
		pUdp->UDP_CSR[EP_NUMBER] &= ~(AT91C_UDP_TXCOMP);
		while (pUdp->UDP_CSR[EP_NUMBER] & AT91C_UDP_TXCOMP);
	}
}

static void AT91F_HID_SendJoypad(AT91PS_HID pHid, gamepad_t * pad) {
	AT91PS_UDP pUdp = pHid->pUdp;
	unsigned char left_right = 0x7F;
	unsigned char up_down = 0x7F;
	unsigned char abcx	= 0x0F ;
	unsigned char start_trig = 0x00;

	pUdp->UDP_FDR[EP_NUMBER] = 0x01;
	pUdp->UDP_FDR[EP_NUMBER] = 0x80;
	pUdp->UDP_FDR[EP_NUMBER] = 0x80;
	pUdp->UDP_FDR[EP_NUMBER] = 0;
	pUdp->UDP_FDR[EP_NUMBER] = 0;
	pUdp->UDP_FDR[EP_NUMBER] = 0;
	pUdp->UDP_FDR[EP_NUMBER] = 0;

	//if (pad->up)		up_down = 0;
	//if (pad->down)		up_down = 0xFF;
	//if (pad->left)		left_right = 0;
	//if (pad->right)		left_right = 0xFF;
	//if (pad->a)			abcx |= 0x10;
	//if (pad->b)			abcx |= 0x20;
	//if (pad->c)			abcx |= 0x40;
	//if (pad->x)			abcx |= 0x80;
	//if (pad->start)		start_trig |= 0x20;
	//if (pad->md)		start_trig |= 0x04;
	//
	//
	//// Send report to the host
	//pUdp->UDP_FDR[EP_NUMBER] = 0x01;
	//pUdp->UDP_FDR[EP_NUMBER] = 0x80;
	//pUdp->UDP_FDR[EP_NUMBER] = 0x80;
	//pUdp->UDP_FDR[EP_NUMBER] = left_right;
	//pUdp->UDP_FDR[EP_NUMBER] = up_down;
	//pUdp->UDP_FDR[EP_NUMBER] = abcx;
	//pUdp->UDP_FDR[EP_NUMBER] = start_trig;
	//pUdp->UDP_FDR[EP_NUMBER] = 0x00;


	pUdp->UDP_CSR[EP_NUMBER] |= AT91C_UDP_TXPKTRDY;

	// Wait for the end of transmission
	while ( !(pUdp->UDP_CSR[EP_NUMBER] & AT91C_UDP_TXCOMP) )
		AT91F_UDP_IsConfigured(pHid);
		
	// Clear AT91C_UDP_TXCOMP flag
	if (pUdp->UDP_CSR[EP_NUMBER] & AT91C_UDP_TXCOMP) {
		pUdp->UDP_CSR[EP_NUMBER] &= ~(AT91C_UDP_TXCOMP);
		while (pUdp->UDP_CSR[EP_NUMBER] & AT91C_UDP_TXCOMP);
	}
}




//*----------------------------------------------------------------------------
//* \fn    AT91F_USB_SendData
//* \brief Send Data through the control endpoint
//*----------------------------------------------------------------------------
static void AT91F_USB_SendData(AT91PS_UDP pUdp, const char *pData, uint length)
{
	uint cpt = 0;
	AT91_REG csr;

	do {
		cpt = MIN(length, 8);
		length -= cpt;

		while (cpt--)
			pUdp->UDP_FDR[0] = *pData++;

		if (pUdp->UDP_CSR[0] & AT91C_UDP_TXCOMP) {
			pUdp->UDP_CSR[0] &= ~(AT91C_UDP_TXCOMP);
			while (pUdp->UDP_CSR[0] & AT91C_UDP_TXCOMP);
		}

		pUdp->UDP_CSR[0] |= AT91C_UDP_TXPKTRDY;
		do {
			csr = pUdp->UDP_CSR[0];

			// Data IN stage has been stopped by a status OUT
			if (csr & AT91C_UDP_RX_DATA_BK0) {
				pUdp->UDP_CSR[0] &= ~(AT91C_UDP_RX_DATA_BK0);
				return;
			}
		} while ( !(csr & AT91C_UDP_TXCOMP) );

	} while (length);

	if (pUdp->UDP_CSR[0] & AT91C_UDP_TXCOMP) {
		pUdp->UDP_CSR[0] &= ~(AT91C_UDP_TXCOMP);
		while (pUdp->UDP_CSR[0] & AT91C_UDP_TXCOMP);
	}
}

//*----------------------------------------------------------------------------
//* \fn    AT91F_USB_SendZlp
//* \brief Send zero length packet through the control endpoint
//*----------------------------------------------------------------------------
void AT91F_USB_SendZlp(AT91PS_UDP pUdp)
{
	pUdp->UDP_CSR[0] |= AT91C_UDP_TXPKTRDY;
	while ( !(pUdp->UDP_CSR[0] & AT91C_UDP_TXCOMP) );
	pUdp->UDP_CSR[0] &= ~(AT91C_UDP_TXCOMP);
	while (pUdp->UDP_CSR[0] & AT91C_UDP_TXCOMP);
}

//*----------------------------------------------------------------------------
//* \fn    AT91F_USB_SendStall
//* \brief Stall the control endpoint
//*----------------------------------------------------------------------------
void AT91F_USB_SendStall(AT91PS_UDP pUdp)
{
	pUdp->UDP_CSR[0] |= AT91C_UDP_FORCESTALL;
	while ( !(pUdp->UDP_CSR[0] & AT91C_UDP_ISOERROR) );
	pUdp->UDP_CSR[0] &= ~(AT91C_UDP_FORCESTALL | AT91C_UDP_ISOERROR);
	while (pUdp->UDP_CSR[0] & (AT91C_UDP_FORCESTALL | AT91C_UDP_ISOERROR));
}

//*----------------------------------------------------------------------------
//* \fn    AT91F_HID_Enumerate
//* \brief This function is a callback invoked when a SETUP packet is received
//*----------------------------------------------------------------------------
static void AT91F_HID_Enumerate(AT91PS_HID pHid)
{
	AT91PS_UDP pUDP = pHid->pUdp;
	uchar bmRequestType, bRequest;
	ushort wValue, wIndex, wLength, wStatus;


	if ( !(pUDP->UDP_CSR[0] & AT91C_UDP_RXSETUP) )
		return;

	bmRequestType = pUDP->UDP_FDR[0];
	bRequest      = pUDP->UDP_FDR[0];
	wValue        = (pUDP->UDP_FDR[0] & 0xFF);
	wValue       |= (pUDP->UDP_FDR[0] << 8);
	wIndex        = (pUDP->UDP_FDR[0] & 0xFF);
	wIndex       |= (pUDP->UDP_FDR[0] << 8);
	wLength       = (pUDP->UDP_FDR[0] & 0xFF);
	wLength      |= (pUDP->UDP_FDR[0] << 8);

	if (bmRequestType & 0x80) {
		pUDP->UDP_CSR[0] |= AT91C_UDP_DIR;
		while ( !(pUDP->UDP_CSR[0] & AT91C_UDP_DIR) );
	}
	pUDP->UDP_CSR[0] &= ~AT91C_UDP_RXSETUP;
	while ( (pUDP->UDP_CSR[0]  & AT91C_UDP_RXSETUP)  );

	// Handle supported standard device request Cf Table 9-3 in USB specification Rev 1.1
	switch ((bRequest << 8) | bmRequestType) {
	case STD_GET_DESCRIPTOR:
		if (wValue == 0x100)       // Return Device Descriptor
			AT91F_USB_SendData(pUDP, devDescriptor, MIN(sizeof(devDescriptor), wLength));
		else if (wValue == 0x200)  // Return Configuration Descriptor
			AT91F_USB_SendData(pUDP, cfgDescriptor, MIN(sizeof(cfgDescriptor), wLength));
		else if (wValue == 0x300)  // Return Language Descriptor
			AT91F_USB_SendData(pUDP, langDescrID, MIN(sizeof(langDescrID), wLength));
		else if (wValue == 0x301)  // Return Language Descriptor 1 
			AT91F_USB_SendData(pUDP, langDescrKeyboardSino, MIN(sizeof(langDescrKeyboardSino), wLength));
		else if (wValue == 0x302)  // Return Language Descriptor 2 
			AT91F_USB_SendData(pUDP, langDescrKeyboard, MIN(sizeof(langDescrKeyboard), wLength));
		else
			AT91F_USB_SendStall(pUDP);
		break;
	case STD_SET_ADDRESS:
		AT91F_USB_SendZlp(pUDP);
		pUDP->UDP_FADDR = (AT91C_UDP_FEN | wValue);
		pUDP->UDP_GLBSTATE  = (wValue) ? AT91C_UDP_FADDEN : 0;
		break;
	case STD_SET_CONFIGURATION:
		pHid->currentConfiguration = wValue;
		AT91F_USB_SendZlp(pUDP);
		pUDP->UDP_GLBSTATE  = (wValue) ? AT91C_UDP_CONFG : AT91C_UDP_FADDEN;
		pUDP->UDP_CSR[EP_NUMBER] = (wValue) ? (AT91C_UDP_EPEDS | AT91C_UDP_EPTYPE_BULK_IN)   : 0;
		break;
	case STD_GET_CONFIGURATION:
		AT91F_USB_SendData(pUDP, (char *) &(pHid->currentConfiguration), sizeof(pHid->currentConfiguration));
		break;
	case STD_GET_STATUS_ZERO:
		wStatus = 0;
		AT91F_USB_SendData(pUDP, (char *) &wStatus, sizeof(wStatus));
		break;
	case STD_GET_STATUS_INTERFACE:
		wStatus = 0;
		AT91F_USB_SendData(pUDP, (char *) &wStatus, sizeof(wStatus));
		break;
	case STD_GET_STATUS_ENDPOINT:
		wStatus = 0;
		wIndex &= 0x0F;
		if ((pUDP->UDP_GLBSTATE & AT91C_UDP_CONFG) && (wIndex <= 3)) {
			wStatus = (pUDP->UDP_CSR[wIndex] & AT91C_UDP_EPEDS) ? 0 : 1;
			AT91F_USB_SendData(pUDP, (char *) &wStatus, sizeof(wStatus));
		}
		else if ((pUDP->UDP_GLBSTATE & AT91C_UDP_FADDEN) && (wIndex == 0)) {
			wStatus = (pUDP->UDP_CSR[wIndex] & AT91C_UDP_EPEDS) ? 0 : 1;
			AT91F_USB_SendData(pUDP, (char *) &wStatus, sizeof(wStatus));
		}
		else
			AT91F_USB_SendStall(pUDP);
		break;
	case STD_SET_FEATURE_ZERO:
		AT91F_USB_SendStall(pUDP);
	    break;
	case STD_SET_FEATURE_INTERFACE:
		AT91F_USB_SendZlp(pUDP);
		break;
	case STD_SET_FEATURE_ENDPOINT:
		wIndex &= 0x0F;
		if ((wValue == 0) && wIndex && (wIndex <= 3)) {
			pUDP->UDP_CSR[wIndex] = 0;
			AT91F_USB_SendZlp(pUDP);
		}
		else
			AT91F_USB_SendStall(pUDP);
		break;
	case STD_CLEAR_FEATURE_ZERO:
		AT91F_USB_SendStall(pUDP);
	    break;
	case STD_CLEAR_FEATURE_INTERFACE:
		AT91F_USB_SendZlp(pUDP);
		break;
	case STD_CLEAR_FEATURE_ENDPOINT:
		wIndex &= 0x0F;
		if ((wValue == 0) && wIndex && (wIndex <= 3)) {
			if (wIndex == 1)
				pUDP->UDP_CSR[1] = (AT91C_UDP_EPEDS | AT91C_UDP_EPTYPE_BULK_OUT);
			else if (wIndex == 2)
				pUDP->UDP_CSR[2] = (AT91C_UDP_EPEDS | AT91C_UDP_EPTYPE_BULK_IN);
			else if (wIndex == 3)
				pUDP->UDP_CSR[3] = (AT91C_UDP_EPEDS | AT91C_UDP_EPTYPE_ISO_IN);
			AT91F_USB_SendZlp(pUDP);
		}
		else
			AT91F_USB_SendStall(pUDP);
		break;

	// handle HID class requests
	case STD_GET_HID_DESCRIPTOR:
		if (wValue == 0x2200) 
			AT91F_USB_SendData(pUDP, (const char *) joypadDescriptor, MIN(sizeof(joypadDescriptor), wLength));
		else
			AT91F_USB_SendStall(pUDP);
		break;

	case STD_SET_IDLE:
		AT91F_USB_SendZlp(pUDP);
		break;
		
	default:
		AT91F_USB_SendStall(pUDP);
	    break;
	}
}
