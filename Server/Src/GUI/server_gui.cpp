// GUI/server_gui.cpp
#include "server_gui.h"
#include <QDebug>

ServerGUI::ServerGUI(QWidget* parent) : QDialog(parent), ui(new Ui::Dialog) {
  ui->setupUi(this);

  // INFO Зона подключения сигналов
  connect(ui->AngleSlider, &QSlider::valueChanged, this,
          &ServerGUI::onAngleSliderValueChanged);
  connect(ui->HorizSlider, &QSlider::valueChanged, this,
          &ServerGUI::onHorizontalSliderValueChanged);
  connect(ui->VertSlider, &QSlider::valueChanged, this,
          &ServerGUI::onVerticalSliderValueChanged);

  // INFO Устанавливаем начальное значения UI
  ui->AngleSliderDATA->setText(QString::number(ui_data_.angle));
  ui->HorizDATA->setText(QString::number(ui_data_.horizontal_indentation));
  ui->VertDATA->setText(QString::number(ui_data_.vertical_indentation));
}

ServerGUI::~ServerGUI() {
  delete ui;
}
/**
 * @brief Слот для передачи данных AngleSliderDATA
 * @param L_value Значение слайдера
 *
 */
void ServerGUI::onAngleSliderValueChanged(double L_value) {
  ui_data_.angle = (L_value / 10);
  ui->AngleSliderDATA->setText(QString::number(ui_data_.angle));
}
/**
 * @brief Слот для передачи данных HorizDATA
 * @param L_value Значение слайдера
 */
void ServerGUI::onHorizontalSliderValueChanged(double L_value) {
  ui_data_.horizontal_indentation = (L_value / 100);
  ui->HorizDATA->setText(QString::number(ui_data_.horizontal_indentation));
}
/**
 * @brief Слот для передачи данных VertDATA
 * @param L_value Значение слайдера
 */
void ServerGUI::onVerticalSliderValueChanged(double L_value) {
  ui_data_.vertical_indentation = (L_value / 100);
  ui->VertDATA->setText(QString::number(ui_data_.vertical_indentation));
}