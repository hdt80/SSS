#include "network/Connection.h"

// =================================
// Constructor and deconstructor
// =================================
Connection::Connection() {
	init();
}

Connection::Connection(std::string ip, int port) {
	init();
	makeConnect(ip, port);
}

Connection::~Connection() {
	disconnect();
}

// =================================
// Methods
// =================================

// Initailze Winsock2 and create the socket we'll be using
void Connection::init() {
	_connected = false;
    // Initalizing Winsock
    // We'll use a Windows macro called MAKEWORD to determine the 
    // major and minor version of Winsock we'll use, 2.2
    int errorCode = WSAStartup(MAKEWORD(2, 2), &_wsaData);
	if (errorCode != 0) {
		error("Failed to initalize Winsock: %i", WSAGetLastError());
		close();
	} else {
		// Creates our SOCKET (Address family, type specifications, protocol)
		// AF_INET - Use IPv4
		// SOCK_STREAM - Two-way data streams
		// IPPROTO_TCP - Use TCP protocol
		_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (_socket == INVALID_SOCKET) {
			error("Socket creation failed: %i", WSAGetLastError());
			close();
		} else {
			u_long mode = 1;
			ioctlsocket(_socket, FIONBIO, &mode);
			info("Connection initalized");
			clearBuffer();
		}
	}
}

// Clean up Winsock, close sockets and close all open connections
void Connection::close() {
	WSACleanup();
	shutdown(_socket, SD_SEND);
	closesocket(_socket);

	_connected = false;
}

// Attempt to connect to the other socket
bool Connection::makeConnect(std::string ip, int port) {
	if (_connected == true) {
		warn("Already connected to %s:%i", _ip.c_str(), _port);
	}
	_ip   = ip;
	_port = port;

	debug("Attempting connection to %s:%i", _ip.c_str(), _port);

	// Resolve IP address for hostname
	if ((_host = gethostbyname(_ip.c_str())) == nullptr) {
		error("Failed to resolve hostname");
		close();
		return false;
	}

	// Setup our socket address struct
	_sockAddr.sin_family = AF_INET;
	_sockAddr.sin_port = htons(_port);
	_sockAddr.sin_addr.s_addr = *((unsigned long*) _host->h_addr);

	// Attempt to connect to server
	// Error number 10035 is WSAEWOULDBLOCK, which means an opperation was
	// called that would block the main thread. Because connect will cause blocking
	// we'll catch that as it's not important and is expected. 
	if (connect(_socket, (SOCKADDR*)(&_sockAddr), sizeof(_sockAddr)) != 0 &&
			WSAGetLastError() != 10035) {
		error("Failed to establish connection with the server: %i", WSAGetLastError());
		close();
		return false;
	} else {
		info("Connection made to %s:%i", _ip.c_str(), _port);
		//_connected = true;
		return true;
	}

}

// Disconnect from the other socket
void Connection::disconnect() {

}

// Print the buffer from the socket
void Connection::printBuffer() {
	if (!_connected) {
		//return;
	}
	int result = recv(_socket, _buffer, BUFFER_SIZE, 0);
	if (result == -1) { // If nothing is returned we don't want to print
		return;         // the buffer out yet
	}
	debug("RECV: \'%s\' (%i)", _buffer, result);

	std::string setTest(_buffer, 3);
	if (setTest == "SET") {
		setValue(_buffer);
		std::string toSet(_buffer + 4, strlen(_buffer));
	}

	clearBuffer();
}

// Sends a request to the server to get the value stored on the server
std::string Connection::getValue(std::string value) {
	if (!_connected) {
		//return "";
	}
	// Send a message to the server requesting a value
	std::string msg = "";
	msg.append("GET#");
	msg.append(value);
	Connection::_connection.write(msg);

	// Wait for a return message from the server, hopefully the value
	int result = recv(_socket, _buffer, BUFFER_SIZE, 0);
	if (result == -1) {
		warn("Recieved nothing when getting \'%s\'", value.c_str());
		return "";
	}

	std::string toReturn(_buffer);
	//debug("\'%s\':\'%s\'", value.c_str(), toReturn.c_str());

	clearBuffer();
	return toReturn;
}

// Set a value based on what message was recieved
void Connection::setValue(char* msg) {
	if (!_connected) {
		error("Not connected!");
		//return;
	}
	int keyStop = 0;
	// Finding the index of the char that splits the key and value
	for (unsigned int i = 0; i < strlen(msg); ++i) {
		if (msg[i] == ':') {
			keyStop = i;
			break;
		}
	}
	// -4 from keyStop cause second param is the amount of chars to create
	// from, so because it's offset by 4, we'll subtract 4
	std::string key(msg + 4, keyStop - 4);
	// Add one more to keyStop so the ':' isn't included
	std::string value(msg + keyStop + 1, strlen(msg));
	debug("\'%s\':\'%s\'", key.c_str(), value.c_str());

	if (Reactor::_reactor.contains(key)) {
		Reactor::_reactor.get(key)->currPower =
			strtol(value.c_str(), nullptr, 10);
	}
}

// Write a message to the socket
// message - Message to send
// Can't use send as Winsock uses that
void Connection::write(std::string message) {
	if (!_connected) {
		//return;
	}
	// SOCKET, char* buf, buff_size, flags
	if (send(_socket, (message + MSG_END).c_str(), strlen((message + MSG_END).c_str()), 0) == SOCKET_ERROR) {
		error("Error while writing to socket: %i", WSAGetLastError());
		_connected = false;
	}
	debug("SEND: \'%s\' (%i)", (message + MSG_END).c_str(), strlen((message + MSG_END).c_str()));
}

// Reset the buffer to null terminators
void Connection::clearBuffer() {
	for (int i = 0; i < BUFFER_SIZE; ++i) {
		_buffer[i] = '\0';
	}
}

// Create a reference to the static var _connection as it's used by multiple
// objects, such as Reactor, PowerCell and FixPanel
Connection Connection::_connection;
