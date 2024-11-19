#pragma once

#include <QDialog>
#include "ui_server.h"
struct GUI_DATA {
  double angle = 0.0;                   // Угол
  double horizontal_indentation = 0.0;  // горизонтальное смещение
  double vertical_indentation = 0.0;  // вертикальное смещение
};
class ServerGUI : public QDialog {
  Q_OBJECT

 private:
  GUI_DATA ui_data_;  // Данные UI
  Ui::Dialog* ui_;  // Указатель на сгенерированный UI класс

 public:
  explicit ServerGUI(QWidget* parent = nullptr);

  ~ServerGUI();

  GUI_DATA* get_Ref_DATA();
  Ui::Dialog* get_Ref_UI() const;

 private slots:

  void onAngleSliderValueChanged(double L_value);

  void onHorizontalSliderValueChanged(double L_value);

  void onVerticalSliderValueChanged(double L_value);
};
