// server.cpp

#include "server.h"

void Server::handleIncomingDatagrams() {
  QByteArray sucsess_response;  // сообщение клиенту о получении сообщения
  while (udp_socket_->hasPendingDatagrams()) {
    message_.resize(udp_socket_->pendingDatagramSize());

    // TODO перевести в отдельный метод
    //  Читаем сообщение и сохраняем адрес отправителя и порт
    udp_socket_->readDatagram(message_.data(), message_.size(), &sender_,
                              &sender_port_);

    if (message_.contains("CONNECT")) {
      // если сообщение начинается с CONNECT то это отладочное сообщение
      // подтверждения соединения
      sucsess_response = "ACK";
      qDebug() << "Connection acknowledged from" << sender_.toString() << ":"
               << sender_port_;  // Останавливаем таймер, так как подключение
                                 // подтверждено
      if (timer_->isActive()) {
        timer_->stop();
        qDebug() << "Timer stopped after successful connection.";
      }
    }

    else {
      udp_socket_->writeDatagram(sucsess_response, sender_, sender_port_);
      message_.clear();
      sucsess_response = "The data is incorrect! " + message_;
    }

    // Отправляем ответное сообщение обратно клиенту по адресу и порту
    udp_socket_->writeDatagram(sucsess_response, sender_, sender_port_);
  }
};
void Server::sendMessage(bool isConnectedMessage_) {
  if (isConnectedMessage_) {
    message_ = "ACK";
    udp_socket_->writeDatagram(message_, sender_, sender_port_);
  } else {
    QJsonObject json_data;
    json_data["camera_angle"] = data_->angle;
    json_data["horizontal_indentation"] = data_->horizontal_indentation;
    json_data["vertical_indentation"] = data_->vertical_indentation;

    // Преобразуем JSON объект в строку JSON
    QJsonDocument json_doc(json_data);
    QByteArray json_bytes = json_doc.toJson(QJsonDocument::Compact);

    // Отправляем JSON данные клиенту
    udp_socket_->writeDatagram(json_bytes, sender_, sender_port_);
  }
}