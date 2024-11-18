#include "client.h"
// client.cpp

void Client::sendMessage() {
  /* отправка отладочного сообщения об успешном получении */
  message_ = "CONNECT";
  udp_socket_->writeDatagram(message_, QHostAddress::LocalHost, port_);
};

void Client::handleResponse() {
  while (udp_socket_->hasPendingDatagrams()) {
    QByteArray datagram;
    datagram.resize(udp_socket_->pendingDatagramSize());
    udp_socket_->readDatagram(datagram.data(), datagram.size());

    if (datagram.contains("ACK")) {
      // если сообщение начинается с ACK то это отладочное сообщение
      // подтверждения соединения
      qDebug() << "Debug: The client received a response from the server:"
               << message_;
      // Останавливаем таймер, так как подключение подтверждено
      if (timer_->isActive()) {
        timer_->stop();
        qDebug() << "Timer stopped after successful connection.";
      }
    } else {
      // Преобразуем данные из JSON
      QJsonDocument json_doc = QJsonDocument::fromJson(datagram);
      if (json_doc.isObject()) {
        QJsonObject json_obj = json_doc.object();
        data_->angle = json_obj["camera_angle"].toDouble();
        data_->horizontal_indentation =
            json_obj["horizontal_indentation"].toDouble();
        data_->vertical_indentation =
            json_obj["vertical_indentation"].toDouble();

        qDebug() << "Received JSON data:";
        qDebug() << "Camera angle:" << data_->angle;
        qDebug() << "Horizontal indentation:" << data_->horizontal_indentation;
        qDebug() << "Vertical indentation:" << data_->vertical_indentation;

      } else {
        qWarning() << "Invalid data received!";
      }
    }
  }
};