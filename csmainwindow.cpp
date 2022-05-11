#include "csmainwindow.h"
#include "ui_csmainwindow.h"

CSMainWindow::CSMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CSMainWindow)
{
    ui->setupUi(this);

    httpUtilSoma = new HttpUtilsSoma(this);
}

CSMainWindow::~CSMainWindow()
{
    delete ui;
    delete httpUtilSoma;
}

void CSMainWindow::getBrainList()
{
//    ui->checkmapwidget->getBrainList();
    httpUtilSoma->getBrainList();
}

void CSMainWindow::downloadImage()
{
//    QString brainId = httpUtilSoma->getPotentialSomaInfo()->getBrainId();
//    XYZ* loc = httpUtilSoma->getCoordinateConvert()->getCenterLocation();
//    QString res = httpUtilSoma->resMap[brainId];
//    if(res == nullptr) {
//        qDebug()<<"Fail to download image, something wrong with res list!";
//        isDownloading = false;
//        return;
//    }
//    ui->checkmapwidget->downloadImage(brainId, res, (int)loc->x, (int)loc->y, (int)loc->z, DEFAULT_IMG_SIZE);;
    ui->checkmapwidget->downloadImage("192334", "RES(30801x18821x11515)", 14239, 28711, 10163, 128);
}

void CSMainWindow::getPotentialLoaction()
{
    QJsonObject userInfo;
    userInfo.insert("name", InfoCache::getInstance().getAccount());
    userInfo.insert("passwd", InfoCache::getInstance().getToken());

    httpUtilSoma->getPotentialLoactionWithHttp(userInfo);
}

void CSMainWindow::on_checkmapBtn_clicked()
{
    // 首先通过httpUtilsSoma的getPotentialLocation设置好内部potentialSomaInfo类
    // 以此获得brainId
    // getPotentialLoaction();
    // 再获得分辨率信息
    // getBrainList();
    downloadImage();
}

