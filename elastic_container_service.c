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

	/*
	
	Todo esto de hace para enviar el mensaje de listar contenedores al host1 por el localhost usando el puerto 3001

	*/

	int sock;

	struct sockaddr_in server;

	char message[20], server_reply[50];

	sock = socket(AF_INET, SOCK_STREAM, 0);

	if(sock == -1){

		printf("Could not create socket");

	}

	puts("Socket created");

	server.sin_family = AF_INET;

	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	server.sin_port = htons(3001);

	if(connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0){

		perror("Connect failed. Error");

		return 1;
	}

	puts("Connected");

	memset(message, 0, 20);

    strcpy(message, "host1 3001");

    send(sock, message, strlen(message), 0);

	printf("Response: %s\n", message);

	close(sock);

}



int main(int argc , char *argv[]) {

	/*
	
	Creacion del Socket de Conexion

	*/
	
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

	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	server.sin_port = htons(3000);

	/* 
	
	Creacion del Bind  del Socket Servidor

	*/

	if(bind(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0){

		perror("Bind failed. Error");

		return 1;

	}

	puts("Bind done");
	
	/* 
	
	Apertura del Socket de Servidor

	*/

	listen(socket_desc, 3);

	puts("Waiting for incoming connections...");

	c = sizeof(struct sockaddr_in);
	
	/*

	Aceptacion de conexion desde un Socket Cliente 

	*/

	client_sock = accept(socket_desc, (struct sockaddr *) &client, (socklen_t*) &c);

	if(client_sock < 0){

		perror("Accept failed");

		return 1;

	}

	puts("Connection accepted");

	/*

	Bucle para recibir mensajes hasta que received = 1

	*/
	
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

	/*
	
	Todo lo de arriba se hace para recibir el mensaje desde el ecs_client
	
	*/

	listContainers();

	return 0;
}