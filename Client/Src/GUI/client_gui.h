#pragma once

#include <QDialog>
#include <QGraphicsScene>
#include <QSvgRenderer>
#include <QtSvgWidgets/QGraphicsSvgItem>

#include "ui_client.h"
struct GUI_DATA {
  double angle = 0.0;                   // угол
  double horizontal_indentation = 0.0;  // отступ по горизонтали
  double vertical_indentation = 0.0;  // отступ по вертикали
};

class Client_GUI : public QDialog {
  Q_OBJECT

 private:
  GUI_DATA ui_data_;  // Данные UI
  Ui::Dialog* ui_;    // Интерфейс UI

  QGraphicsScene* background_scene_;  // Сцена для отображения SVG
  QGraphicsPixmapItem* red_cross_image_;  // SVG-объект креста(красного)
  QGraphicsPixmapItem* black_cross_image_;  // SVG-объект креста(чёрного)

  // Центр сцены
  const double center_x = 200;
  const double center_y = 200;

 public:
  Client_GUI(QWidget* parent);
  ~Client_GUI();
  void initGUI();
  GUI_DATA* get_Ref_DATA() { return &ui_data_; }

  void updateCrossPositionAndAngle();

 private:
  void loadSVG_Images();
  void drawCross();
  void updateInfoLabels();

 private slots:
  void swapCross();
  void swapBackground();
};
