/*

host El host es la maquina donde se crearan los contenedores, para efectos de
prueba puede ser una maquina virtual o la maquina que tenga disponible el
estudiante.

ecs-agent Este agente es el encargado de crear, listar, detener o borrar contenedores. Este proceso solo recibe instrucciones del elastic-container-service
por medio del proceso admin_container. Como la creación de un contenedor
no todo el tiempo es inmediata, el agente recibe la petición y responde con un
status de recibido y ejecuta la acción.
Cuando un agente se inicia en un host, este debe reportarse enviando una petición al proceso subscribe_host del elastic-container-service.

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<unistd.h>	//write

int ecs_agent(){

    /*
	
	Creacion del Socket Servidor para el ecs_agent del host_1 en el localhost con el puerto 3001

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

	server.sin_port = htons(3001);

	if(bind(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0){

		perror("Bind failed. Error");

		return 1;

	}

	puts("Bind done");

	listen(socket_desc, 3);

	puts("Waiting for incoming connections...");

	c = sizeof(struct sockaddr_in);
/

	client_sock = accept(socket_desc, (struct sockaddr *) &client, (socklen_t*) &c);

	if(client_sock < 0){

		perror("Accept failed");

		return 1;

	}

	puts("Connection accepted");
	
    while(!received){

        memset(client_message, 0, 2000);

        if(recv(client_sock, client_message, 2000, 0) > 0){

            printf("received message host: %s\n", client_message);

			received = 1;

            send(client_sock, client_message, strlen(client_message), 0);

        } 
		
		else{

            puts("recv failed");

        }
		
    }

	/*
	
	Todo lo de arriba se hace para recibir el mensaje desde el ecs por medio del proceso admin_container
	
	*/

}

int main(int argc, char *argv[]) {

	ecs_agent();

	return 0;

}