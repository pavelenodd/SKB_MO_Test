// main.cpp для клиента

#include <QApplication>
#include "client.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  Client client;

  return app.exec();
}
