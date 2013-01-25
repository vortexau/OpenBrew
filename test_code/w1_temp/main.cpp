// Simple program to read and display all temp sensors connected to the OneWire bus.

#include <fstream>
#include <iostream>
#include <string>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

int main() {

	string dir, filepath, thisdir;
	struct dirent *dirp;
	struct stat filestat;
	struct stat status;
	char oneWirePath[64] = "/sys/bus/w1/devices";

	// Print out the OneWire sensors we have found.

	DIR *dirHandle;

	dirHandle = opendir(oneWirePath);

	if(dirHandle == NULL) {
		cout << "Error opening directory for reading" << endl;
		return 1;
	}

	while( (dirp = readdir(dirHandle)) ) {

		// for each of the directories in the list, we need to check to see if each
		// is a valid sensor.

		// Ignore the directory 'w1_bus_master1'
		// Ignore the directory '.'
		// Ignore the directory '..'
		if(dirp->d_name[0] == '.') { // ignore directories that start with .
			continue;
		}

		cout << "Sensor Found: " << dirp->d_name << endl;

		char charThisDir[124];
		strcpy(charThisDir, oneWirePath);
		strcat(charThisDir, "/");
		strcat(charThisDir, dirp->d_name);
		strcat(charThisDir, "/w1_slave");

		cout << "Checking for existence of w1_slave in path " << charThisDir << endl;

		ifstream w1_detail(charThisDir);
		if (w1_detail.good()) {
			cout << "This sensor appears to be a real sensor. Details are: " << endl;

			std::string content;
			content.assign( (std::istreambuf_iterator<char>(w1_detail) ),
			                (std::istreambuf_iterator<char>()    ) );

			cout << content << endl;

			// loop through the lines of the file here.
			// We know the first 26 chars are the sensor address.

			cout << "------------" << endl;

		}

	}

	closedir(dirHandle);

	return 0;
}
