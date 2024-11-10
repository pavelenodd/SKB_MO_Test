// server.h

#pragma once
#include <QCoreApplication>
#include <QHostAddress>
#include <QString>
#include <QUdpSocket>
#include <map>
#include "server_gui.h"

class Server : public QObject {
  Q_OBJECT
 private:
  QUdpSocket* udp_socket_;  // Обект сокета для отправки и приема сообщений
  ServerGUI server_gui_;    // Объект GUI
  unsigned int port_ = 8080;  // Номер порта
  QByteArray message_;        // Буфер для  сообщени
  QHostAddress sender_;       // Адрес отправителя
  quint16 sender_port_;       // Порт отправителя

  std::map<QString, double> data_ = {
      {"camera angle", 0},  // угол камеры по горизонтали
      {"horizontal indentation", 0},  // отступ по горизонтали
      {"vertical indentation", 0}     // отступ по вертикали
  };

 public:
  Server(QObject* parent = nullptr) {
    udp_socket_ = new QUdpSocket(this);
    server_gui_.show();  // Отображаем GUI
    /**
     * Привязываем сокет к локальному адресу и порту
     */
    if (!udp_socket_->bind(QHostAddress::LocalHost, port_)) {
      qCritical() << "The socket could not be bound to the port. The port may "
                     "already be occupied.";
      return;
    }

    /**
     * Слот обработки входящих данных
     */
    connect(udp_socket_, &QUdpSocket::readyRead, this,
            &Server::handleIncomingDatagrams);
  }

  ~Server() { delete udp_socket_; }

 signals:
  void dataReceived(const QString& key,
                    double value);  // Сигнал для передачи данных GUI

 private slots:

  /**
   * \brief Обработчик входящих данных (Datagrams)
   */
  void handleIncomingDatagrams();
};
