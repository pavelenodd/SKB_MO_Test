#pragma once

#include <QCoreApplication>
#include <QString>
#include <QTimer>
#include <QUdpSocket>
#include <map>

class Client : public QObject {
  Q_OBJECT
 private:
  QUdpSocket* udp_socket_;  // Обект сокета для отправки и приема сообщений
  unsigned int port_ = 8080;  // Номер порта
  unsigned int delay_ = 2000;  // Задержка между отправкой сообщений 2сек
  QByteArray message_ = "tws";  // Буфер для  сообщени
  std::map<QString, double> data_ = {
      {"camera angle", 0},  // угол камеры по горизонтали
      {"horizontal indentation", 0},  // отступ по горизонтали
      {"vertical indentation", 0}     // отступ по вертикали
  };

 public:
  Client(QObject* parent = nullptr) : QObject(parent) {
    udp_socket_ = new QUdpSocket(this);

    // Подключаем слот для обработки входящих сообщений
    connect(udp_socket_, &QUdpSocket::readyRead, this, &Client::handleResponse);

    // Таймер, который отправлять запрос на сервер
    QTimer* timer = new QTimer(this);

    // Соединяем сигнал таймера с функцией отправки сообщения
    connect(timer, &QTimer::timeout, this, &Client::sendMessage);

    timer->start(delay_);
  }
  ~Client() { delete udp_socket_; }
 private slots:

  /**
   *\brief Метод для отправки сообщения серверу
   */
  void sendMessage();

  /**
   *\brief Обработчик входящих данных (ответа от сервера)
   */
  void handleResponse();
};
