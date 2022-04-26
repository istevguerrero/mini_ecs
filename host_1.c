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

int wakeContainers(){

    


}

int main(int argc, char *argv[]) {

	int sock, socket_desc, client_sock, c, read_size;

	struct sockaddr_in server, client;

	char message[1000], server_reply[2000];

	sock = socket(AF_INET, SOCK_STREAM, 0);

	if(sock == -1){

		printf("Could not create socket");

	}

	puts("Socket created");
	
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	server.sin_family = AF_INET;

	server.sin_port = htons(3001);

	if(connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0){

		perror("Connect failed. Error");

		return 1;

	}
	
	puts("Connected\n");

    memset(message, 0, 20 );

    strcpy(message, "host1 3001");

    send(sock, message, strlen(message), 0);

    close(sock);

    socket_desc = socket(AF_INET , SOCK_STREAM , 0);

    server.sin_family = AF_INET;

	server.sin_addr.s_addr = INADDR_ANY;

	server.sin_port = htons(3000);

	if(bind(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0){

		//print the error message

		perror("Bind failed. Error");

		return 1;

	}

	puts("Bind done");

    while(1){

        listen(socket_desc, 3);

        puts("Waiting for incoming connections...");

        c = sizeof(struct sockaddr_in);

        client_sock = accept(socket_desc, (struct sockaddr *) &client, (socklen_t*) &c);

        if(client_sock < 0){

            perror("Accept failed");

            return 1;

        }

        wakeContainers();

        //EJECUTAR LA COSA DE LOS CONTENEDORES



    }


}

