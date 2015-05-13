#include "arduino/Serial.h"

Serial::Serial() {
    _connected = false;
    dataLen = SER_BUFFER_SIZE;
    readResult = 0;
}

Serial::Serial(const char* port) {
    _connected = false;
    dataLen = SER_BUFFER_SIZE;
    readResult = 0;
    connect(port);
}

Serial::~Serial() {
    if(_connected) {
        _connected = false;
        //Close the serial handler
        CloseHandle(_serial);
    }
}

bool Serial::connect(const char* port) {
    // Attempt a connection
    _serial = CreateFile(port, GENERIC_READ | GENERIC_WRITE,
        0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

    // Check if connection was successful
    if (_serial == INVALID_HANDLE_VALUE) {
        error("Error connecting to port: %lu", GetLastError());
        return false;
    } else {
        // If we're connected set up paramaters for the port
        DCB serialParams = {0};

        // Try to get the current port state
        if (!GetCommState(_serial, &serialParams)) {
            error("Failed to get current serial parameters");
            return false;
        } else {
            // Define serial connection parameters for the arduino board
            serialParams.BaudRate    = CBR_9600;
            serialParams.ByteSize    = 8;
            serialParams.StopBits    = ONESTOPBIT;
            serialParams.Parity      = NOPARITY;
            serialParams.fDtrControl = DTR_CONTROL_ENABLE;

            // Set params for the port
            if(!SetCommState(_serial, &serialParams)) {
                warn("Couldn't set serial port parameters");
                return true;
            } else {
                _connected = true;
                //Flush any remaining characters in the buffers 
                PurgeComm(_serial, PURGE_RXCLEAR | PURGE_TXCLEAR);
                Sleep(WAIT_TIME);
                return true;
            }
        }
    }
}

int Serial::read(char* buffer, unsigned int size) {
    // Number of bytes we've read
    DWORD bytesRead;
    // Number of bytes to read
    unsigned int toRead;

    //Use the ClearCommError function to get status info on the Serial port
    ClearCommError(_serial, &_errors, &_status);

    // If there's something to read, read it
    if (_status.cbInQue > 0) {
        if (_status.cbInQue > size) {
            toRead = size;
        } else {
            toRead = _status.cbInQue;
        }
        // Try to read the require number of chars, and return the number of read bytes on success
        if (ReadFile(_serial, buffer, toRead, &bytesRead, NULL) && bytesRead != 0) {
            return bytesRead;
        }
    }
    // If nothing has been read, or that an error was detected return -1
    return -1;
}


bool Serial::write(char* buffer, int size) {
    DWORD bytesSend;
    // Try to write the buffer on the Serial port
    if (!WriteFile(_serial, (void*)buffer, size, &bytesSend, 0)) {
        // In case it don't work get comm error and return false
        ClearCommError(_serial, &_errors, &_status);
        return false;
    } else {
        return true;
    }
}

void Serial::loop() {
    if (!done) {
        readResult = read(buffer, dataLen);
        if (readResult > -1) {
            if (buffer[0] == '1') {
                printf("PORT> RECV: \'%s\' (%i)\n", buffer, readResult);
                Connection::_connection.write("EVN#3;ENG;Weapon");
                done = true;
            }
            flushBuffer();
        }
    }
}

void Serial::flushBuffer() {
    for (int i = 0; i < SER_BUFFER_SIZE; ++i) {
        buffer[i] = '\0';
    }
}

Serial Serial::_port;