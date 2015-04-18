#include <core/Connection.h>

namespace sss {

    Connection& Connection::getInstance() {
        static Connection INSTANCE;
        return INSTANCE;
    }

    Connection::Connection() {
    
    }

    Connection::~Connection() {
        disconnect();
    }

#ifndef __APPLE__


    void Connection::init() {
        int errorCode = WSAStartup(MAKEWORD(2, 2), &_wsaData);
        if(errorCode != 0) {
            disconnect();
        } else {
            _socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            if(_socket == INVALID_SOCKET) {
                disconnect();
            } else {
                u_long mode = 1;
                ioctlsocket(_socket, FIONBIO, &mode);
                clearBuffer();
            }
        }
    }

    void Connection::disconnect() {
        WSACleanup();
        shutdown(_socket, SD_SEND);
        closesocket(_socket);

        _connected = false;
    }

    bool Connection::makeConnection(const std::string& ip, int port) {
        _ip = ip;
        _port = port;

        /* resolve IP address for hostname */
        if((_host = gethostbyname(_ip.c_str())) == nullptr) {
            std::cerr << " Failed to resolve hostname " << std::endl;
            disconnect();
            return false;
        }

        /* Set our socket address struct */
        _sockAddr.sin_family = AF_INET;
        _sockAddr.sin_port   = htons( _port );
        _sockAddr.sin_addr.s_addr = *((unsigned long*) _host->h_addr);

        /*
         * Attempt to connect to server
         * error number 10035 is WSAWOULDBLOCK, which means an opperation was
         * called that would bloeck the main thread. becuase connect will cause blocking
         * we'll catch that as it's not important and is expected
         */
        if(connect(_socket, (SOCKADDR*)(&_sockAddr), sizeof(_sockAddr)) != 0 and WSAGetLastError() != 10035) {
            disconnect();
            return false;
        } else {
            return true;
        }
    }

    /* print the buffer from the socket */
    void Connection::printBuffer() {

        memset(_buffer, 0, sizeof(_buffer));
        int result = recv(_socket, _buffer, SOCK_BUFFER_SIZE, 0);
        if(result == -1) 
            return;

        std::string setTest(_buffer, 3);
        if(not setTest.compare("SET")) {
            setValue(_buffer + 4);
        }

        clearBuffer();
    }

    std::string Connection::getValue(const std::string& value) {
        std::string msg = "";
        msg.append("GET#");
        msg.append(value);
        write(msg);

        int result = recv(_socket, _buffer, SOCK_BUFFER_SIZE, 0);
        if(result == -1) 
            return "";

        std::string toReturn(_buffer);

        clearBuffer();
        return toReturn;
    }

    void Connection::setValue(const char* msg) {
        int keyStop = 0;
        for(size_t i = 0; i < strlen(msg); ++i) {
            if(msg[i] == ':') {
                keyStop = i;
                break;
            }
        }

        std::string key(msg + 4, keyStop - 4);
        std::string value(msg + keyStop + 1, strlen(msg));


        /**********************************
         * Parse the input
         **********************************/

    }

    void Connection::write(const std::string& message) {
        if (send(_socket, (message + MSG_END).c_str(), strlen((message + MSG_END).c_str()), 0) == SOCKET_ERROR) {
			printf("Error while writing to socket: %i\n", WSAGetLastError());
		}
		printf("SEND: \'%s\' (%i)\n", (message + MSG_END).c_str(), strlen((message + MSG_END).c_str()));
    }

    void Connection::clearBuffer() {
        memset(_buffer, 0, sizeof(_buffer));
    }

#else

    bool Connection::makeConnection(const std::string& ip, int port) {
        _ip = ip;
        _port = port;

        _socketDesc = socket(AF_INET, SOCK_STREAM, 0);
        if(_socketDesc == -1) {
            std::cerr << " could not create socket " << std::endl;
            return false;
        }

        // if((fcntl(_socketDesc, F_SETFL, O_NONBLOCK)) < 0) {
        //     std::cerr << "Could not set socket to non-blocking" << std::endl;
        //     return false;
        // }
        memset(&_server, 0, sizeof(_server));

        _server.sin_addr.s_addr = inet_addr(_ip.c_str());
        _server.sin_family      = AF_INET;
        _server.sin_port        = htons( _port ); 

        if(connect(_socketDesc, (struct sockaddr*)&_server, sizeof(_server)) < 0) {
            std::cerr << " connect error " << std::endl;
            return false;
        }

        _connected = true;

        return true;
    }

    void Connection::disconnect() {
        close(_socketDesc);
        _connected = false;
    }

    void Connection::printBuffer() {

        struct timeval tv;
        fd_set read_fds;

        tv.tv_sec = 2;
        tv.tv_usec = 5000000;

        FD_ZERO(&read_fds);
        // FD_SET(0, &read_fds);

        // if(select(1, &read_fds, NULL, NULL, &tv) == -1) {
        //     std::cerr << "select error" << std::endl;  
        //     return;
        // }

        int result = recv(_socketDesc, &_buffer[0], SOCK_BUFFER_SIZE, 0);
        if(result == -1) 
            return;

        printf("%s\n", _buffer);

        std::string setTest(_buffer, 3);
        if(not setTest.compare("SET")) 
            setValue(_buffer);



        clearBuffer();

    }

    std::string Connection::getValue(const std::string& value) {
        std::string msg = "";
        msg.append("GET#");
        msg.append(value);
        write(msg);

        int result = recv(_socketDesc, _buffer, SOCK_BUFFER_SIZE, 0);
        if(result == -1) 
            return "";

        std::string toReturn(_buffer);

        clearBuffer();
        return toReturn;
    }

    void Connection::setValue(const char* msg) {
        int keyStop = 0;
        for(size_t i = 0; i < strlen(msg); ++i) {
            if(msg[i] == ':') {
                keyStop = i;
                break;
            }
        }

        std::string key(msg + 4, keyStop - 4);

        std::string value(msg + keyStop + 1, strlen(msg));

        /***************************************
         * Parse Input
         ***************************************/

    }

    void Connection::write(const std::string& msg) {
        if(send(_socketDesc, (msg + MSG_END).c_str(), msg.length() + 1, 0) < 0)
            std::cout << "Error Writing" << std::endl;
    }

    void Connection::clearBuffer() {
        memset(_buffer, 0, SOCK_BUFFER_SIZE);
    }
#endif
}
