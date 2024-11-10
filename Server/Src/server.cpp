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
      message_.remove(0, 15);  // Удаление данных ключа и знака :
      data_.at("camera angle") = message_.toDouble();
      sucsess_response = "The data is correct. Data is \"camera angle\" ";
      // DEBUG ^
    } else if (L_str.contains("horizontal indentation")) {
      message_.remove(0, 25);  // Удаление данных ключа и знака :
      data_.at("horizontal indentation") = message_.toDouble();
      sucsess_response =
          "The data is correct. Data is \"horizontal indentation\" ";
      // DEBUG ^
    } else if (L_str.contains("vertical indentation")) {
      message_.remove(0, 23);  // Удаление данных ключа и знака :
      data_.at("vertical indentation") = message_.toDouble();
      sucsess_response =
          "The data is correct. Data is \"vertical indentation\" ";
      // DEBUG ^
    } else {
      udp_socket_->writeDatagram(sucsess_response, sender_, sender_port_);
      message_.clear();
      sucsess_response = "The data is incorrect! ";
    }

    qDebug() << "The server received a message from the client:" << message_;

    // Отправляем ответное сообщение обратно клиенту по адресу и порту
    udp_socket_->writeDatagram(sucsess_response, sender_, sender_port_);
  }
};