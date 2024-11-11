// GUI/server_gui.h
#pragma once

#include <QDialog>
#include "ui_server.h"
struct GUI_DATA {
  double angle = 0.0;
  double horizontal_indentation = 0.0;
  double vertical_indentation = 0.0;
};
class ServerGUI : public QDialog {
  Q_OBJECT

 private:
  GUI_DATA ui_data_ = {3.5, 0, 0};  // Данные UI
  Ui::Dialog* ui;  // Указатель на сгенерированный UI класс

 public:
  explicit ServerGUI(QWidget* parent = nullptr);

  ~ServerGUI();
  /**
   * @brief Возвращает указатель данные UI
   */
  GUI_DATA* get_Ref_DATA() { return &ui_data_; }

 private slots:

  void onAngleSliderValueChanged(double L_value);

  void onHorizontalSliderValueChanged(double L_value);

  void onVerticalSliderValueChanged(double L_value);
};

