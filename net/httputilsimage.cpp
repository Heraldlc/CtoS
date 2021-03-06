#include "httputilsimage.h"

#include <QFile>
#include <QFileDialog>

HttpUtilsImage::HttpUtilsImage(QWidget *parent)
    : HttpUtils(parent)
{

}

/**
 * @brief HttpUtilsImage::getBrainListWithHttp
 * @param userInfo
 */
void HttpUtilsImage::getBrainListWithHttp(QJsonObject userInfo)
{
    // set for query parameters on server, default value: off=0, limit=2000
    QJsonObject queryCondition;
    queryCondition.insert("off", 0);
    queryCondition.insert("limit", 2000);

    QJsonObject body;
    body.insert("user", userInfo);
    body.insert("condition", queryCondition);
    asyncPostRequest(URL_GET_BRAIN_LIST, body);
}

/**
 * @brief download image block
 * @param userInfo
 * @param bBox
 */
void HttpUtilsImage::downloadImageWithHttp(QJsonObject userInfo, QJsonObject bBox)
{
    // requestBody
    QJsonObject body;
    body.insert("bb", bBox);
    body.insert("user", userInfo);
    asyncPostRequest(URL_DOWNLOAD_IMAGE, body);
}

/**
 * @brief download image block
 * @param username
 * @param password
 * @param swc file
 * @param res, RES(1000*1000*500)
 * @param x
 * @param y
 * @param z
 * @param len, size of image block
 */
void HttpUtilsImage::getBBSwcWithHttp(QString username, QString password, QString swc, int res, int x, int y, int z, int len)
{
    QJsonObject body;
    body.insert("name", username);
    body.insert("passwd", password);
    body.insert("swc", swc);
    body.insert("x", x);
    body.insert("y", y);
    body.insert("z", z);
    body.insert("len", len);
    body.insert("res", res);
    asyncPostRequest(URL_GET_BBSWC, body);
}

void HttpUtilsImage::downloadSomaBlockWithHttp(QString username, QString password, QString swc, int res, int x, int y, int z, int len)
{
    QJsonObject body;
    body.insert("name", username);
    body.insert("passwd", password);
    body.insert("swc", swc);
    body.insert("x", x);
    body.insert("y", y);
    body.insert("z", z);
    body.insert("len", len);
    body.insert("res", res);
    asyncPostRequest(URL_GET_BBSWC, body);
}


void HttpUtilsImage::replyFinished(QNetworkReply *reply) {
    qDebug()<<"do download image";
    QByteArray data = reply->readAll();
    int status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if(status == 200) {
        QString fileName = "C:/Users/SEU/Desktop/1.v3dpbd";
        QFile file(fileName);
        file.open(QIODevice::WriteOnly);
        QDataStream out(&file);
        out.writeBytes(data, data.size());

        file.close();
        qDebug()<<"done download image";
    }
}



















