#pragma once
// client_gui.h

#include <QDialog>
#include "ui_client.h"
struct GUI_DATA {
  double angle = 0.0;
  double horizontal_indentation = 0.0;
  double vertical_indentation = 0.0;
};

// Объявление класса Client_GUI
class Client_GUI : public QDialog {
  Q_OBJECT

 private:
  GUI_DATA ui_data_;  // Данные UI
  Ui::Dialog* ui_;

 public:
  Client_GUI(QWidget* parent);
  ~Client_GUI();
};
