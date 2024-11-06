#pragma once
#include <QCoreApplication>
#include <QHostAddress>
#include <QUdpSocket>

class Server : public QObject {
  Q_OBJECT
 private:
  QUdpSocket* udp_socket_;  // Обект сокета для отправки и приема сообщений
  unsigned int port_ = 8080;  // Номер порта
  QByteArray message_;        // Буфер для  сообщени
  QHostAddress sender_;       // Адрес отправителя
  quint16 sender_port_;       // Порт отправителя

 public:
  Server(QObject* parent = nullptr) {
    udp_socket_ = new QUdpSocket(this);

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

 private slots:

  /**
   * \brief Обработчик входящих данных (Datagrams)
   */
  void handleIncomingDatagrams();
};
