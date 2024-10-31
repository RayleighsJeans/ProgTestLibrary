#pragma once


#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <assert.h>
#include <cstring>
#include <iostream>


#include "../../include/printSuite.hpp"
#include "../../include/randGenerators.hpp"
#include "../../include/timer.hpp"


#define OUT std::cout << __FILE__ << " " << __LINE__ << std::endl;


namespace network
{
template <typename PacketType>
class SimpleClient
{
 private:
  size_t m_counter = 0;
  int m_clientSocket = -1;
  unsigned int m_msTimeOut;

  sockaddr_in m_address;

  PacketType m_package[4];

 public:
  SimpleClient(const unsigned int msTimeout = 10000) : m_msTimeOut(msTimeout)
  {
    m_clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    assert("Error opening socket." && m_clientSocket != -1);

    m_address.sin_family = AF_INET;
    m_address.sin_addr.s_addr = INADDR_ANY;
    m_address.sin_port = htons(8080);

    connect(m_clientSocket, (struct sockaddr*)&m_address, sizeof(m_address));
    memset(m_package, 0, sizeof(m_package));
  };

  ~SimpleClient()
  {
    std::cout << "Packets sent: " << m_counter << std::endl;
    close(m_clientSocket);
  };

  void start(const unsigned int msTick = 1000)
  {
    const size_t N = sizeof(m_package) / sizeof(PacketType);

    helper::Timer clock;
    clock.tick();

    helper::RandomGenerator<PacketType> gen(
      std::numeric_limits<PacketType>::min(),
      std::numeric_limits<PacketType>::max());

    std::vector<PacketType> container(N);
    while ((unsigned int)clock.timeSinceStart() < m_msTimeOut) {
      if ((unsigned int)clock.elapsed() >= msTick) {
        container = gen.randomVector(N);
        std::copy(container.begin(), container.end(), m_package);

        if (m_package[0] != 0) {
          std::cout << "Packet sent: ";
          for (const PacketType& entry : m_package)
            std::cout << entry << " ";
        }

        send(m_clientSocket, &m_package, N, 0);
        m_counter++;
        memset(m_package, 0, sizeof(m_package));
        clock.tick();
      }

      clock.tock(false);
    }
  }
};
} // namespace network