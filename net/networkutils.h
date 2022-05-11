#ifndef NETWORKUTILS_H
#define NETWORKUTILS_H

#include <QObject>
#include <QNetworkReply>

class NetWorkUtil : public QObject
{
    Q_OBJECT
public:
    static NetWorkUtil *instance();

    QNetworkReply * postRequst(const QString &url, QJsonObject &body);

    ~NetWorkUtil();

signals:
    void finished(QNetworkReply * reply);

public slots:


private:
    explicit NetWorkUtil(QObject *parent = nullptr);
    NetWorkUtil(NetWorkUtil &) = delete;
    NetWorkUtil &operator=(NetWorkUtil nwu) = delete;

private:
    class Private;
    friend class Private;
    Private * d;
    QNetworkRequest request;
};

#endif // NETWORKUTILS_H
