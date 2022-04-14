import socket

sock = socket.create_connection(('localhost', 3000))

try:

    message = "hola"
    sock.sendall(message)

finally:
    print('closing socket')
    sock.close()