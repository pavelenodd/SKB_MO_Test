// GUI/server_gui.cpp
#include "server_gui.h"
#include <QDebug>

ServerGUI::ServerGUI(QWidget* parent) : QDialog(parent), ui_(new Ui::Dialog) {
  ui_->setupUi(this);

  // INFO Зона подключения сигналов
  connect(ui_->AngleSlider, &QSlider::valueChanged, this,
          &ServerGUI::onAngleSliderValueChanged);
  connect(ui_->HorizSlider, &QSlider::valueChanged, this,
          &ServerGUI::onHorizontalSliderValueChanged);
  connect(ui_->VertSlider, &QSlider::valueChanged, this,
          &ServerGUI::onVerticalSliderValueChanged);

  // INFO Устанавливаем начальное значения UI
  ui_->AngleSliderDATA->setText(QString::number(ui_data_.angle));
  ui_->HorizDATA->setText(QString::number(ui_data_.horizontal_indentation));
  ui_->VertDATA->setText(QString::number(ui_data_.vertical_indentation));
}

ServerGUI::~ServerGUI() {
  delete ui_;
}
/**
 * @brief Слот для передачи данных AngleSliderDATA
 * @param L_value Значение слайдера
 *
 */
void ServerGUI::onAngleSliderValueChanged(double L_value) {
  ui_data_.angle = (L_value / 10);
  ui_->AngleSliderDATA->setText(QString::number(ui_data_.angle));
}
/**
 * @brief Слот для передачи данных HorizDATA
 * @param L_value Значение слайдера
 */
void ServerGUI::onHorizontalSliderValueChanged(double L_value) {
  ui_data_.horizontal_indentation = (L_value / 100);
  ui_->HorizDATA->setText(QString::number(ui_data_.horizontal_indentation));
}
/**
 * @brief Слот для передачи данных VertDATA
 * @param L_value Значение слайдера
 */
void ServerGUI::onVerticalSliderValueChanged(double L_value) {
  ui_data_.vertical_indentation = (L_value / 100);
  ui_->VertDATA->setText(QString::number(ui_data_.vertical_indentation));
}