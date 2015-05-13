#ifndef SERIAL_H 
#define SERIAL_H

#define WAIT_TIME 2500
#define SER_BUFFER_SIZE 256

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#include "util/Logger.h"
#include "network/Connection.h"

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

        void loop();

        // Vars
        HANDLE  _serial; // Serial port handle
        COMSTAT _status; // Status of the serial port
        DWORD   _errors; // Errors from the serial port

        bool _connected;

        // Static var
        static Serial _port;

    private:
        void flushBuffer();

        char buffer[SER_BUFFER_SIZE];
        int  dataLen;
        int  readResult;

        bool done; // If the minigame has been done
};

#endif