#pragma once
// client.h

#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QTimer>
#include <QUdpSocket>
#include "GUI/client_gui.h"

class Client : public QObject {
  Q_OBJECT
 private:
  Client_GUI* gui_;
  QUdpSocket* udp_socket_;  // Обект сокета для отправки и приема сообщений
  unsigned int port_ = 8080;  // Номер порта
  unsigned int delay_ = 200;  // Задержка между пингом коннекта  0.2сек
  QByteArray message_;  // Буфер для  сообщени
  GUI_DATA* data_;      // Данные UI
  QTimer* timer_;  // Таймер, который отправляет запросы на сервер

 public:
  Client(QObject* parent = nullptr) : QObject(parent) {
    udp_socket_ = new QUdpSocket(this);

    // Создаем и отображаем GUI
    gui_ = new Client_GUI(nullptr);
    gui_->show();
    gui_->initGUI();
    data_ = gui_->get_Ref_DATA();

    // Подключаем слот для обработки входящих сообщений
    connect(udp_socket_, &QUdpSocket::readyRead, this, &Client::handleResponse);

    // Таймер, который отправляет запросы на сервер
    timer_ = new QTimer(this);

    // Соединяем сигнал таймера с функцией отправки сообщения
    connect(timer_, &QTimer::timeout, this, &Client::sendMessage);

    timer_->start(delay_);
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
