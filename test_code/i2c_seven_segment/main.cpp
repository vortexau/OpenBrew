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

#define SEVEN_SEG_LCD_1 0x70 //30a Relay Board

uint16_t displaybuffer[8];
int file;

int beginTransmission();
void endTransmission();
void sendCharacters();

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

int main() {
	sendCharacters();
}

int beginTransmission() {

	// BeagleBone specific I2C bus
	if ((file = open("/dev/i2c-3", O_RDWR)) < 0) {
		cout << "Failed to open connection to the I2C Bus" << endl;
		return (1);
	}

	if (ioctl(file, I2C_SLAVE, SEVEN_SEG_LCD_1) < 0) {
		cout << "I2C_SLAVE address " << SEVEN_SEG_LCD_1 << " failed..." << endl;
		return (2);
	}

	return 1;
}

void endTransmission() {
	close(file);
}

void sendCharacters() {

	beginTransmission();

	i2c_smbus_write_byte(file, 0x21); // start oscillator
	i2c_smbus_write_byte(file, 0xE0 | 15); // set brightness to max
	i2c_smbus_write_byte(file, 0x81); // display on, blink off

	i2c_smbus_write_byte(file, 0x00); // starting RAM Address

	/*
	cout << "First numbers " << endl;

	displaybuffer[0] = 0x3F; // 0
	displaybuffer[1] = 0x06; // 1
	displaybuffer[2] = 0x00; // colon off
	displaybuffer[3] = 0x5B; // 2
	displaybuffer[4] = 0x4F; // 3

	i2c_smbus_write_i2c_block_data(file, 0x00, 8, (__u8 *)displaybuffer);

	sleep(1);

	cout << "Second numbers" << endl;

	displaybuffer[0] = 0x7C; // b
	displaybuffer[1] = 0x79; // E
	displaybuffer[2] = 0x00; // colon off
	displaybuffer[3] = 0x79; // E
	displaybuffer[4] = 0x71; // F

	i2c_smbus_write_i2c_block_data(file, 0x00, 8, (__u8 *)displaybuffer);

	sleep(1);

	displaybuffer[0] = 0x00; // clear
	displaybuffer[1] = 0x00; // clear
	displaybuffer[2] = 0x00; // colon off
	displaybuffer[3] = 0x00; // clear
	displaybuffer[4] = 0x00; // clear

	i2c_smbus_write_i2c_block_data(file, 0x00, 8, (__u8 *)displaybuffer);

	for (uint8_t i=0; i<16; i++) {

		displaybuffer[0] = numbertable[i];

		i2c_smbus_write_i2c_block_data(file, 0x00, 8, (__u8 *)displaybuffer);

		sleep(1);
	}

	*/

	// junk to loop around the edges. why not.


	for(;;) {

		// length 8 works best so far.

		displaybuffer[0] = 0x01;
		displaybuffer[1] = 0x01;
		displaybuffer[2] = 0x00; // colon.
		displaybuffer[3] = 0x01;
		displaybuffer[4] = 0x01;
		displaybuffer[5] = 0x01;
		displaybuffer[6] = 0x01;
		displaybuffer[7] = 0x01;


		if(write(file, displaybuffer, 8) != 8) {
			cout << "error with the write" << endl;
		}

		// i2c_smbus_write_i2c_block_data(file, 0x00, 8, (__u8 *)displaybuffer);

		displaybuffer[0] = 0x00;
		displaybuffer[1] = 0x00;
		displaybuffer[2] = 0x00; // colon.
		displaybuffer[3] = 0x00;
		displaybuffer[4] = 0x00;
		displaybuffer[5] = 0x00;
		displaybuffer[6] = 0x00;
		displaybuffer[7] = 0x00;

		i2c_smbus_write_i2c_block_data(file, 0x00, 8, (__u8 *)displaybuffer);

		cout << "loop" << endl;
		sleep(1);

		/*

		displaybuffer[0] = 0x01;
		displaybuffer[1] = 0x01;
		displaybuffer[2] = 0x00; // colon.
		displaybuffer[3] = 0x01;
		displaybuffer[4] = 0x01;
		displaybuffer[5] = 0x01;
		displaybuffer[6] = 0x01;
		displaybuffer[7] = 0x01;

		i2c_smbus_write_i2c_block_data(file, 0x00, 8, (__u8 *)displaybuffer);

		usleep(400);
		displaybuffer[0] = 0x02;
		displaybuffer[1] = 0x02;
		displaybuffer[2] = 0x00; // colon.
		displaybuffer[3] = 0x02;
		displaybuffer[4] = 0x02;
		displaybuffer[5] = 0x02;
		displaybuffer[6] = 0x02;
		displaybuffer[7] = 0x02;
		i2c_smbus_write_i2c_block_data(file, 0x00, 8, (__u8 *)displaybuffer);

		usleep(400);

		displaybuffer[0] = 0x04;
		displaybuffer[1] = 0x04;
		displaybuffer[2] = 0x00; // colon.
		displaybuffer[3] = 0x04;
		displaybuffer[4] = 0x04;
		displaybuffer[5] = 0x04;
		displaybuffer[6] = 0x04;
		displaybuffer[7] = 0x04;
		i2c_smbus_write_i2c_block_data(file, 0x00, 8, (__u8 *)displaybuffer);

		usleep(400);

		displaybuffer[0] = 0x08;
		displaybuffer[1] = 0x08;
		displaybuffer[2] = 0x00; // colon.
		displaybuffer[3] = 0x08;
		displaybuffer[4] = 0x08;
		displaybuffer[5] = 0x08;
		displaybuffer[6] = 0x08;
		displaybuffer[7] = 0x08;
		i2c_smbus_write_i2c_block_data(file, 0x00, 8, (__u8 *)displaybuffer);

		usleep(400);

		displaybuffer[0] = 0x10;
		displaybuffer[1] = 0x10;
		displaybuffer[2] = 0x00; // colon.
		displaybuffer[3] = 0x10;
		displaybuffer[4] = 0x10;
		displaybuffer[5] = 0x10;
		displaybuffer[6] = 0x10;
		displaybuffer[7] = 0x10;
		i2c_smbus_write_i2c_block_data(file, 0x00, 8, (__u8 *)displaybuffer);

		usleep(400);

		displaybuffer[0] = 0x20;
		displaybuffer[1] = 0x20;
		displaybuffer[2] = 0x00; // colon.
		displaybuffer[3] = 0x20;
		displaybuffer[4] = 0x20;
		displaybuffer[5] = 0x20;
		displaybuffer[6] = 0x20;
		displaybuffer[7] = 0x20;
		i2c_smbus_write_i2c_block_data(file, 0x00, 8, (__u8 *)displaybuffer);

		usleep(400);
		*/

	}

	endTransmission();
}

