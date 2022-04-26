/*

elastic-container-service Este servicio es el encargado de recibir las peticiones del cliente y ejecutarlas. Este servicio constara de dos procesos, el admin_container y el subscribe_host, los cuales se crearan usando fork.
El admin_container es el proceso encargado de recibir las peticiones para manejar los contenedores (crear, listar, detener y borrar contenedores). El subscribe_host, es un proceso encargado de recibir peticiones desde los hosts y lleva
un control de los hosts disponibles para crear contenedores. Solo los agentes que
corren en el host interactuan con el proceso subscribe_host.

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<unistd.h>	//write

int listContainers(){

	int list;

	struct sockaddr_in server;

	char petition[20], reply[50];

	list = socket(AF_INET, SOCK_STREAM, 0);

	if(list == -1){

		printf("Could not create socket");

	}

	puts("Socket created");

	server.sin_family = AF_INET;

	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	server.sin_port = htons(3001);

	if(connect(list, (struct sockaddr *)&server, sizeof(server)) < 0){

		perror("Connect failed. Error");

		return 1;
	}

	puts("Connected");

	memset(petition, 0, 20);

	strcpy(petition, "list");

	send(list, petition, strlen(petition), 0);

	memset(reply, 0, 50);

	recv(list, reply, 50, 0);

	printf("Response: %s\n", reply);

	close(list);

}


int main(int argc , char *argv[]) {
	
	int socket_desc, client_sock, c, read_size;

	struct sockaddr_in server, client;

	char client_message[2000];

	int received = 0;

	socket_desc = socket(AF_INET, SOCK_STREAM , 0);

	if(socket_desc == -1){

		printf("Could not create socket");

	}

	puts("Socket created");

	server.sin_family = AF_INET;

	server.sin_addr.s_addr = INADDR_ANY;

	server.sin_port = htons(3000);

	if(bind(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0){

		//print the error message

		perror("Bind failed. Error");

		return 1;

	}

	puts("Bind done");
	
	//Listen

	listen(socket_desc, 3);
	
	//Accept and incoming connection

	puts("Waiting for incoming connections...");

	c = sizeof(struct sockaddr_in);
	
	//accept connection from an incoming client

	client_sock = accept(socket_desc, (struct sockaddr *) &client, (socklen_t*) &c);

	if(client_sock < 0){

		perror("Accept failed");

		return 1;

	}

	puts("Connection accepted");
	
    while(!received){

        memset(client_message, 0, 2000);

        //Receive a message from client

        if(recv(client_sock, client_message, 2000, 0) > 0){

            printf("received message: %s\n", client_message);

            //Send the message back to client

			received = 1;

            send(client_sock, client_message, strlen(client_message), 0);

        } 
		
		else{

            puts("recv failed");

        }
		
    }

	return 0;
}