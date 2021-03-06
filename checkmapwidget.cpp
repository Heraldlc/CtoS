#include "checkmapwidget.h"
#include "ui_checkmapwidget.h"

#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>

/**
 * @brief 此窗口在构造时完成图像下载及渲染
 * @param parent
 */
CheckMapWidget::CheckMapWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CheckMapWidget)
{
    ui->setupUi(this);

    httpUtilsImage = new HttpUtilsImage(this);

    connect(NetWorkUtil::instance(), &NetWorkUtil::finished, this, &CheckMapWidget::downloadImageFinish);
}

CheckMapWidget::~CheckMapWidget()
{
    delete ui;
    //    delete potentialSomaInfo;
}

void CheckMapWidget::downloadImage(QString brainId, QString res, int offsetX, int offsetY, int offsetZ, int size)
{
    QJsonObject pa1;
    pa1.insert("x", offsetX - size/2);
    pa1.insert("y", offsetY - size/2);
    pa1.insert("z", offsetZ - size/2);

    QJsonObject pa2;
    pa2.insert("x", offsetX + size/2);
    pa2.insert("y", offsetY + size/2);
    pa2.insert("z", offsetZ + size/2);

    QJsonObject bBox;
    bBox.insert("pa1", pa1);
    bBox.insert("pa2", pa2);
    bBox.insert("res", res);
    bBox.insert("obj", brainId);

    QJsonObject userInfo;
    userInfo.insert("name", InfoCache::getInstance().getAccount());
    userInfo.insert("passwd", InfoCache::getInstance().getToken());

//    httpUtilsImage->downloadImageWithHttp(userInfo, bBox);
    // requestBody
    QJsonObject body;
    body.insert("bb", bBox);
    body.insert("user", userInfo);

    // post request
    QJsonDocument document;
    document.setObject(body);
    QByteArray dataArray;
    dataArray = document.toJson(QJsonDocument::Compact);

    NetWorkUtil::instance()->postRequst(URL_DOWNLOAD_IMAGE, body);
}

void CheckMapWidget::downloadImageFinish(QNetworkReply *reply)
{
    qDebug() << "do download image";
    QByteArray data = reply->readAll();
    char* fileContent = data.data();

    // 保存此图像文件
    QString filename = QFileDialog::getSaveFileName(this, "Save File");
    QFile file(filename);
    file.open(QIODevice::WriteOnly);
//    QDataStream out(&file);
//    out.writeRawData(data, data.size()-1);
    while(*data) {
        file.write(fileContent);
        fileContent++;
    }

    file.close();

    reply->deleteLater();
    reply = nullptr;
}
