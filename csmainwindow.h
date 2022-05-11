#ifndef CSMAINWINDOW_H
#define CSMAINWINDOW_H

#include <QMainWindow>

#include "serverconnection/net/httputilsReadyDownload.h"


#include "basic_4dimage.h"

namespace Ui {
class CSMainWindow;
}

class CSMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CSMainWindow(QWidget *parent = nullptr);
    ~CSMainWindow();

    void getBrainList();
    void downloadImage();
    void getPotentialLoaction();

public slots:
    void on_checkmapBtn_clicked();

private:
    Ui::CSMainWindow *ui;
    int DEFAULT_IMG_SIZE = 128;


    bool isDownloading = false;

    HttpUtilsSoma *httpUtilSoma;
};

#endif // CSMAINWINDOW_H
