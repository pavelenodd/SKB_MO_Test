#include "client_gui.h"
// client_gui.cpp

#include <QtSvgWidgets/QSvgWidget>

Client_GUI::Client_GUI(QWidget* parent)
    : QDialog(parent),
      ui_(new Ui::Dialog),
      background_scene_(new QGraphicsScene(this)) {
  ui_->setupUi(this);
};

Client_GUI::~Client_GUI() {
  delete ui_;
};

void Client_GUI::initGUI() {
  // Устанавливаем сцену для отображения
  ui_->graphicsView->setScene(background_scene_);

  // Рисуем зелёный крест
  DrawCross();

  // Загружаем SVG-изображения
  loadSVG_Images();
};

void Client_GUI::loadSVG_Images() {
  QSvgRenderer* red_renderer =
      new QSvgRenderer(QStringLiteral(":/crosshair_red.svg"), this);
  QSvgRenderer* black_renderer =
      new QSvgRenderer(QStringLiteral(":/crosshair_black.svg"), this);

  if (red_renderer->isValid() && black_renderer->isValid()) {
    // Размеры сцены и позиции креста
    int scene_width = background_scene_->width();
    int scene_height = background_scene_->height();

    // Центр перекрестья
    int cross_center_x =
        50;  // Центр перекрестья по горизонтали (как в DrawCross)
    int cross_center_y =
        50;  // Центр перекрестья по вертикали (как в DrawCross)

    // Размеры перекрестья
    QSize cross_size(200, 200);  // Размер области перекрестья (ширина и высота)

    // Создаем прозрачные QPixmap для рендеринга SVG
    QPixmap red_pixmap(cross_size);
    red_pixmap.fill(Qt::transparent);

    QPixmap black_pixmap(cross_size);
    black_pixmap.fill(Qt::transparent);

    QPainter red_painter(&red_pixmap);
    QPainter black_painter(&black_pixmap);

    // Отрисовываем SVG, масштабируя его на размер перекрестья
    red_renderer->render(&red_painter,
                         QRectF(0, 0, cross_size.width(), cross_size.height()));
    black_renderer->render(
        &black_painter, QRectF(0, 0, cross_size.width(), cross_size.height()));

    // Устанавливаем QGraphicsPixmapItem для сцены
    QGraphicsPixmapItem* red_item =
        new QGraphicsPixmapItem(QPixmap::fromImage(red_pixmap.toImage()));
    red_item->setOffset(
        cross_center_x - cross_size.width() / 2,
        cross_center_y - cross_size.height() / 2);  // Центрируем

    QGraphicsPixmapItem* black_item =
        new QGraphicsPixmapItem(QPixmap::fromImage(black_pixmap.toImage()));
    black_item->setOffset(
        cross_center_x - cross_size.width() / 2,
        cross_center_y - cross_size.height() / 2);  // Центрируем

    // Добавляем элементы на сцену
    background_scene_->addItem(red_item);
    background_scene_->addItem(black_item);
  }
};

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
};
