#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("语音识别");

    ui->pushButton->setText("按住说话");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_pressed()
{
    ui->pushButton->setText("松开识别");

    //开始录音
    audio = new Audio;
    audio->startAudio(adressFile);
}

void Widget::on_pushButton_released()
{
    //停止录音
    audio->stopAudio();

    //修改按钮文字
    ui->pushButton->setText("开始识别");

    //开始识别
    Speech my_speech;
    QString text = my_speech.speechIdentify(adressFile, language);

    ui->textEdit->setText(text);

    ui->pushButton->setText("按住说话");
}

void Widget::on_clearButton_clicked()
{
    ui->textEdit->clear();
}

void Widget::on_EnglishButton_clicked()
{
    language.falg = 2;
    ui->textEdit->clear();
    ui->textEdit->setText("请说英语");
}

void Widget::on_ChineseButton_clicked()
{
    language.falg = 1;
    ui->textEdit->clear();
    ui->textEdit->setText("请说普通话");
}

void Widget::on_pushButton_4_clicked()
{
    language.falg = 3;
    ui->textEdit->clear();
    ui->textEdit->setText("请说四川话");
}
