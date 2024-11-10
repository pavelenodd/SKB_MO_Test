// main.cpp

#include <QApplication>
#include <QThread>
#include "server.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  Server server;

  return app.exec();
}
