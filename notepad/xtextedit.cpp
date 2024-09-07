#include "xtextedit.h"
#include <qglobal.h>
#include <qnamespace.h>
#include <qtextedit.h>

XTextEdit::XTextEdit(QWidget *parent) : QTextEdit(parent) {}
void XTextEdit::wheelEvent(QWheelEvent *e) {
  if (CtrlPressed) {
    if (e->angleDelta().y() > 0) {
      zoomIn();
    } else if (e->angleDelta().y() < 0) {
      zoomOut();
    }
    e->accept();
  } else {
    QTextEdit::wheelEvent(e);
  }
}
void XTextEdit::keyPressEvent(QKeyEvent *e) {
  if (e->key() == Qt::Key_Control) {
    CtrlPressed = true;
    // qDebug() << "ctrl pressed";
  }
  QTextEdit::keyPressEvent(e);
}
void XTextEdit::keyReleaseEvent(QKeyEvent *e) {
  if (e->key() == Qt::Key_Control) {
    CtrlPressed = false;
    // qDebug() << "ctrl release";
  }
  QTextEdit::keyReleaseEvent(e);
}