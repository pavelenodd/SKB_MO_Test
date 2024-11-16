#include "client.h"
// client.cpp

void Client::sendMessage() {
  if (!message_.isEmpty()) {
    /* code */

    // Тестовые сообщения для отправки
    QByteArray test_message = "camera angle: 1";
    QByteArray test_message1 = "horizontal indentation: 5";
    QByteArray test_message2 = "horizontal indentation: 9";

    // Отправляем сообщение на локальный адрес и порт, где запущен сервер
    udp_socket_->writeDatagram(test_message, QHostAddress::LocalHost, port_);
    udp_socket_->writeDatagram(test_message1, QHostAddress::LocalHost, port_);
    udp_socket_->writeDatagram(test_message2, QHostAddress::LocalHost, port_);
  }
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