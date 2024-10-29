#pragma once


#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <assert.h>
#include <cstring>
#include <iostream>

#include "../../include/timer.hpp"


template <typename PacketType>
class SimpleServer
{
 private:
  int m_serverSocket = -1;
  int m_clientSocket = -1;

  sockaddr_in m_address;

  PacketType m_buffer[1024];

 public:
  SimpleServer(const size_t msTimeout)
  {
    m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    assert("Error opening socket." && m_serverSocket != -1);

    m_address.sin_family = AF_INET;
    m_address.sin_addr.s_addr = INADDR_ANY;
    m_address.sin_port = htons(4000);

    assert("Error binding socket." &&
           bind(m_serverSocket, (struct sockaddr*)&m_address,
                sizeof(m_address)) != -1);

    listen(m_serverSocket, 1);

    m_clientSocket = accept(m_serverSocket, NULL, NULL);
    memset(m_buffer, 0, sizeof(m_buffer));
  }

  void start()
  {
    while (true) {
      memset(m_buffer, 0, sizeof(m_buffer));
      recv(m_clientSocket, m_buffer, sizeof(m_buffer), 0);
      std::cout << "Message from client: " << m_buffer;
    }

    close(server_socket);
  }
};