#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char** argv) {
    // address to connect to (provided as cmd argument)
    char* address;
    address = argv[1];
    
    // create a socket 
    int client_socket;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // specify an address to connect to in more details
    struct sockaddr_in remote_address;
    remote_address.sin_family = AF_INET;
    remote_address.sin_port = htons(80); // most web servers are on port 80
    inet_aton(address, &remote_address.sin_addr.s_addr); // convert char* address to a proper format address structure
    
    // connect to a remote address
    connect(client_socket, (struct sockaddr*)&remote_address, sizeof(remote_address));
    
    // specify HTTP GET method & what resource we're gonna get
    char request[] = "GET / HTTP/1.1\r\n\r\n";
    char response[4096];

    // send an http request
    send(client_socket, request, sizeof(request), 0);

    // recieve a response
    recv(client_socket, &response, sizeof(response), 0);
    
    // print received data
    printf("response from server: %s\n", response);

    // close the socket
    close(client_socket);

    return 0;
}
