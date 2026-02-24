#include "audio.h"

Audio::Audio(QObject *parent)
    : QObject{parent}
{

}
void Audio::startAudio(QString fileName)
{
    QAudioDeviceInfo device = QAudioDeviceInfo::defaultInputDevice();
    if (device.isNull()) // 录音设备不存在
    {
        QMessageBox::warning(NULL, "警告(Audio)", "无音频设备");
        qDebug() << "无音频设备";
    }
    else
    {
        //音频编码要求
        QAudioFormat my_format;

        my_format.setSampleRate(16000);    //设置采样频率
        my_format.setChannelCount(1);      //设置通道数
        my_format.setSampleSize(16);       //设置位深
        my_format.setCodec("audio/pcm");   //设置编码

        //判断设备是否支持该格式
        if(!device.isFormatSupported(my_format))
        {
            my_format = device.nearestFormat(my_format);
        }

        //打开文件
        my_file = new QFile();
        my_file->setFileName(fileName);
        my_file->open(QIODevice::WriteOnly);

        //创建录音对象
        my_audio = new QAudioInput(my_format, this);

        //开始录音
        my_audio->start(my_file);
    }


}

void Audio::stopAudio()
{
    //停止录音
    my_audio->stop();

    //关闭文件
    my_file->close();

    //删除文件对象
    delete my_file;
    my_file = NULL;
}
