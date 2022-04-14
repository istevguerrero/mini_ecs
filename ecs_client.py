import socket

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

        print("Connection closed succesfully")

        sock.close()

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