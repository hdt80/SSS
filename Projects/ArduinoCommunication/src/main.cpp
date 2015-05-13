// =================================
// Includes
// =================================
#include <cstdio>
#include <cstdlib>

#include "Serial.h"

#define BUFFER_SIZE 256

void flushBuffer(char* buffer, int size) {
	for (int i = 0; i < size; ++i) {
		buffer[i] = '\0';
	}
}

// =================================
// Main
// =================================
int main(int argc, char* argv[]) {
	info("Attempting to connect to Arduino");

	Serial port;
	port.connect("COM4");

	if (port._connected) {
		info("Connected to Arduino");
	}

	char data[BUFFER_SIZE]; // Pre-allocate a buffer
	flushBuffer(data, BUFFER_SIZE);

	int dataLength = BUFFER_SIZE; // How many bytes to read
	int readResult = 0;   // How many bytes we read from the serial port

	while (port._connected) {
		readResult = port.read(data, dataLength);
		if (readResult > -1) {
			printf("RECV: \'%s\' (%i)\n", data, readResult);
			flushBuffer(data, BUFFER_SIZE);
		}
	}
	return 0;
}