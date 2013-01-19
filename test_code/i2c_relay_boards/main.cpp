#include <iostream>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "i2c-dev.h"

using namespace std;

#define RELAY_BOARD 0x20 //30a Relay Board
#define RELAY_ON    1
#define RELAY_OFF   0

#define RELAY_8     0
#define RELAY_7     1
#define RELAY_6     2
#define RELAY_5     3
#define RELAY_4     4
#define RELAY_3     5
#define RELAY_2     6
#define RELAY_1     7

int pin_array[2][8] = {
		0B01111111, 0B10111111, 0B11011111, 0B11101111, 0B11110111, 0B11111011, 0B11111101, 0B11111110,
		0B10000000, 0B01000000, 0B00100000, 0B00010000, 0B00001000, 0B00000100, 0B00000010, 0B00000001
};

int relayAction(int addr, int pin, int x);

int main() {

	cout << "Opening I2C Bus" << endl;




	cout << "'Random' relay test. Should see 7, 3, 4 go on. 7 off, 4 off, 7 on, 4 off, 3 off, 7 off." << endl;

	// Relay 7 - On
	relayAction(RELAY_BOARD, RELAY_7, RELAY_ON);
	sleep(1);
	// Relay 3 - On
	relayAction(RELAY_BOARD, RELAY_3, RELAY_ON);
	sleep(1);
	// Relay 4 - On
	relayAction(RELAY_BOARD, RELAY_4, RELAY_ON);
	sleep(5);
	// Relay 7 - Off
	relayAction(RELAY_BOARD, RELAY_7, RELAY_OFF);
	sleep(1);
	// Relay 4 - Off
	relayAction(RELAY_BOARD, RELAY_4, RELAY_OFF);
	sleep(1);
	// Relay 7 - On
	relayAction(RELAY_BOARD, RELAY_7, RELAY_ON);
	sleep(1);
	// Relay 4 - Off
	relayAction(RELAY_BOARD, RELAY_4, RELAY_OFF);
	sleep(1);
	// Relay 3 - Off
	relayAction(RELAY_BOARD, RELAY_3, RELAY_OFF);
	sleep(1);
	// Relay 7 - Off
	relayAction(RELAY_BOARD, RELAY_7, RELAY_OFF);
	sleep(1);

	cout << "Aaaaand, done!" << endl;


	cout << "Closing I2C Bus" << endl;



	return 0;
}

int relayAction(int addr, int pin, int x) {

	int file;

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

