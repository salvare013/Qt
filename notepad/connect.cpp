#include "widget.h"

void Widget::CloseWindow() {
  if (ui->textEdit->toPlainText().isEmpty()) {
    this->close();
  } else {
    if (file.isOpen()) {
      if (ui->textEdit->document()->isModified()) {
        FileSave();
        file.close();
      }
      this->close();
    } else {
      FileClean();
      this->close();
    }
  }
}
void Widget::FileOpen() {
  QString fileName = QFileDialog::getOpenFileName(
      this, tr("Open File"), "D:/CodeSet/Text",
      tr("TextFiles(*.txt);;"
         "CodeFiles(*.c *.cpp *.cc *.cxx *.h *.py);;"
         "AllFiles(*.*)"));

  ui->textEdit->clear();

  file.setFileName(fileName);
  if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
    qDebug() << "open file fail";
  }
  this->setWindowTitle("老徐记事本--- " + fileName + " ---已打开");
  QTextStream in(&file);
  in.setCodec(ui->comboBox->currentText().toStdString().c_str());

  while (!in.atEnd()) {
    QString context = in.readLine();
    ui->textEdit->append(context);
  }
}
void Widget::FileSave() {
  if (!file.isOpen()) {
    QString fileName = QFileDialog::getSaveFileName(
        this, tr("Open File"), "D:/CodeSet/Text",
        tr("TextFiles(*.txt);;"
           "CodeFiles(*.c *.cpp *.cc *.cxx *.h *.py);;"
           "AllFiles(*.*)"));
    file.setFileName(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
      qDebug() << "save file fail";
    }
  }
  file.resize(0);
  QTextStream out(&file);
  out.setCodec(ui->comboBox->currentText().toStdString().c_str());
  out << ui->textEdit->toPlainText();
  this->setWindowTitle("老徐记事本--- " + file.fileName() +
                       " ---已保存");
}
void Widget::FileClean() {
  if (ui->textEdit->toPlainText().isEmpty()) {
    return;
  }
  int ret = QMessageBox::warning(
      this, tr("老徐记事本"), tr("文本未保存,是否保存?"),
      QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
      QMessageBox::Save);
  switch (ret) {
    case QMessageBox::Save:
      FileSave();
      ui->textEdit->clear();
      break;
    case QMessageBox::Discard:
      if (file.isOpen()) {
        file.close();
      }
      ui->textEdit->clear();
      break;
    case QMessageBox::Cancel:
      qDebug() << "Cancel was clicked";
      break;
    default:
      FileSave();
      break;
  }
  this->setWindowTitle("老徐记事本---无文件");
}
void Widget::ChangeCode() {
  ui->textEdit->clear();
  if (file.isOpen()) {
    QTextStream in(&file);
    in.setCodec(ui->comboBox->currentText().toStdString().c_str());
    file.seek(0);
    while (!in.atEnd()) {
      QString context = in.readLine();
      ui->textEdit->append(context);
    }
  }
}
void Widget::ShowPosition() {
  // 设置行号与列号
  QTextCursor cursor = ui->textEdit->textCursor();
  QString row = QString::number(cursor.blockNumber() + 1);
  QString col = QString::number(cursor.columnNumber() + 1);
  //   const QString pos = "Row: " + row + " , " + "Col: " + col;
  const QString pos = "行: " + row + " , " + "列: " + col;
  ui->position->setText(pos);
  // 设置当前行高亮
  QList<QTextEdit::ExtraSelection> extraSelections;
  QTextEdit::ExtraSelection ext;
  ext.cursor = ui->textEdit->textCursor();
  QBrush qBrush(Qt::cyan);
  ext.format.setBackground(qBrush);
  ext.format.setProperty(QTextFormat::FullWidthSelection, true);
  extraSelections.append(ext);
  ui->textEdit->setExtraSelections(extraSelections);
}
void Widget::ChangeFontSize(int size) {
  QFont font;
  if (size == 0) {
    font.setPointSize(defaultFontSize);
    ui->textEdit->setFont(font);
    return;
  }
  int fontSize = ui->textEdit->font().pointSize();
  if (size > 0) {
    fontSize++;
  } else {
    if (fontSize > 9) {
      fontSize--;
    }
  }
  font.setPointSize(fontSize);
  ui->textEdit->setFont(font);
}