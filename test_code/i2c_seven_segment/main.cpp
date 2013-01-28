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
int file;

int beginTransmission();
void endTransmission();
void startOscillator();
void displayOnBlinkOff();
void setBrightness();
void sendCharacters();
void initDisplay();


int main() {

//	startOscillator();
//	displayOnBlinkOff();
//	setBrightness();
	initDisplay();
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

void startOscillator() {
	beginTransmission();
	i2c_smbus_write_byte(file, 0x21);
	endTransmission();
}

void displayOnBlinkOff() {
	beginTransmission();
	i2c_smbus_write_byte(file, 0x80 | 0x01 | (0 << 1));
	endTransmission();
}

void setBrightness() {
	beginTransmission();
	i2c_smbus_write_byte(file, 0xE0 | 15);
	endTransmission();
}

void initDisplay() {
	beginTransmission();
	i2c_smbus_write_byte(file, 0x21); // start oscillator
	i2c_smbus_write_byte(file, 0x80 | 0x01 | (0 << 1)); // display on, blink off
	i2c_smbus_write_byte(file, 0xE0 | 15); // set brightness to max
	endTransmission();
}

void sendCharacters() {

	beginTransmission();

	i2c_smbus_write_byte(file, 0x00);

	displaybuffer[0] = 0x3F; // 0
	displaybuffer[1] = 0x06; // 1
	displaybuffer[2] = 0x00; // colon off
	displaybuffer[3] = 0x5B; // 2
	displaybuffer[4] = 0x4F; // 3

	for (uint8_t i=0; i<8; i++) {
		//Wire.write(displaybuffer[i] & 0xFF);
		i2c_smbus_write_byte(file, displaybuffer[i] & 0xFF);
		i2c_smbus_write_byte(file, displaybuffer[i] >> 8);
	}

	endTransmission();
}

