#include "client.h"

Client::Client(QObject* parent = nullptr) : QObject(parent) {
  udp_socket_ = new QUdpSocket(this);
  port_ = 8080;
  delay_ = 200;
  // Создаем и отображаем GUI
  gui_ = new Client_GUI(nullptr);
  gui_->show();
  gui_->initGUI();
  data_ref_ = gui_->get_Ref_DATA();

  // Подключаем слот для обработки входящих сообщений
  connect(udp_socket_, &QUdpSocket::readyRead, this, &Client::handleResponse);

  // Таймер, который отправляет запросы на сервер
  timer_ = new QTimer(this);

  // Соединяем сигнал таймера с функцией отправки сообщения
  connect(timer_, &QTimer::timeout, this, &Client::sendMessage);
  timer_->start(delay_);
};

Client::~Client() {
  delete udp_socket_;
  delete gui_;
}
/**
 * \brief Метод для отправки сообщения серверу
 */
void Client::sendMessage() {
  // INFO отправка отладочного сообщения об успешном получении
  message_ = "CONNECT";
  udp_socket_->writeDatagram(message_, QHostAddress::LocalHost, port_);
};
/**
 * \brief Обработчик входящих данных (ответа от сервера)
 */
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
      QJsonDocument json_doc = QJsonDocument::fromJson(datagram);
      if (json_doc.isObject()) {
        QJsonObject json_obj = json_doc.object();
        data_ref_->angle = json_obj["camera_angle"].toDouble();
        data_ref_->horizontal_indentation =
            json_obj["horizontal_indentation"].toDouble();
        data_ref_->vertical_indentation =
            json_obj["vertical_indentation"].toDouble();

        qDebug() << "Received JSON data:";
        qDebug() << "Camera angle:" << data_ref_->angle;
        qDebug() << "Horizontal indentation:"
                 << data_ref_->horizontal_indentation;
        qDebug() << "Vertical indentation:" << data_ref_->vertical_indentation;

        gui_->updateCrossPositionAndAngle();

      } else {
        qWarning() << "Invalid data received!";
      }
    }
  }
};