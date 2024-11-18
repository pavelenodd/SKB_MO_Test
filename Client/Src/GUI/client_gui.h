#pragma once
// client_gui.h

#include <QDialog>
#include <QGraphicsScene>
#include <QSvgRenderer>
#include <QtSvgWidgets/QGraphicsSvgItem>

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
  Ui::Dialog* ui_;    // Интерфейс UI

  QGraphicsScene* background_scene_;  // Сцена для отображения SVG
  QGraphicsSvgItem* aim_image_;       // SVG-объект прицела
  QGraphicsSvgItem* red_cross_image_;  // SVG-объект креста(красного)
  QGraphicsSvgItem* black_cross_image_;  // SVG-объект креста(чёрного)

 public:
  Client_GUI(QWidget* parent);
  ~Client_GUI();
  void initGUI();
  GUI_DATA* get_Ref_DATA() { return &ui_data_; }

 private:
  void loadSVG_Images();
  void DrawCross();
};
