import socket
import sys


def get_constants(prefix):
    """Create a dictionary mapping socket module
    constants to their names.
    """
    return {
        getattr(socket, n): n
        for n in dir(socket)
        if n.startswith(prefix)
    }

def createConnection():

    return socket.create_connection(("localhost", 3000))

def createContainer(containerName):

    sock = createConnection()

    print("Connection established on port 3000")

    try:

        print("Trying request...")

        clientRequest = ("create" + containerName).encode()

        sock.sendall(clientRequest)

    finally:

        print("Request made succesfully")

        print("Closing connection...")

        sock.close()

        print("Connection closed succesfully")

def listContainers():

    sock = createConnection()

    print("Connection established on port 3000")

    try:

        print("Trying request...")

        clientRequest = ("list").encode()

        sock.sendall(clientRequest)

    finally:

        print("Request made succesfully")

        print("Closing connection...")

        sock.close()

        print("Connection closed succesfully")

def stopContainer(containerName):

    sock = createConnection()

    print("Connection established on port 3000")

    try:

        print("Trying request...")

        clientRequest = ("stop" + containerName).encode()

        sock.sendall(clientRequest)

    finally:

        print("Request made succesfully")

        print("Closing connection...")

        sock.close()

        print("Connection closed succesfully")

def removeContaienr(containerName):

    sock = createConnection()

    print("Connection established on port 3000")

    try:

        print("Trying request...")

        clientRequest = ("remove" + containerName).encode()

        sock.sendall(clientRequest)

    finally:

        print("Request made succesfully")

        print("Closing connection...")

        sock.close()

        print("Connection closed succesfully")

families = get_constants('AF_')

types = get_constants('SOCK_')

protocols = get_constants('IPPROTO_')

# Create a TCP/IP socket
sock = socket.create_connection(('localhost', 3000))

print('Family  :', families[sock.family])

print('Type    :', types[sock.type])

print('Protocol:', protocols[sock.proto])

print()

"""

try:

    # Send data
    message = b'This is the message.  It will be repeated.'
    print('sending {!r}'.format(message))
    sock.sendall(message)

    amount_received = 0
    amount_expected = len(message)

    while amount_received < amount_expected:
        data = sock.recv(16)
        amount_received += len(data)
        print('received {!r}'.format(data))

finally:
    print('closing socket')
    sock.close()

"""