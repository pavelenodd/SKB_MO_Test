#include "Client/client.h"
#include "Server/server.h"

int main(int argc, char* argv[]) {
  QCoreApplication app(argc, argv);

  Server server;
  // остановка на 2 сек
  // TODO надо сделать задержку на время запуска сервера
  Client client;

  return app.exec();
}
