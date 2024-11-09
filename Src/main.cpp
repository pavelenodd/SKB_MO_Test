#include <QThread>
#include "Client/client.h"
#include "Server/server.h"

int main(int argc, char* argv[]) {
  QCoreApplication app(argc, argv);

  Server server;
  // остановка на 2 сек
  QThread::sleep(2);

  Client client;

  return app.exec();
}
