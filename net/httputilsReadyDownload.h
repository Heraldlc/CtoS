#ifndef HTTPUTILSREADYDOWNLOAD_H
#define HTTPUTILSREADYDOWNLOAD_H

#include "net/httputils.h"
#include "net/httputilsimage.h"
#include "serverconnection/model/potentialsomainfo.h"
#include "serverconnection/model/coordinateconvert.h"
#include <QHash>
#include <QJsonObject>

class HttpUtilsSoma: public HttpUtils
{
    Q_OBJECT
public:
    HttpUtilsSoma(QWidget *parent = nullptr);
    ~HttpUtilsSoma();

    void asyncPostRequestForPotentialLocation(QUrl url, QJsonObject body);
    void getPotentialLoactionWithHttp(QJsonObject userInfo);
    // PotentialSomaInfo function
    PotentialSomaInfo* getPotentialSomaInfo();
    void setPotentialSomaInfo(PotentialSomaInfo* pSomaInfo);

    // CoordinateConvert function
    CoordinateConvert* getCoordinateConvert();
    void setCoordinateConvert(CoordinateConvert* cConvert);

    void handleCoordinateConvertWithPotentialLocation();

    // set ResMap
    QHash<QString, QString> resMap;
    void getBrainList();
    void getBrainListWithHttp(QJsonObject userInfo);
    void asyncPostRequestForBrainList(QUrl url, QJsonObject body);

public slots:
    void getPotentialLocationReplyFinished(QNetworkReply *reply);
    void getBrainListReplyFinished(QNetworkReply *reply);

private:
    QString URL_GET_POTENTIAL_LOCATION = SERVER_IP + "/dynamic/soma/getpotentiallocation";
    QString URL_GET_BRAIN_LIST = SERVER_IP + "/dynamic/image/getimagelist";

    PotentialSomaInfo* potentialSomaInfo = nullptr;
    CoordinateConvert* coordinateConvert = nullptr;


};

#endif // HTTPUTILSREADYDOWNLOAD_H
