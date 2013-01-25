// Test file to connect to a 7 segment Adafruit LED
// display over i2c and test it.
//
//
//

#include <iostream>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "i2c-dev.h"

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

void main() {


	// BeagleBone specific I2C bus
	if ((file = open("/dev/i2c-3", O_RDWR)) < 0) {
		cout << "Failed to open connection to the I2C Bus" << endl;
		return (1);
	}

	if (ioctl(file, I2C_SLAVE, RELAY_BOARD) < 0) {
		cout << "I2C_SLAVE address " << RELAY_BOARD << " failed..." << endl;
		return (2);
	}

	//state = PCF8574.read(addr);
	// Read the current state fo the relay board.
	int state = i2c_smbus_read_byte(file);

	// Using bitwise, add or subtract the relay you wish to turn on or off.
	if (x == RELAY_ON) {
		state &= pin_array[0][pin];
	} else if (x == RELAY_OFF) {
		state |= pin_array[1][pin];
	}

	//PCF8574.write(addr, state);       // ON
	i2c_smbus_write_byte(file, state);

	close(file);

}
