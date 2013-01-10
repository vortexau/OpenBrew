#include <iostream>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "i2c-dev.h"

using namespace std;

#define relay_board 0x38;

int main() {

	cout << "Opening I2C Bus" << endl;

	int file;

	// BeagleBone specific I2C bus
	if ((file = open("/dev/i2c-3", O_RDWR)) < 0) {
		cout << "Failed to open connection to the I2C Bus" << en
		dl;
		return (1);
	}

	if (ioctl(file, I2C_SLAVE, 0x20) < 0) {
		cout << "I2C_SLAVE address " << 0x20 << " failed..." << endl;
		return (2);
	}

	// Turn all the relays on. We do this by sending 0
	if (i2c_smbus_write_byte(file, 0x00) < 0) {
		cout << "Failed to enable all relays!" << endl;
	} else {
		cout << "All relays enabled." << endl;
		
	}

	sleep(2);

	// We will need to work out a sensible way to turn relays on and off
	// using the hex methods.

	// Turn all the relays off.
	// We do this by sending 255.
	if (i2c_smbus_write_byte(file, 0xFF) < 0) {
		cout << "Failed to disable all relays!" << endl;
	} else {
		cout << "All relays disabled" << endl;
	}

	cout << "Closing I2C Bus" << endl;

	close(file);

	return 0;
}

