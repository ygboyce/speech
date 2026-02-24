#include "http.h"

Http::Http(QObject *parent) : QObject(parent)
{

}

bool Http::post_sync(QString Url, QMap<QString, QString> header, QByteArray requestData, QByteArray &replyData)
{
    QNetworkAccessManager manager;  //发送请求的对象
    QNetworkRequest request;        //请求对象

    request.setUrl(Url);
    QMapIterator<QString, QString> it(header); //迭代器

    while (it.hasNext())  //遍历map
    {
        it.next();
        request.setRawHeader(it.key().toLatin1(), it.value().toLatin1());
    }

    QNetworkReply *reply = manager.post(request, requestData);
    QEventLoop l;

    //当服务器返回，reply发出信号
    connect(reply, &QNetworkReply::finished, &l, &QEventLoop::quit);
    l.exec();  //死循环， reply发出信号结束循环

    if (reply != nullptr && reply->error() == QNetworkReply::NoError)
    {
        qDebug() << "请求成功";
        replyData = reply->readAll(); // 读取服务器返回的数据
        qDebug() << replyData;

        return true;
    }
    else
    {
        qDebug() << "请求失败";
        return false;
    }

}
