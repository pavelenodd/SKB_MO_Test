#include "Client/client.h"
#include "Server/server.h"

int main(int argc, char* argv[]) {
  QCoreApplication app(argc, argv);

  Server server;
  Client client;

  return app.exec();
}
