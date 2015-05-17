import threading
import Queue
import socket as sock
import select
import sys


IP = "localhost"
PORT = 5003

server_socket = sock.socket(sock.AF_INET, sock.SOCK_STREAM)
server_socket.setsockopt(sock.SOL_SOCKET, sock.SO_REUSEADDR, 1)
server_socket.bind((IP, PORT))
server_socket.listen(5)

connections = [server_socket]

running = True

def send_all(send_sock, msg):
    for socket in connections:
        if socket != server_socket and socket != send_sock:
            try:
                socket.send(msg)
            except:
                socket.close()
                connections.remove(socket)
                print("removed connection")


def server():

    while running:
        read_sockets, write_sockets, error_sockets = select.select(connections, [], [])

        for socket in read_sockets:
            if socket == server_socket:
                client, c_addr = server_socket.accept()
                connections.append(client)
            else:
                try:
                    data = socket.recv(8048)
                    if data:
                        send_all(socket, data)
                except sock.error as msg:
                    print(msg)
                    socket.close()
                    connections.remove(socket)
                    print("removed connection")
                    continue



if __name__ == '__main__':
    thread = None
    try:
        thread = threading.Thread(target=server)
        thread.daemon = True
        thread.start()
    except Exception as e:
        print("could not create thread")
        print(e.message)
        sys.exit(0)
    while 1:
        INPUT = input(">>> ").split(' ')
        if INPUT[0] == "quit":
            running = False
            break
        elif INPUT[0] == "write":
            send_all(server_socket, INPUT[1])
        else:
            print("Invalid Input")
    print("")
    # thread.join()



