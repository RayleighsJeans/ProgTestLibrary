#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

int main()
{
  std::cout << "Starting the Client ..." << std::endl;
  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket == -1) {
    std::cerr << "Error creating the socket ..." << std::endl;
  }
  sockaddr_in clientAddr;
  clientAddr.sin_family = AF_INET;
  clientAddr.sin_port = htons(4000);
  clientAddr.sin_addr.s_addr = INADDR_ANY;

  connect(client_socket, (struct sockaddr*)&clientAddr, sizeof(clientAddr));

  char mess[1024];
  while (true) {
    std::cout << "Enter the message to send : ";
    fgets(mess, sizeof(mess), stdin);
    send(client_socket, &mess, strlen(mess), 0);
    if (strcmp(mess, "exit\n") == 0)
      break;
    memset(mess, 0, sizeof(mess));
  }
  close(client_socket);
  return (0);
}