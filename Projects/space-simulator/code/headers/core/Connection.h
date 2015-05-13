#pragma once

#include <string>
#include <cstring>
#include <unistd.h>
#include <memory.h>
#include <core/Game.h>
#include <iostream>
#include <core/event_queue.h>

#ifndef __APPLE__
    #include <winsock2.h>
#else
    #include <arpa/inet.h>
    #include <sys/time.h>
    #include <sys/socket.h>
    #include <fcntl.h>
#endif

#define TIMEOUT_WAIT 2500
#define SOCK_BUFFER_SIZE 1024
#define MSG_END '@'

namespace sss {

    class Connection {
        private:
            bool _connected;
            char _buffer[SOCK_BUFFER_SIZE];

#ifndef __APPLE__ 
            WSADATA _wsaData;
            SOCKET _socket;
            SOCKADDR_IN _sockAddr;
#else
            struct sockaddr_in _server;
            int _socketDesc;
          
#endif
            struct hostent* _host;
            int _port;
            std::string _ip;
        protected:
            Connection();
            ~Connection();
        public:
            static Connection& getInstance();

            bool makeConnection(const std::string& ip, int port);
            void disconnect();

            void printBuffer();
            void write(const std::string& msg);

            std::string getValue(const std::string& value);
            void setValue(const char* msg);


        private:
            void init();
            void clearBuffer();

        protected:
    };

}
