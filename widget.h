#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QString>
#include "audio.h"
#include "speech.h"

const QString adressFile = "E:\\1.pcm";

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_pressed();

    void on_pushButton_released();

    void on_clearButton_clicked();

    void on_EnglishButton_clicked();

    void on_ChineseButton_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Widget *ui;

    Audio *audio;

    Speech language;
};
#endif // WIDGET_H
