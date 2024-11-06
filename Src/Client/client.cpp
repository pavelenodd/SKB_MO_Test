#include "client.h"

void Client::sendMessage() {
  // Тестовое сообщение для отправки
  QByteArray test_message = "Request from the client";

  // Отправляем сообщение на локальный адрес и порт, где запущен сервер
  udp_socket_->writeDatagram(test_message, QHostAddress::LocalHost, port_);

  qDebug() << "The client sent a message to the server:" << test_message;
};
void Client::handleResponse() {
  while (udp_socket_->hasPendingDatagrams()) {
    // Буфер для хранения полученного ответа
    message_.resize(udp_socket_->pendingDatagramSize());

    // Читаем ответ и сохраняем его в буфер
    udp_socket_->readDatagram(message_.data(), message_.size());

    qDebug() << "The client received a response from the server:" << message_;
  }
};