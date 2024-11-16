#include "client_gui.h"
// client_gui.cpp

Client_GUI::Client_GUI(QWidget* parent) : QDialog(parent), ui_(new Ui::Dialog) {
  ui_->setupUi(this);
}

Client_GUI::~Client_GUI() {
  delete ui_;
}
