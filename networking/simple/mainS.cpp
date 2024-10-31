#include "tcpServer.hpp"

int main()
{
  using namespace network;

  SimpleServer<int> server;
  server.start();

  return 0;
}