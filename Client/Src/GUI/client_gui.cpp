#include "client_gui.h"

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

  // INFO Устанавливаем начальное значения UI выбора цвета фона
  ui_->BackgroundColorCombBox->addItem("Белый");
  ui_->BackgroundColorCombBox->addItem("Чёрный");
  ui_->BackgroundColorCombBox->addItem("Серый");
  // Устанавливаем белый фон как начальный
  background_scene_->setBackgroundBrush(Qt::white);

  // INFO Устанавливаем начальное значения UI выбора цвета креста
  ui_->CrossColorCombBox->addItem("Красный");
  ui_->CrossColorCombBox->addItem("Чёрный");

  // INFO Зона подключения сигналов
  // Коннект смены цвета фона
  connect(ui_->BackgroundColorCombBox, &QComboBox::currentIndexChanged, this,
          swapBackground);
  // Коннект смены цвета креста
  connect(ui_->CrossColorCombBox, &QComboBox::currentIndexChanged, this,
          swapCross);

  drawCross();

  loadSVG_Images();
};
/**
 * \brief Загрузка SVG-объектов(крестов) и установка их на сцене
 */
void Client_GUI::loadSVG_Images() {
  // Создаем рендереры SVG
  QSvgRenderer* renderer_red_cross =
      new QSvgRenderer(QStringLiteral(":/crosshair_red.svg"), this);
  QSvgRenderer* renderer_black_cross =
      new QSvgRenderer(QStringLiteral(":/crosshair_black.svg"), this);

  if (!renderer_red_cross->isValid() || !renderer_black_cross->isValid()) {
    qDebug() << "Failed to load SVG!";
    return;
  }

  // Размер области для рендеринга
  QSize target_size(300, 300);

  // Рендерим красный крест
  QPixmap red_pixmap(target_size);
  red_pixmap.fill(Qt::transparent);
  QPainter red_painter(&red_pixmap);
  renderer_red_cross->render(&red_painter);

  // Рендерим чёрный крест
  QPixmap black_pixmap(target_size);
  black_pixmap.fill(Qt::transparent);
  QPainter black_painter(&black_pixmap);
  renderer_black_cross->render(&black_painter);

  // Создаем QGraphicsPixmapItem для красного креста
  red_cross_image_ = new QGraphicsPixmapItem(red_pixmap);
  red_cross_image_->setOffset(-target_size.width() / 2,
                              -target_size.height() / 2);
  background_scene_->addItem(red_cross_image_);

  // Создаем QGraphicsPixmapItem для чёрного креста
  black_cross_image_ = new QGraphicsPixmapItem(black_pixmap);
  black_cross_image_->setOffset(-target_size.width() / 2,
                                -target_size.height() / 2);
  background_scene_->addItem(black_cross_image_);

  // Устанавливаем начальное состояние
  red_cross_image_->setVisible(true);
  black_cross_image_->setVisible(false);
};

/**
 * \brief Отрисовка перекрестья на сцене
 */
void Client_GUI::drawCross() {
  // Размер области для рендеринга
  QSize target_size(100, 100);  // Размер области для перекрестья
  QPixmap pixmap(target_size);
  pixmap.fill(Qt::transparent);

  // Создаём painter для отрисовки на QPixmap
  QPainter painter(&pixmap);
  QPen pen(Qt::green);
  pen.setWidth(2);
  painter.setPen(pen);

  // Рисуем крест
  painter.drawLine(0, target_size.height() / 2, target_size.width(),
                   target_size.height() / 2);

  painter.drawLine(target_size.width() / 2, 0, target_size.width() / 2,
                   target_size.height());

  // Добавляем результат в сцену как QGraphicsPixmapItem
  QGraphicsPixmapItem* green_cross_item = new QGraphicsPixmapItem(pixmap);
  green_cross_item->setOffset(-target_size.width() / 2,
                              -target_size.height() / 2);
  // Добавляем в сцену
  background_scene_->addItem(green_cross_item);
};
/**
 * \brief Функция обновления позиции и угла перекрестья
 */
void Client_GUI::updateCrossPositionAndAngle() {
  // Учитываем угол камеры для масштаба по горизонтали
  double scale_factor = (ui_data_.angle / 360.0) * 6000.0 / 50.0;
  double adjusted_center_x = center_x * scale_factor;

  // Вычисляем новые координаты с учётом смещения
  double new_x = adjusted_center_x * ui_data_.horizontal_indentation;
  double new_y = center_y * ui_data_.vertical_indentation;

  // Устанавливаем позицию креста
  red_cross_image_->setPos(new_x, new_y);
  black_cross_image_->setPos(new_x, new_y);

  updateInfoLabels();
};

/**
 * \brief Обновление информации на интерфейсе
 */
void Client_GUI::updateInfoLabels() {
  ui_->CameraAngleInfo->setText("Угол камеры: " +
                                QString::number(ui_data_.angle));
  ui_->HorizItendInfo->setText(
      "Отступ по горизонтали: " +
      QString::number(ui_data_.horizontal_indentation));
  ui_->VerticItendInfo->setText("Отступ по вертикали: " +
                                QString::number(ui_data_.vertical_indentation));
};
/**
 * \brief Слот смены цвета перекрестия
 */
void Client_GUI::swapCross() {
  red_cross_image_->setVisible(!red_cross_image_->isVisible());
  black_cross_image_->setVisible(!black_cross_image_->isVisible());
};

/**
 * \brief Слот смены цвета фона
 */
void Client_GUI::swapBackground() {
  if (ui_->BackgroundColorCombBox->currentText() == "Белый") {
    background_scene_->setBackgroundBrush(Qt::white);
  } else if (ui_->BackgroundColorCombBox->currentText() == "Чёрный") {
    background_scene_->setBackgroundBrush(Qt::black);
  } else if (ui_->BackgroundColorCombBox->currentText() == "Серый") {
    background_scene_->setBackgroundBrush(Qt::gray);
  }
};