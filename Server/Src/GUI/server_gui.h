// GUI/server_gui.h

#pragma once

#include <QDialog>
#include "ui_server.h"
class ServerGUI : public QDialog {
  Q_OBJECT
 private:
  Ui::Dialog* ui;  // Указатель на сгенерированный UI класс

 public:
  explicit ServerGUI(QWidget* parent = nullptr);
  ~ServerGUI();
};
