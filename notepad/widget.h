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

 private:
  const int defaultFontSize = 13;

 private:
  Ui::Widget *ui;
};

#endif  // WIDGET_H
