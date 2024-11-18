// server.h

#pragma once
#include <QCoreApplication>
#include <QHostAddress>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QTimer>
#include <QUdpSocket>

#include "server_gui.h"
class Server : public QObject {
  Q_OBJECT
 private:
  QUdpSocket* udp_socket_;  // Обект сокета для отправки и приема сообщений
  ServerGUI gui_;           // Объект GUI
  unsigned int port_;       // Номер порта
  unsigned int delay_;  // Задержка между сообщениями 0.2сек
  QByteArray message_;        // Буфер для  сообщени
  QHostAddress sender_;       // Адрес отправителя
  quint16 sender_port_;       // Порт отправителя
  GUI_DATA* data_;            // Данные UI
  QTimer* timer_;  // Таймер отправки сообщений

 public:
  Server(QObject* parent = nullptr) {
    port_ = 8080;
    delay_ = 200;
    udp_socket_ = new QUdpSocket(this);
    gui_.show();                  // Отображаем GUI
    data_ = gui_.get_Ref_DATA();  // Получаем указатель на данные UI
    /**
     * Привязываем сокет к локальному адресу и порту
     */
    if (!udp_socket_->bind(QHostAddress::LocalHost, port_)) {
      qCritical() << "The socket could not be bound to the port. The port may "
                     "already be occupied.";
      return;
    }

    /**
     * Подключаем слот для обработки исходящих сообщений
     */
    // Таймер, который отправляет запросы клиенту
    timer_ = new QTimer(this);
    // Соединяем сигнал таймера с функцией отправки сообщения
    connect(timer_, &QTimer::timeout, this, [this]() { sendMessage(true); });

    timer_->start(delay_);
    /**
     * Слот обработки входящих данных
     */
    connect(udp_socket_, &QUdpSocket::readyRead, this,
            &Server::handleIncomingDatagrams);

    connect(gui_.get_Ref_UI()->SendPushButt, &QPushButton::clicked, this,
            [this]() { sendMessage(false); });
  }

  ~Server() { delete udp_socket_; }

 private slots:
  /**
   *\brief Метод для отправки сообщения серверу
   */
  void sendMessage(bool isConnectedMessage_);
  /**
   * \brief Обработчик входящих данных (Datagrams)
   */
  void handleIncomingDatagrams();
};
