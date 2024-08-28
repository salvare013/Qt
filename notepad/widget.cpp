#include "widget.h"
#include <qtextedit.h>
#include <qwidget.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  connect(ui->close, &QPushButton::clicked, this,
          &Widget::CloseWindow);
  connect(ui->open, &QPushButton::clicked, this, &Widget::FileOpen);
  connect(ui->save, &QPushButton::clicked, this, &Widget::FileSave);
  connect(ui->clean, &QPushButton::clicked, this,
          &Widget::FileClean);
  connect(ui->comboBox,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &Widget::ChangeCode);
  connect(ui->textEdit, &QTextEdit::cursorPositionChanged, this,
          &Widget::ShowPosition);

  QShortcut *open =
      new QShortcut(QKeySequence(tr("Ctrl+O", "File|Open")), this);
  QShortcut *save =
      new QShortcut(QKeySequence(tr("Ctrl+S", "File|Save")), this);
  QShortcut *quit =
      new QShortcut(QKeySequence(tr("Ctrl+Q", "File|Quit")), this);
  QShortcut *clean =
      new QShortcut(QKeySequence(tr("Ctrl+W", "File|Clean")), this);
  QShortcut *zoomIn =
      new QShortcut(QKeySequence(tr("Ctrl+=", "File|ZoomIn")), this);
  QShortcut *zoomOut = new QShortcut(
      QKeySequence(tr("Ctrl+-", "File|ZoomOut")), this);
  QShortcut *zoomInWindow = new QShortcut(
      QKeySequence(tr("Ctrl+M", "File|zoomWindow")), this);
  QShortcut *reFontSize = new QShortcut(
      QKeySequence(tr("Ctrl+R", "File|ReFontSize")), this);
  connect(open, &QShortcut::activated, this, &Widget::FileOpen);
  connect(save, &QShortcut::activated, this, &Widget::FileSave);
  connect(quit, &QShortcut::activated, this, &Widget::CloseWindow);
  connect(clean, &QShortcut::activated, this, &Widget::FileClean);
  connect(zoomIn, &QShortcut::activated, [=] {
    ChangeFontSize(1);
    // ui->textEdit->zoomIn();
  });
  connect(zoomOut, &QShortcut::activated, [=] {
    ChangeFontSize(-1);
    // ui->textEdit->zoomOut();
  });
  connect(zoomInWindow, &QShortcut::activated,
          [=] { this->showMaximized(); });
  connect(reFontSize, &QShortcut::activated,
          [=] { ChangeFontSize(0); });
}

Widget::~Widget() {
  delete ui;
}

void Widget::closeEvent(QCloseEvent *event) {
  CloseWindow();
}
void Widget::wheelEvent(QWheelEvent *event) {
  if (keyControlPressed) {
    if (event->angleDelta().y() >= 0) {
      ChangeFontSize(1);
    } else {
      ChangeFontSize(-1);
    }
    event->accept();
  }
  QWidget::wheelEvent(event);
}
void Widget::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Control) {
    keyControlPressed = true;
  }
  QWidget::keyPressEvent(event);
}
void Widget::keyReleaseEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Control) {
    keyControlPressed = false;
  }
  QWidget::keyReleaseEvent(event);
}