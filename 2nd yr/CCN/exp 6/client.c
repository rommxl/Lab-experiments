// Client side C/C++ program to demonstrate Socket
// programming
#include <Winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

int main(int argc, char const* argv[])
{
	int status, valread, client_fd=0;
	struct sockaddr_in serv_addr;
	//char* hello = "Hello from client";
	char buffer[1024] = { 0 };
	int num1, num2, sum;
	if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
  
    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
        <= 0) {
        printf(
            "\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if ((status
         = connect(client_fd, (struct sockaddr*)&serv_addr,
                   sizeof(serv_addr)))
        < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

	//sending two numbers
	printf("Enter the first number: ");
	scanf("%d",&num1);
	printf("Enter the second number: ");
	scanf("%d",&num2);
	sprintf(buffer, "%d %d", num1, num2);

	send(client_fd, buffer, strlen(buffer), 0);
	//printf("Hello message sent\n");
	valread = read(client_fd, buffer, 1024);
	sum=atoi(buffer);
	//printf("%s\n", buffer);
	printf("Sum is: %d",sum);

	// closing the connected socket
	close(client_fd);
	return 0;
}

