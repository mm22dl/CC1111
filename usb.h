#ifndef _USB_H_
#define _USB_H_

#include "cc1111.h"
#include "lib.h"
#include "led.h"

// USB bit masks
#define USB_INEP5IE (1 << 5)
#define USB_INEP4IE (1 << 4)
#define USB_INEP3IE (1 << 3)
#define USB_INEP2IE (1 << 2)
#define USB_INEP1IE (1 << 1)
#define USB_EP0IE   (1 << 0)

#define USB_OUTEP5IE (1 << 5)
#define USB_OUTEP4IE (1 << 4)
#define USB_OUTEP3IE (1 << 3)
#define USB_OUTEP2IE (1 << 2)
#define USB_OUTEP1IE (1 << 1)

#define USB_INEP5IF (1 << 5)
#define USB_INEP4IF (1 << 4)
#define USB_INEP3IF (1 << 3)
#define USB_INEP2IF (1 << 2)
#define USB_INEP1IF (1 << 1)
#define USB_EP0IF   (1 << 0)

#define USB_OUTEP5IF (1 << 5)
#define USB_OUTEP4IF (1 << 4)
#define USB_OUTEP3IF (1 << 3)
#define USB_OUTEP2IF (1 << 2)
#define USB_OUTEP1IF (1 << 1)

// USB setup masks
#define USB_SETUP_DIRECTION (0x01 << 7)
#define USB_SETUP_TYPE      (0x03 << 5)
#define USB_SETUP_RECIPIENT (0x1F << 0)

// USB directions
#define USB_DIRECTION_OUT (0 << 7)
#define USB_DIRECTION_IN  (1 << 7)

// USB types
#define USB_TYPE_STANDARD   (0 << 5)
#define USB_TYPE_CLASS      (1 << 5)
#define USB_TYPE_VENDOR     (2 << 5)
#define USB_TYPE_RESERVED   (3 << 5)

// USB recipients
#define USB_RECIPIENT_DEVICE    0
#define USB_RECIPIENT_INTERFACE 1
#define USB_RECIPIENT_EP        2
#define USB_RECIPIENT_OTHER     3

// USB standard requests
#define USB_REQUEST_GET_STATUS        0
#define USB_REQUEST_CLEAR_FEATURE     1
#define USB_REQUEST_SET_FEATURE       3
#define USB_REQUEST_SET_ADDRESS       5
#define USB_REQUEST_GET_DESCRIPTOR    6
#define USB_REQUEST_SET_DESCRIPTOR    7
#define USB_REQUEST_GET_CONFIGURATION 8
#define USB_REQUEST_SET_CONFIGURATION 9
#define USB_REQUEST_GET_INTERFACE     10
#define USB_REQUEST_SET_INTERFACE     11
#define USB_REQUEST_SYNCH_FRAME       12

// USB descriptors
#define USB_DESC_DEVICE           1
#define USB_DESC_CONFIGURATION    2
#define USB_DESC_STRING           3
#define USB_DESC_INTERFACE        4
#define USB_DESC_ENDPOINT         5
#define USB_DESC_DEVICE_QUALIFIER 6
#define USB_DESC_OTHER_SPEED      7
#define USB_DESC_INTERFACE_POWER  8

#define USB_TRANSFER_CONTROL     0
#define USB_TRANSFER_ISOCHRONOUS 1
#define USB_TRANSFER_BULK        2
#define USB_TRANSFER_INTERRUPT   3

// USB max bytes
#define USB_SIZE_EP_CONTROL 32
#define USB_SIZE_EP_OUT     64 // MAX: 256
#define USB_SIZE_EP_IN      64 // MAX: 512

// USB EPs
#define USB_EP_CONTROL 0
#define USB_EP_OUT     4
#define USB_EP_IN      5

// USB IF masks
#define USB_IF_CONTROL (1 << USB_EP_CONTROL)
#define USB_IF_OUT     (1 << USB_EP_OUT)
#define USB_IF_IN      (1 << USB_EP_IN)

// USB power
#define USB_MAX_POWER 100 // Maximum power in mA

// USB states
#define USB_STATE_IDLE    0
#define USB_STATE_SEND    1
#define USB_STATE_RECEIVE 2

// USB vendor and product IDs
#define USB_VID 0x0451
#define USB_PID 0x16A7

// USB string descriptors
#define USB_MANUFACTURER_LENGTH (29 * 2)
#define USB_MANUFACTURER \
	LE_WORD('k'),		 \
    LE_WORD('e'),		 \
    LE_WORD('i'),		 \
    LE_WORD('n'),		 \
    LE_WORD('e'),		 \
    LE_WORD('c'),		 \
    LE_WORD('h'),		 \
    LE_WORD('t'),		 \
    LE_WORD('e'),		 \
    LE_WORD('r'),		 \
    LE_WORD('d'),		 \
    LE_WORD('e'),		 \
    LE_WORD('u'),		 \
    LE_WORD('t'),		 \
    LE_WORD('s'),		 \
    LE_WORD('c'),		 \
    LE_WORD('h'),		 \
    LE_WORD('e'),		 \
    LE_WORD('r'),		 \
    LE_WORD('@'),		 \
    LE_WORD('g'),		 \
    LE_WORD('m'),		 \
    LE_WORD('a'),		 \
    LE_WORD('i'),		 \
    LE_WORD('l'),		 \
    LE_WORD('.'),		 \
    LE_WORD('c'),		 \
    LE_WORD('o'),		 \
    LE_WORD('m')

#define USB_PRODUCT_LENGTH (6 * 2)
#define USB_PRODUCT \
    LE_WORD('C'),	\
    LE_WORD('C'),	\
    LE_WORD('1'),	\
    LE_WORD('1'),	\
    LE_WORD('1'),	\
    LE_WORD('1')

#define USB_SERIAL_LENGTH (3 * 2)
#define USB_SERIAL \
    LE_WORD('0'),  \
    LE_WORD('0'),  \
    LE_WORD('1')

// USB descriptors
__xdata uint8_t usb_descriptors[] = {

    // Device descriptor
    18,                  // Size
    USB_DESC_DEVICE,     // Type
    LE_WORD(0x0200),     // USB specification number
    2,                   // Class
    0,                   // Subclass
    0,                   // Protocol
    USB_SIZE_EP_CONTROL, // Max packet size for EP0
    LE_WORD(USB_VID),    // Vendor
    LE_WORD(USB_PID),    // Product
    LE_WORD(0x0100),     // Release number
    1,                   // Manufacturer string descriptor index
    2,                   // Product string descriptor index
    3,                   // Serial number string descriptor index
    1,                   // Number of configurations

    // Configuration descriptor
    9,                      // Size
    USB_DESC_CONFIGURATION, // Type
    LE_WORD(32),            // Total length (configuration, interfaces and EPs)
    2,                      // Number of interfaces
    1,                      // Configuration index
    0,                      // Configuration string descriptor (none)
    192,                    // Power parameters for this configuration
    USB_MAX_POWER / 2,      // Max power in 2mA units (divided by 2)

    // Interface descriptor 1 (data)
    9,                  // Size
    USB_DESC_INTERFACE, // Type
    0,                  // Interface number (start with zero, then increment)
    0,                  // Alternative setting
    2,                  // Number of EP for this interface
    10,                 // Class (data)
    0,                  // Subclass
    0,                  // Protocol
    0,                  // Interface string descriptor (none)

    // Data EP OUT
    7,                              // Size
    USB_DESC_ENDPOINT,              // Type
    USB_DIRECTION_OUT | USB_EP_OUT, // Direction and address
    USB_TRANSFER_BULK,              // Transfer type
    LE_WORD(USB_SIZE_EP_OUT),       // Max packet size
    0,                              // Polling interval in frames (none)

    // Data EP IN
    7,                            // Size
    USB_DESC_ENDPOINT,            // Type
    USB_DIRECTION_IN | USB_EP_IN, // Direction and address
    USB_TRANSFER_BULK,            // Transfer type
    LE_WORD(USB_SIZE_EP_IN),      // Max packet size
    0,                            // Polling interval in frames (none)

    // String descriptors
    4,               // Size
    USB_DESC_STRING, // Type
    LE_WORD(0x1009), // Language (EN-CA)

    // String descriptor (manufacturer)
    USB_MANUFACTURER_LENGTH + 2,
    USB_DESC_STRING,
    USB_MANUFACTURER,

    // String descriptor (product)
    USB_PRODUCT_LENGTH + 2,
    USB_DESC_STRING,
    USB_PRODUCT,

    // String descriptor (serial)
    USB_SERIAL_LENGTH + 2,
    USB_DESC_STRING,
    USB_SERIAL,

    // EOD
    0
};

// USB device
struct usb_device {
    uint8_t configuration;
    uint8_t interface;
};

// USB setup
struct usb_setup_packet {
    uint8_t info;
    uint8_t request;
    uint16_t value;
    uint16_t index;
    uint16_t length;
};

// USB byte counters
struct usb_n_bytes {
    uint8_t ep0_out;
    uint8_t ep0_in;
    uint16_t ep_out;
    uint16_t ep_in;
    uint16_t ep_in_last;
};

void usb_init(void);
void usb_enable(void);
void usb_on(void);
void usb_off(void);
void usb_stall(void);
void usb_reset_flags(void);
void usb_reset_ep(int ep);
void usb_reset_counters(int ep);
void usb_enable_interrupts(void);
void usb_reset_interrupts(void);
void usb_set_ep(uint8_t ep);
uint8_t usb_get_ep(void);
void usb_write_byte(uint8_t byte);
uint8_t usb_read_byte(void);
void usb_ep0_queue_byte(uint8_t byte);
void usb_ep0_write_bytes(uint8_t n);
void usb_ep0_read_bytes(uint8_t n);
void usb_ep0_send_bytes(void);
void usb_ep0_receive_bytes(uint8_t end);
void usb_send_bytes(void);
void usb_received_bytes(void);
void usb_wait_in(void);
void usb_put_byte(uint8_t byte);
void usb_put_bytes(uint8_t *bytes);
void usb_flush_bytes(void);
int usb_poll_byte(void);
uint8_t usb_get_byte(void);
void usb_set_address(uint8_t addr);
void usb_set_configuration(uint8_t value);
void usb_get_configuration(void);
void usb_get_descriptor(uint16_t value);
void usb_get_setup_packet(void);
void usb_parse_setup_packet(void);
void usb_setup(void);
void usb_control(void);
void usb_out(void);
void usb_in(void);
void usb(void);
void usb_isr(void) __interrupt P2INT_VECTOR;

#endif