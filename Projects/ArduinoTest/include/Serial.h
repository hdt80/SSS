#ifndef SERIAL_H 
#define SERIAL_H

#define WAIT_TIME 2500

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#include "Logger.h"

class Serial {
    public:
        // Constructors
        Serial();
        Serial(const char* port);
        ~Serial();

        // Methods
        bool connect(const char* port);

        int  read(char* buffer, unsigned int size);
        bool write(char* buffer, int size);

        // Vars
        HANDLE  _serial; // Serial port handle
        COMSTAT _status; // Status of the serial port
        DWORD   _errors; // Errors from the serial port

        bool _connected;
};

#endif