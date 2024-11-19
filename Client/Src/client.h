#pragma once

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
  Client_GUI* gui_;         // gui-объект клиента
  QUdpSocket* udp_socket_;  // Обект сокета для отправки и приема сообщений
  unsigned int port_;       // Номер порта
  unsigned int delay_;  // Задержка между пингом коннекта  0.2сек
  QByteArray message_;  // Буфер для  сообщени
  GUI_DATA* data_ref_;  // Данные UI
  QTimer* timer_;  // Таймер, который отправляет запросы на сервер

 public:
  Client(QObject* parent = nullptr);
  ~Client();
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
