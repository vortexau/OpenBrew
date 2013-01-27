// Test file to connect to a 7 segment Adafruit LED
// display over i2c and test it.
//
//
//

#include <iostream>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdint.h>
#include "i2c-dev.h"

using namespace std;

#define SEVEN_SEG_LCD_0 0x70 //30a Relay Board
#define SEVEN_SEG_LCD_1 0x71 //30a Relay Board

static const uint8_t numbertable[] = {
	0x3F, /* 0 */
	0x06, /* 1 */
	0x5B, /* 2 */
	0x4F, /* 3 */
	0x66, /* 4 */
	0x6D, /* 5 */
	0x7D, /* 6 */
	0x07, /* 7 */
	0x7F, /* 8 */
	0x6F, /* 9 */
	0x77, /* a */
	0x7C, /* b */
	0x39, /* C */
	0x5E, /* d */
	0x79, /* E */
	0x71, /* F */
};

uint16_t displaybuffer[8];

int main() {

	int file;

	// BeagleBone specific I2C bus
	if ((file = open("/dev/i2c-3", O_RDWR)) < 0) {
		cout << "Failed to open connection to the I2C Bus" << endl;
		return (1);
	}

	if (ioctl(file, I2C_SLAVE, SEVEN_SEG_LCD_1) < 0) {
		cout << "I2C_SLAVE address " << SEVEN_SEG_LCD_1 << " failed..." << endl;
		return (2);
	}

	//state = PCF8574.read(addr);
	// Read the current state fo the relay board.
	//int state = i2c_smbus_read_byte(file);

	// Build a string to send to the 7segment display.
	// Awesome overview on how to build characters for the 7seg display here:
	// http://forums.adafruit.com/viewtopic.php?f=47&t=29897#p156582

	// Process of writing to the display.

	// Then to use his example:

//	// send 0x71 // = F
//	displaybuffer[0] = 0x71;
//	// send 0x3E // = U
//	displaybuffer[1] = 0x3E;
//	// send 0x00 // = colon off
//	displaybuffer[2] = 0x00;
//	// send 0x79 // = E
//	displaybuffer[3] = 0x79;
//	// send 0x38 // = L
//	displaybuffer[4] = 0x38;

	// send 0x71 // = F
	displaybuffer[0] = 0x3F; // 0
	// send 0x3E // = U
	displaybuffer[1] = 0x06; // 1
	// send 0x00 // = colon off
	displaybuffer[2] = 0x00;
	// send 0x79 // = E
	displaybuffer[3] = 0x5B; // 2
	// send 0x38 // = L
	displaybuffer[4] = 0x4F; // 3
	
	// send 0x21 - start the oscillator
	i2c_smbus_write_byte(file, 0x21);
	
	// send 0x81 - turn blink off and display on
//	i2c_smbus_write_byte(file, 0x81);
	// Hex is BLINK_CMD, DISPLAY_ON, BLINK_OFF
	i2c_smbus_write_byte(file, 0x80 | 0x01 | (0 << 1));
	
	// send 0xEF - set brightness to max (not really required, but a bit of a sanity check).
	i2c_smbus_write_byte(file, 0xE0 | 15);


	i2c_smbus_write_byte(file, 0x00); // Starting RAM address. Required.
	


	// loop through the displaybuffer and write the bytes.
//	for (uint8_t i=0; i<8; i++) {
//    		//Wire.write(displaybuffer[i] & 0xFF);
//    		i2c_smbus_write_byte(file, displaybuffer[i]);
// 	}



//	i2c_smbus_write_byte(file, state);

	close(file);

}
