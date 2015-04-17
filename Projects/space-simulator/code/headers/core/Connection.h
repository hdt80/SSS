#ifndef NETWORK_CONNECT_H
#define NETWORK_CONNECT_H

#include <string>
#include <string.h>
#include <unistd.h>
#include <iostream>

#include <winsock2.h>

#include "core/Logger.h"

#define TIMEOUT_WAIT 2500
#define CONBUF_SIZE  1024
#define MSG_END      '@'

// A Connection is a socket connection using UDP between two open
// sockets, wether is be Java or C++
class Connection {

    public:
        // Constructor and deconstructor
        Connection();
        Connection(std::string ip, int port);
        ~Connection();
        
        // Methods
        bool makeConnect(std::string ip, int port);
        void disconnect();

        void printBuffer();
        void write(std::string message);

        std::string getValue(std::string value);
        void        setValue(char* msg);

        static Connection _connection;
    private:
        bool _connected;
        char _buffer[CONBUF_SIZE];

        // Winsock data members
        WSADATA         _wsaData;
        SOCKET          _socket;
        struct hostent* _host;
        SOCKADDR_IN     _sockAddr;

        int  _port;      // Port connection
        std::string _ip; // IP of the other socket

        void init();  // Initalizes winsock2
        void close(); // Close ws2 and all resources
        void clearBuffer();
};

#endif
