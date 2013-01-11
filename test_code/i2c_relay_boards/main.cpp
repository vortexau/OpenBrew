#include <iostream>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "i2c-dev.h"

using namespace std;

#define RELAY_BOARD 0x20; //30a Relay Board
#define RELAY_ON    1;
#define RELAY_OFF   0;	

int pin_array[2][8] = {
  0B01111111, 0B10111111, 0B11011111, 0B11101111, 0B11110111, 0B11111011, 0B11111101, 0B11111110,
  0B10000000, 0B01000000, 0B00100000, 0B00010000, 0B00001000, 0B00000100, 0B00000010, 0B00000001
};

int main() {

	cout << "Opening I2C Bus" << endl;

	int file;

	// BeagleBone specific I2C bus
	if ((file = open("/dev/i2c-3", O_RDWR)) < 0) {
		cout << "Failed to open connection to the I2C Bus" << en
		dl;
		return (1);
	}

	if (ioctl(file, I2C_SLAVE, RELAY_BOARD) < 0) {
		cout << "I2C_SLAVE address " << RELAY_BOARD << " failed..." << endl;
		return (2);
	}

    // scroll thtrough the relays, switch on, then off.
    for(int i = 0; i < 8; i++) {
        
        relayAction(file, RELAY_BOARD, i, RELAY_ON);
        
        sleep(1);
        
        relayAction(file, RELAY_BOARD, i, RELAY_OFF);
        
        sleep(1)
        
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

void relayAction(int file, int addr, int pin, int x) {
  //state = PCF8574.read(addr);   
  // Read the current state fo the relay board.
  state = i2c_smbus_read_byte(file);

  // Using bitwise, add or subtract the relay you wish to turn on or off.
  if (x == RELAY_ON) { 
      state &= pin_array[0][pin];                      
  } else if (x == RELAY_OFF) {
      state |= pin_array[1][pin]; 
  }
  
  //PCF8574.write(addr, state);       // ON
  i2c_smbus_write_bite(file, state);
}

