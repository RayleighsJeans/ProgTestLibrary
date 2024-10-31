#pragma once


#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <assert.h>
#include <cstring>
#include <iostream>


#include "../../include/randGenerators.hpp"
#include "../../include/timer.hpp"
#include "../../include/printSuite.hpp"


#define OUT std::cout << __FILE__ << " " << __LINE__ << std::endl;


namespace network
{
template <typename PacketType>
class SimpleClient
{
 private:
  int m_clientSocket = -1;

  sockaddr_in m_address;

  unsigned int m_msTimeOut;

  PacketType m_package[4];

 public:
  SimpleClient(const unsigned int msTimeout = 10000) : m_msTimeOut(msTimeout)
  {
    OUT;
    m_clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    assert("Error opening socket." && m_clientSocket != -1);
    OUT;

    m_address.sin_family = AF_INET;
    m_address.sin_addr.s_addr = INADDR_ANY;
    m_address.sin_port = htons(8080);
    OUT;

    connect(m_clientSocket, (struct sockaddr*)&m_address, sizeof(m_address));
    OUT;

    memset(m_package, 0, sizeof(m_package));
    OUT;
  };

  ~SimpleClient() { close(m_clientSocket); };

  void start(const unsigned int msTick = 1000)
  {
    OUT;

    const size_t N = sizeof(m_package) / sizeof(PacketType);

    helper::Timer clock;
    clock.tick();
    OUT;

    helper::RandomGenerator<PacketType> gen(
      std::numeric_limits<PacketType>::min(),
      std::numeric_limits<PacketType>::max());
    OUT;

    std::vector<PacketType> container;
    OUT;
    while ((unsigned int)clock.timeSinceStart() < m_msTimeOut) {
      // OUT;
      // std::cout << clock.elapsed() << std::endl;
      if ((unsigned int)clock.elapsed() >= msTick) {
        container = gen.randomVector(N);
        std::copy(container.begin(), container.end(), m_package);

        if (m_package[0] != 0) {
          std::cout << "Message from client: ";
          for (const PacketType& entry : m_package)
            std::cout << entry << " ";
        }

        OUT;
        helper::print<char[], int>("container", container);
        std::cout << clock.elapsed() << std::endl;

        send(m_clientSocket, &m_package, N, 0);
        memset(m_package, 0, sizeof(m_package));
        clock.tick();
      }

      clock.tock(false);
    }
  }
};
} // namespace network