// This is just a simple C++ program to turn an LED on and off.

// led3 path: /sys/class/leds/beaglebone::usr3

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main()
{

	int ledValue;
	string ledResponse;

	FILE *ledFile;

	for(;;) {

		cout << "Toggle LED? Y/N: ";
		getline(cin, ledResponse);

		cout << "You said: " << ledResponse << endl;

		if(ledResponse == "y" || ledResponse == "Y") {
			// Toggle the LED here.
			cout << "Toggling the LED, as requested!" << endl;

			// fopen the brightness file at LEDPATH
			ledFile = fopen("/sys/devices/platform/leds-gpio/leds/beaglebone::usr3/brightness", "rb+");

			if(ledFile == NULL) {
				perror("Opening the LED file failed!");
				exit(1);
			}

			ledValue = fgetc(ledFile);

			cout << "ledValue is " << ledValue <<  endl;

			// fwrite 1 or 0 to the 'brightness' file
			if(ledValue == '0') {
				fputs("1", ledFile);
			} else {
				fputs("0", ledFile);
			}

			if (ferror (ledFile)) {
			      cout << "Error Writing to file" << endl;
			}

			// fclose the file handle. Required to send the change we made above.
			fclose(ledFile);

		} else {
			cout << "Not toggling this time!" << endl;
		}

	}

	return 0;
}
