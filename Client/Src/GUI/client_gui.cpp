#include "client_gui.h"
// client_gui.cpp

Client_GUI::Client_GUI(QWidget* parent)
    : QDialog(parent),
      ui_(new Ui::Dialog),
      background_scene_(new QGraphicsScene(this)) {
  ui_->setupUi(this);
}

Client_GUI::~Client_GUI() {
  delete ui_;
}

void Client_GUI::initGUI() {
  // Устанавливаем сцену для отображения
  ui_->graphicsView->setScene(background_scene_);

  // Рисуем зелёный крест
  DrawCross();

  // Загружаем SVG-изображения
  // sloadSVG_Images();
}

void Client_GUI::loadSVG_Images() {
  // Создаём красный прицел
  // red_cross_image_ = new QGraphicsSvgItem("Svg/crosshair red.svg");
  if (red_cross_image_) {
    background_scene_->addItem(red_cross_image_);
    red_cross_image_->setVisible(false);  // Пока скрываем
  }

  // Создаём чёрный прицел
  // black_cross_image_ = new QGraphicsSvgItem("Svg/crosshair black.svg");
  if (black_cross_image_) {
    background_scene_->addItem(black_cross_image_);
    black_cross_image_->setVisible(false);  // Пока скрываем
  }
}

void Client_GUI::DrawCross() {
  // Размеры креста
  int scene_width = background_scene_->width();
  int scene_height = background_scene_->height();

  // Устанавливаем размер сцены
  background_scene_->setSceneRect(0, 0, scene_width, scene_height);

  // Цвет и толщина линии
  QPen pen(Qt::green);
  pen.setWidth(1);

  // Горизонтальная линия
  background_scene_->addLine(10, 50, 90, 50, pen);

  // Вертикальная линия
  background_scene_->addLine(50, 10, 50, 90, pen);
}
