#include "speech.h"

Speech::Speech(QObject *parent) : QObject(parent)
{

}

QString Speech::speechIdentify(QString fileName, Speech &language)
{
    //选择语言
    if (language.falg == 0)
    {
        QMessageBox::warning(NULL, "识别提示", "未选择语言");
        return "";
    }
    else if (language.falg == 1) languageSpeechUrl = ChineseSpeechUrl;
    else if (language.falg == 2) languageSpeechUrl = EnglishSpeechUrl;
    else if (language.falg == 3) languageSpeechUrl = SichuanSpeechUrl;


    //获取access_token
    QString tokenUrl = QString(baiduTokenUrl).arg(client_id).arg(client_secret);

    QMap<QString, QString> header;
    header.insert(QString("Content-Type"), QString("audio/pcm;rate=16000"));

    QByteArray requestData;    //发送的内容
    QByteArray replyData;      //服务器返回的内容

    QString accessToken;

    Http my_http;
    bool result = my_http.post_sync(tokenUrl, header, requestData, replyData);
    if (result)
    {
        QString key = "access_token";
        accessToken = getJsonValue(replyData, key);
        qDebug() << accessToken;
    }
    else
    {
        QMessageBox::warning(NULL, "识别提示", "服务器请求失败");
        return "";
    }

    //组合Url
    QString speechUrl = QString(languageSpeechUrl).arg(QHostInfo::localHostName()).arg(accessToken);

    //把文件转换成QBytArray
    QFile file;
    file.setFileName(fileName);
    file.open(QIODevice::ReadOnly);
    requestData = file.readAll();
    file.close();

    replyData.clear();

    //再次发起请求
    result = my_http.post_sync(speechUrl, header, requestData, replyData);
    if (result)
    {
        QString key = "result";
        QString text = getJsonValue(replyData, key);
        //qDebug() << accessToken;
        return text;
    }
    else
        QMessageBox::warning(NULL, "识别提示", "语音识别失败");

    return "";
}

QString Speech::getJsonValue(QByteArray ba, QString key)
{
    QJsonParseError paraseError;
    QJsonDocument jsonDocument = QJsonDocument::fromJson(ba, &paraseError);
    if (paraseError.error == QJsonParseError::NoError)
    {
        if (jsonDocument.isObject())
        {
            //jsonDocument转换成json对象
            QJsonObject jsonObj = jsonDocument.object();
            if (jsonObj.contains(key))
            {
                QJsonValue jsonValue = jsonObj.value(key);
                if (jsonValue.isString())       //字符串
                {
                    return jsonValue.toString();
                }
                else if (jsonValue.isArray())   //数组
                {
                    QJsonArray arr = jsonValue.toArray();
                    QJsonValue jv = arr.at(0);    //获取第1个元素
                    return jv.toString();
                }
            }
        }
    }

    return "";
}
