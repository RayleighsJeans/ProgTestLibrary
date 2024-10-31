#pragma once


#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <assert.h>
#include <cstring>
#include <iostream>

#include "../../include/timer.hpp"


#define OUT std::cout << __FILE__ << " " << __LINE__ << std::endl;


namespace network
{
template <typename PacketType>
class SimpleServer
{
 private:
  size_t m_counter = 0;

  int m_serverSocket = -1;
  int m_clientSocket = -1;

  unsigned int m_msTimeOut;

  sockaddr_in m_address;

  PacketType m_buffer[16];

 public:
  SimpleServer(const unsigned int msTimeout = 10000) : m_msTimeOut(msTimeout)
  {
    m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    assert("Error opening socket." && m_serverSocket != -1);

    m_address.sin_family = AF_INET;
    m_address.sin_addr.s_addr = INADDR_ANY;
    m_address.sin_port = htons(8080);

    assert("Error binding socket." &&
           bind(m_serverSocket, (struct sockaddr*)&m_address,
                sizeof(m_address)) != -1);

    listen(m_serverSocket, 1);

    m_clientSocket = accept(m_serverSocket, NULL, NULL);
    fcntl(m_clientSocket, F_SETFL, O_NONBLOCK);
    memset(m_buffer, 0, sizeof(m_buffer));
  }

  ~SimpleServer()
  {
    std::cout << "Packets received: " << m_counter << std::endl;
    close(m_serverSocket);
  };

  void start()
  {
    helper::Timer clock;
    clock.tick();

    while ((unsigned int)clock.timeSinceStart() < m_msTimeOut) {
      memset(m_buffer, 0, sizeof(m_buffer));
      recv(m_clientSocket, m_buffer, sizeof(m_buffer), 0);

      if (m_buffer[0] != 0) {
        m_counter++;
        std::cout << "Packet from client: ";
        for (const PacketType& entry : m_buffer)
          std::cout << entry << " ";
        std::cout << std::endl;
      }

      clock.tock(false);
    }
  }
};
} // namespace network