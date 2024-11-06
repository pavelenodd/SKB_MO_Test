#include "server.h"

void Server::handleIncomingDatagrams() {
  while (udp_socket_->hasPendingDatagrams()) {
    message_.resize(udp_socket_->pendingDatagramSize());

    // Читаем сообщение и сохраняем адрес отправителя и порт
    udp_socket_->readDatagram(message_.data(), message_.size(), &sender_,
                              &sender_port_);

    qDebug() << "The server received a message from the client:" << message_;

    // Тестовое ответное сообщение
    QByteArray test_response = "Response from the server";

    // Отправляем ответное сообщение обратно клиенту по указанному адресу и
    // порту
    udp_socket_->writeDatagram(test_response, sender_, sender_port_);
  }
};