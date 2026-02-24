#ifndef SPEECH_H
#define SPEECH_H

#include <QObject>
#include <QWidget>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QHostInfo>  //主机信息
#include <QFile>
#include <QMessageBox>

#include "http.h"

//获取access_tocken相关
const QString baiduTokenUrl = "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=%1&client_secret=%2&";
const QString client_id = "Zht0swBZYZStjZJsORdQbyKW";
const QString client_secret = "1htAdwVBhUgEACTZs79h5m74fjLN7xEX";

//语音识别相关
const QString ChineseSpeechUrl = "http://vop.baidu.com/server_api?dev_pid=1537&cuid=%1&token=%2";       //普通话
const QString EnglishSpeechUrl = "http://vop.baidu.com/server_api?dev_pid=1737&cuid=%1&token=%2";       //英语
const QString SichuanSpeechUrl = "http://vop.baidu.com/server_api?dev_pid=1837&cuid=%1&token=%2";       //四川话

class Speech : public QObject
{
    Q_OBJECT
public:
    explicit Speech(QObject *parent = nullptr);

    QString speechIdentify(QString fileName, Speech &language);
    QString getJsonValue(QByteArray ba, QString key);

    //QString languageSpeechUrl(QString &speechUrl);

    int falg;
    QString languageSpeechUrl;

signals:

};

#endif // SPEECH_H
