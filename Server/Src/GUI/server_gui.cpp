// GUI/server_gui.cpp
#include "server_gui.h"

ServerGUI::ServerGUI(QWidget* parent)
    : QDialog(parent), ui(new Ui::Dialog) {  // Инициализация указателя ui
  ui->setupUi(this);
}

ServerGUI::~ServerGUI() {
  delete ui;
}
