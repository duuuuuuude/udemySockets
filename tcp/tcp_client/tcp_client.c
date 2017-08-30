#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>

int main() {
    // Create a socket
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    // specify an address for the socket to connect to (it's gonna be on local machine)
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // connect to a server 
    int connection_status = connect(network_socket, (struct sockaddr*)&server_address, sizeof(server_address));
    
    if (connection_status < 0) {
        printf("There was an error making a connection to the remote socket(server)\n\n");
    }
    
    // receive data from the server
    char server_response[256];
    recv(network_socket, &server_response, sizeof(server_response), 0);

    // printing out the server's response
    printf("The server sent the data: %s\n", server_response);
    
    // and then close the socket
    close(network_socket);
    return 0;
}


