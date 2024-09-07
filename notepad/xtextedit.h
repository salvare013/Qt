#ifndef XTEXTEDIT_H
#define XTEXTEDIT_H

#include <QDebug>
#include <QKeyEvent>
#include <QTextEdit>

class XTextEdit : public QTextEdit {
 public:
  XTextEdit(QWidget *parent = nullptr);

 private:
  bool CtrlPressed = false;

 protected:
  void wheelEvent(QWheelEvent *e) override;
  void keyPressEvent(QKeyEvent *e) override;
  void keyReleaseEvent(QKeyEvent *e) override;
};

#endif  // XTEXTEDIT_H
