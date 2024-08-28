#ifndef WIDGET_H
#define WIDGET_H

#include <qfont.h>
#include <qglobal.h>
#include <QDebug>
#include <QFileDialog>
#include <QKeyEvent>
#include <QMessageBox>
#include <QShortcut>
#include <QTextEdit>
#include <QWidget>
#include "./ui_widget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
  Q_OBJECT

 public:
  QFile file;

  Widget(QWidget *parent = nullptr);
  ~Widget();

  void closeEvent(QCloseEvent *event) override;

 public slots:
  void CloseWindow();
  void FileOpen();
  void FileSave();
  void FileClean();
  void ChangeCode();
  void ShowPosition();
  void ChangeFontSize(int size);

 protected:
  virtual void wheelEvent(QWheelEvent *event) override;
  virtual void keyPressEvent(QKeyEvent *event) override;
  virtual void keyReleaseEvent(QKeyEvent *event) override;

 private:
  bool keyControlPressed = false;
  const int defaultFontSize = 13;

  Ui::Widget *ui;
};

#endif  // WIDGET_H
