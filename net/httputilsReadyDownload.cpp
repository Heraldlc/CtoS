#include "httputilsReadyDownload.h"

#include <QJsonArray>
#include <QJsonDocument>
#include "serverconnection/infocache.h"


HttpUtilsSoma::HttpUtilsSoma(QWidget *parent)
    :HttpUtils(parent)
{

}

HttpUtilsSoma::~HttpUtilsSoma()
{

}

/**
 * @brief similar to asyncPostRequest, for connecting different slots
 * @param url
 * @param body
 */
void HttpUtilsSoma::asyncPostRequestForPotentialLocation(QUrl url, QJsonObject body)
{
    QJsonDocument document;
    document.setObject(body);
    QByteArray dataArray;
    dataArray = document.toJson(QJsonDocument::Compact);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setUrl(url);

    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getPotentialLocationReplyFinished(QNetworkReply*)));
    manager->post(request, dataArray);
}


void HttpUtilsSoma::getPotentialLoactionWithHttp(QJsonObject userInfo)
{
    QJsonObject body;
    body.insert("user", userInfo);
    asyncPostRequestForPotentialLocation(URL_GET_POTENTIAL_LOCATION, body);
}

/**
 * @brief HttpUtilsSoma::getPotentialSomaInfo
 * @return
 */
PotentialSomaInfo *HttpUtilsSoma::getPotentialSomaInfo()
{
    return potentialSomaInfo;
}

void HttpUtilsSoma::setPotentialSomaInfo(PotentialSomaInfo *pSomaInfo)
{
    this->potentialSomaInfo = pSomaInfo;
}

/**
 * @brief HttpUtilsSoma::getCoordinateConvert
 * @return
 */
CoordinateConvert *HttpUtilsSoma::getCoordinateConvert()
{
    return coordinateConvert;
}

void HttpUtilsSoma::setCoordinateConvert(CoordinateConvert *cConvert)
{
    this->coordinateConvert = cConvert;
}

void HttpUtilsSoma::handleCoordinateConvertWithPotentialLocation()
{
    if(potentialSomaInfo != nullptr) {
        coordinateConvert->initLocation(potentialSomaInfo->getLoaction());
    }
    if(resMap.isEmpty()) {
        getBrainList();
    }
}

/**
 * @brief functions for get brain list
 */
void HttpUtilsSoma::getBrainList()
{
    QJsonObject userInfo;
    userInfo.insert("name", InfoCache::getInstance().getAccount());
    userInfo.insert("passwd", InfoCache::getInstance().getToken());
    getBrainListWithHttp(userInfo);
}

void HttpUtilsSoma::getBrainListWithHttp(QJsonObject userInfo)
{
    QJsonObject queryCondition;
    queryCondition.insert("off", 0);
    queryCondition.insert("limit", 2000);

    QJsonObject body;
    body.insert("user", userInfo);
    body.insert("condition", queryCondition);
    asyncPostRequestForBrainList(URL_GET_BRAIN_LIST, body);
}

void HttpUtilsSoma::asyncPostRequestForBrainList(QUrl url, QJsonObject body)
{
    QJsonDocument document;
    document.setObject(body);
    QByteArray dataArray;
    dataArray = document.toJson(QJsonDocument::Compact);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setUrl(url);

    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getBrainListReplyFinished(QNetworkReply*)));
    manager->post(request, dataArray);
}

// slot: getPotentialLocationReplyFinished -> asyncPostRequestForPotentialLocation()
void HttpUtilsSoma::getPotentialLocationReplyFinished(QNetworkReply *reply)
{
    int status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if(status == 200) {
        // process response
        QByteArray responseData = reply->readAll();
        qDebug()<< "potential location reply data: " << responseData;
        QJsonObject potentialLocation = QJsonDocument::fromJson(responseData).object();
        if(potentialLocation.contains("loc")) {
            QJsonObject loc = potentialLocation.value("loc").toObject();

            XYZ* location = new XYZ(loc.value("x").toInt(), loc.value("y").toInt(), loc.value("z").toInt());
            PotentialSomaInfo* pSomaInfo = new PotentialSomaInfo(potentialLocation.value("id").toInt(), potentialLocation.value("image").toString(), location);
            setPotentialSomaInfo(pSomaInfo);
            delete pSomaInfo;
            delete location;
        }
    }
    else {
        qDebug()<<"get potential location reply failed!";
    }

    reply->deleteLater();
}

void HttpUtilsSoma::getBrainListReplyFinished(QNetworkReply *reply)
{
    int status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if(status == 200) {
        QByteArray reponseData = reply->readAll();
        qDebug()<< "brain list reply data: " << reponseData;
        QJsonArray jsonArray = QJsonDocument::fromJson(reponseData).array();
        for(int i = 0; i < jsonArray.count(); i++) {
            QJsonValue cur = jsonArray.at(i);
            QJsonObject jsonObject = cur.toObject();
            QString imageId;
            if(jsonObject.contains("name")) {
                QJsonValue value = jsonObject.value("name");
                imageId = value.toString();
            }
            QString detail;
            if(jsonObject.contains("detail")) {
                QJsonValue value = jsonObject.value("detail");
                detail = value.toString();
                qDebug() <<"detail拆分" << detail;
            }

        }
    }
    else {
        qDebug()<<"get brain list failed!";
    }
}
