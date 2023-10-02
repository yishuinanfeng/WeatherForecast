#include "CityCodeUtil.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "weatherdata.h"

#include <QAction>
#include <QContextMenuEvent>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <UiUpdater.h>
#include <WeatherDataTransformer.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(width(),height());

    exitMenu = new QMenu(this);
    exitAction = new QAction();

    exitAction->setText("退出");

    exitMenu->addAction(exitAction);

    connect(exitAction,&QAction::triggered,this,[=]{
        qApp->exit(0);
    });

    networkManager = new QNetworkAccessManager();
    connect(networkManager,&QNetworkAccessManager::finished,this,&MainWindow::onNetReply);

    //1010100是北京的城市编码
//    getWeatherInfo("101010100");

    QString cityCode = CityCodeUtil::getCityCode("广州");
    if(cityCode == ""){
        QMessageBox::warning(this,"天气","请输入正确的城市名",QMessageBox::Ok);
        return;
    }
    qDebug() << "cityCode:" << cityCode;
    getWeatherInfo(cityCode);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete networkManager;
}

void MainWindow::onNetReply(QNetworkReply *reply)
{
    qDebug() << "onNetReply success";

    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    qDebug() << "operation:" << reply->operation();
    qDebug() << "statusCode:" << statusCode;
    qDebug() << "url:" << reply->url();
    qDebug() << "raw header:" << reply->rawHeaderList();

    if(reply->error() != QNetworkReply::NoError || statusCode != 200){
        qDebug() << reply->errorString().toLatin1().data();
        QMessageBox::warning(this,"天气","请求失败",QMessageBox::Ok);
    }else{
        QByteArray byteArray = reply->readAll();
        qDebug() << "read all byteArray:" << byteArray.data();
        WeatherDataTransformer weatherDataTransformer;
        WeatherData weatherData = weatherDataTransformer.parseJson(&byteArray);
        qDebug() << "weatherData:" << weatherData;

        UiUpdater uiUpdater(ui);
        uiUpdater.update(ui,&weatherData);
    }
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    //菜单栏弹在当前鼠标所在的位置
    exitMenu->exec(QCursor::pos());
    event->accept();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    offSet = event->globalPos() - this->pos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos() - offSet);
}

void MainWindow::getWeatherInfo(QString cityCode)
{
    QNetworkRequest request(QUrl("http://t.weather.itboy.net/api/weather/city/" + cityCode));
    networkManager->get(request);

    //    connect(reply, &QNetworkReply::finished, [=]() {
    //        if (reply->error() == QNetworkReply::NoError) {
    //            QByteArray data = reply->readAll();
    //            // 处理响应数据
    //        } else {
    //            QString error_message = reply->errorString();
    //            // 处理错误
    //        }

    //        reply->deleteLater();
    //    });
}


