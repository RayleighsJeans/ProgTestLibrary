#include "tcpClient.hpp"

int main()
{
  using namespace network;

  SimpleClient<int> client;
  client.start();

  return 0;
}