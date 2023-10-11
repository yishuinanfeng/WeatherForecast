#include "CityCodeUtil.h"
#include "citylineedit.cpp"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "weatherdata.h"

#include <QAction>
#include <QContextMenuEvent>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QPainter>
#include <QPoint>
#include <weatherdatatransformer.h>


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

    ui->ll_high_curve->installEventFilter(this);
    ui->ll_low_curve->installEventFilter(this);

    connect(exitAction,&QAction::triggered,this,[=]{
        qApp->exit(0);
    });

    networkManager = new QNetworkAccessManager();
    connect(networkManager,&QNetworkAccessManager::finished,this,&MainWindow::onNetReply);

    connect(ui->pb_search,&QPushButton::clicked,this,&MainWindow::onSearchCityClick);
    connect(ui->le_city,&CityLineEdit::enterKeyPressed,this,&MainWindow::onSearchCityEnterClick);

    QString defaultCityCode = DEFAULT_CITY_CODE;
    getWeatherInfo(defaultCityCode);

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

        uiUpdater = new UiUpdater(ui);
        uiUpdater->update(ui,&weatherData);

        update();
    }
}

void MainWindow::onSearchCityClick(bool checked)
{
    qDebug() << "onSearchCityClick:";
    QString inputCity = ui->le_city->text();
    if(inputCity == nullptr || inputCity == ""){
        QMessageBox::warning(this,"天气","请输入正确的城市名",QMessageBox::Ok);
        return;
    }

    QString cityCode = CityCodeUtil::getCityCode(inputCity);
    if(cityCode == ""){
        QMessageBox::warning(this,"天气","请输入正确的城市名",QMessageBox::Ok);
        return;
    }
    qDebug() << "cityCode:" << cityCode;
    getWeatherInfo(cityCode);
}

void MainWindow::onSearchCityEnterClick()
{
    onSearchCityClick();
}

void MainWindow::drawHighCurve()
{
    if(uiUpdater != nullptr){
       uiUpdater->drawHighCurve(ui);
    }
}

void MainWindow::drawLowCurve()
{
    if(uiUpdater != nullptr){
        uiUpdater->drawLowCurve(ui);
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

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->ll_high_curve && event->type() == QEvent::Paint){
        drawHighCurve();        
    }

    if(watched == ui->ll_low_curve && event->type() == QEvent::Paint){
        drawLowCurve();        
    }

    return QWidget::eventFilter(watched,event);
}


