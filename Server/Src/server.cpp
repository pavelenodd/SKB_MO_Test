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
    QString L_str = message_;

    if (L_str.contains("camera angle")) {
      message_.remove(0, 14);  // Удаление данных ключа и знака :
      data_->angle = message_.toDouble();
      sucsess_response = "Data is \"camera angle\" " + message_;
      // DEBUG ^
    } else if (L_str.contains("horizontal indentation")) {
      message_.remove(0, 24);  // Удаление данных ключа и знака :
      data_->horizontal_indentation = message_.toDouble();
      sucsess_response = "Data is \"horizontal indentation\" " + message_;
      // DEBUG ^
    } else if (L_str.contains("vertical indentation")) {
      message_.remove(0, 22);  // Удаление данных ключа и знака :
      data_->vertical_indentation = message_.toDouble();
      sucsess_response = "Data is \"vertical indentation\" " + message_;
      // DEBUG ^
    } else {
      udp_socket_->writeDatagram(sucsess_response, sender_, sender_port_);
      message_.clear();
      sucsess_response = "The data is incorrect! " + message_;
    }

    // Отправляем ответное сообщение обратно клиенту по адресу и порту
    udp_socket_->writeDatagram(sucsess_response, sender_, sender_port_);
  }
};