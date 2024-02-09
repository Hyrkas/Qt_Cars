#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_BtnLoadTable_clicked()
{
    QString site_url="http://localhost:3000/cars";
    QNetworkRequest request((site_url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //WEBTOKEN ALKU
   QByteArray myToken="Bearer xRstgr...";
   request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU

    getManager = new QNetworkAccessManager(this);
    connect(getManager, SIGNAL(finished (QNetworkReply*)), this, SLOT(getCarsSlot(QNetworkReply*)));
    reply = getManager->get(request);
}

void MainWindow::getCarsSlot (QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString car;
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        car+=QString::number(json_obj["ID"].toInt())+","+json_obj["brand"].toString()+","+json_obj["model"].toString()+"\r";
    }

    qDebug()<<car;

    ui->textEdit->setText(car);

    reply->deleteLater();
    getManager->deleteLater();
}

