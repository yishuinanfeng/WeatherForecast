#include "uidatahandler.h"


#include <QList>
#include <QPainter>
#include <QString>
#include <QStyle>
#include <uiupdater.h>
#include <ui_mainwindow.h>
#include <QDateTime>
#include "uiupdater.h"

UiUpdater::UiUpdater(Ui::MainWindow *ui)
{
    weekDayViewList = QList<QLabel*>();
    weekViewList = QList<QLabel*>();
    typeIconViewList= QList<QLabel*>();
    typeNameViewList= QList<QLabel*>();
    airQualityViewList= QList<QLabel*>();
    windViewList= QList<QLabel*>();
    windValueViewList= QList<QLabel*>();

    weekDayViewList << ui->ll_week_day1
                    << ui->ll_week_day2
                    << ui->ll_week_day3
                    << ui->ll_week_day4
                    << ui->ll_week_day5
                    << ui->ll_week_day6;

    weekViewList << ui->ll_week1
                 << ui->ll_week2
                 << ui->ll_week3
                 << ui->ll_week4
                 << ui->ll_week5
                 << ui->ll_week6;

    typeNameViewList << ui->ll_type1
                     << ui->ll_type2
                     << ui->ll_type3
                     << ui->ll_type4
                     << ui->ll_type5
                     << ui->ll_type6;

    typeIconViewList << ui->ll_type_icon1
                     << ui->ll_type_icon2
                     << ui->ll_type_icon3
                     << ui->ll_type_icon4
                     << ui->ll_type_icon5
                     << ui->ll_type_icon6;

    airQualityViewList << ui->ll_air1
                       << ui->ll_air2
                       << ui->ll_air3
                       << ui->ll_air4
                       << ui->ll_air5
                       << ui->ll_air6;

    windValueViewList << ui->ll_wind1
                      << ui->ll_wind2
                      << ui->ll_wind3
                      << ui->ll_wind4
                      << ui->ll_wind5
                      << ui->ll_wind6;

    windViewList << ui->ll_wind_name1
                 << ui->ll_wind_name2
                 << ui->ll_wind_name3
                 << ui->ll_wind_name4
                 << ui->ll_wind_name5
                 << ui->ll_wind_name6;


}

UiUpdater::~UiUpdater()
{

}

void UiUpdater::update(Ui::MainWindow *ui,WeatherData *weatherData)
{
    updateTodayWeather(ui,weatherData);
    updateTodayWeatherExtraInfo(ui,weatherData);
    updateRecentDayWeather(ui,weatherData);
    updateTitle(ui,weatherData);
    updateTempCurveData(ui,weatherData);
}

void UiUpdater::updateTodayWeather(Ui::MainWindow *ui, WeatherData *weatherData)
{
    UiDataHandler uiDataHandler;
    UiTodayWeather* uiTodayWeather = uiDataHandler.getTodayWeatherInfo(weatherData);

    ui->ll_city->setText(uiTodayWeather->city);
    ui->ll_tempture->setText(uiTodayWeather->tempture);
    ui->ll_tempture_range->setText(uiTodayWeather->temptureRange);
    ui->ll_type->setText(uiTodayWeather->type);
    QString pic = uiTodayWeather->icon;
    QPixmap pix = QPixmap(pic);
    ui->ll_state_pic->setPixmap(pix);
    ui->ll_state_pic->setScaledContents(true);
}

void UiUpdater::updateTodayWeatherExtraInfo(Ui::MainWindow *ui, WeatherData *weatherData)
{

    UiDataHandler uiDataHandler;
    UiTodayExtraInfo* uiTodayExtraInfo = uiDataHandler.getTodayWeatherExtraInfo(weatherData);

    ui->ll_ganmao->setText(uiTodayExtraInfo->ganmao);

    for(int i = 0;i < uiTodayExtraInfo->extraInfoItemList.size(); i++){
        if(i == 0){
            QPixmap pixmap = QPixmap(uiTodayExtraInfo->extraInfoItemList[i].icon);
            ui->ll_wind_icon->setPixmap(pixmap);
            ui->ll_wind_icon->setScaledContents(true);
            ui->ll_wind->setText(uiTodayExtraInfo->extraInfoItemList[i].title);
            ui->ll_wind_value->setText( uiTodayExtraInfo->extraInfoItemList[i].degree);
        }else if(i == 1){
            QPixmap pixmap = QPixmap(uiTodayExtraInfo->extraInfoItemList[i].icon);
            ui->ll_pm25_icon->setPixmap(pixmap);
            ui->ll_pm25_icon->setScaledContents(true);
            ui->ll_pm25->setText(uiTodayExtraInfo->extraInfoItemList[i].title);
            ui->ll_pm25_value->setText( uiTodayExtraInfo->extraInfoItemList[i].degree);
        }else if(i == 2){
            QPixmap pixmap = QPixmap(uiTodayExtraInfo->extraInfoItemList[i].icon);
            ui->ll_wet_icon->setPixmap(pixmap);
            ui->ll_wet_icon->setScaledContents(true);
            ui->ll_wet->setText(uiTodayExtraInfo->extraInfoItemList[i].title);
            ui->ll_wet_value->setText( uiTodayExtraInfo->extraInfoItemList[i].degree);

        }else if(i == 3){
            QPixmap pixmap = QPixmap(uiTodayExtraInfo->extraInfoItemList[i].icon);
            ui->ll_air_icon->setPixmap(pixmap);
            ui->ll_air_icon->setScaledContents(true);
            ui->ll_air_quality->setText(uiTodayExtraInfo->extraInfoItemList[i].title);
            ui->ll_air_value->setText( uiTodayExtraInfo->extraInfoItemList[i].degree);
        }

    }
}

void UiUpdater::updateRecentDayWeather(Ui::MainWindow *ui, WeatherData *weatherData)
{

    UiDataHandler uiDataHandler;
    QList<UiRecentDayWeather>* uiRecentDayWeatherList = uiDataHandler.getRecentDayWeatherExtraInfo(weatherData);

    for (int i = 0; i < uiRecentDayWeatherList->size();i++) {
        if(i < weekDayViewList.size()){
            if(i == 0){
                weekDayViewList[i]->setText("今天");
            }else if(i == 1){
                weekDayViewList[i]->setText("明天");
            }
            else {
                weekDayViewList[i]->setText(uiRecentDayWeatherList->at(i).dayWeek);
            }
        }
        if(i < weekViewList.size()){
            weekViewList[i]->setText(uiRecentDayWeatherList->at(i).date);
        }
        if(i < typeIconViewList.size()){
            QPixmap pixmap = QPixmap(uiRecentDayWeatherList->at(i).icon);
            typeIconViewList[i]->setPixmap(pixmap);
        }
        if(i < typeNameViewList.size()){
            typeNameViewList[i]->setText(uiRecentDayWeatherList->at(i).type);
        }
        if(i < airQualityViewList.size()){
            airQualityViewList[i]->setText(uiRecentDayWeatherList->at(i).airQuality);
            airQualityViewList[i]->setStyleSheet(uiRecentDayWeatherList->at(i).style);
        }
        if(i < windViewList.size()){
            windViewList[i]->setText(uiRecentDayWeatherList->at(i).windDirection);
        }
        if(i < windValueViewList.size()){
            windValueViewList[i]->setText(uiRecentDayWeatherList->at(i).windDegree);
        }

    }
}

void UiUpdater::updateTitle(Ui::MainWindow *ui, WeatherData *weatherData)
{
    QString date = QDateTime::fromString(weatherData->date,"yyyyMMdd").toString("yyyy/MM/dd");
    QString title = date + " " + weatherData->data.forecast[0].week;
    ui->ll_date->setText(title);
}

void UiUpdater::updateTempCurveData(Ui::MainWindow *ui, WeatherData *weatherData)
{
    QList<Forecast> forecastList = weatherData->data.forecast;

    for (int i = 0; i<DEFAULT_WEATHER_DAY ;i++) {
        if(i >= forecastList.size()){
            return;
        }

        QString highTemp = forecastList[1].high;
        QString lowTemp = forecastList[1].low;
        if(forecastList[i].high.split(" ").size() > 1){
            highTemp = forecastList[i].high.split(" ")[1];
        }

        if(forecastList[i].low.split(" ").size() > 1){
            lowTemp = forecastList[i].low.split(" ")[1];
        }

        highTemps[i] = highTemp.remove("℃").toInt();
        lowTemps[i] = lowTemp.remove("℃").toInt();

        qDebug() << "highTemp:" << highTemp << "highTemps[i]:" << highTemps[i];
        qDebug() << "lowTemp:" << lowTemp << "lowTemps[i]:" << lowTemps[i];
    }
}

void UiUpdater::drawHighCurve(Ui::MainWindow *ui)
{
    for(int i = 0;i< DEFAULT_WEATHER_DAY;i++){
        qDebug() << "highTemps[i]:" << highTemps[i];
    }

    //后续的绘制用的是ll_high_curve的坐标系
    QPainter painter(ui->ll_high_curve);
    //抗锯齿
    painter.setRenderHint(QPainter::Antialiasing,true);

    qDebug() << "ui->ll_high_curve->x():" << ui->ll_high_curve->x();
    qDebug() << "ui->ll_high_curve->width():" << ui->ll_high_curve->width();


    int pointX[DEFAULT_WEATHER_DAY] = {0};
    for (int i = 0; i < DEFAULT_WEATHER_DAY; i++) {
        pointX[i] = ui->ll_high_curve->x() + DEFAULT_CURVE_PADDING
                + (ui->ll_high_curve->width() - 2 * DEFAULT_CURVE_PADDING)/(DEFAULT_WEATHER_DAY - 1) * i;

        qDebug() << "drawHighCurve pointX:" << pointX[i];

    }

    qDebug() << "ui->ll_high_curve->y():" << ui->ll_high_curve->y();
    qDebug() << "ui->ll_high_curve->height():" << ui->ll_high_curve->height();

    int pointY[DEFAULT_WEATHER_DAY] = {0};

    int centerY = ui->ll_high_curve->height()/2;

    qDebug() << "centerY:" << centerY;

    float averageTemp = 0.0f;

    float sum = 0;
    int largest = highTemps[0];
    int smallest = highTemps[0];


    for(int i = 0;i< DEFAULT_WEATHER_DAY;i++){
        sum += highTemps[i];
        if(largest < highTemps[i]){
            largest = highTemps[i];
        }else if(smallest > highTemps[i]){
            smallest = highTemps[i];
        }
        qDebug() << "highTemps[i]:" << highTemps[i];
    }

    averageTemp = sum / DEFAULT_WEATHER_DAY;

    qDebug() << "sum:" << sum;
    qDebug() << "largest:" << largest;
    qDebug() << "smallest:" << smallest;
    qDebug() << "averageTemp:" << averageTemp;

    float largeDistance  = largest - averageTemp;
    float smallDistance  = averageTemp - smallest;
    //每一度对应的像素步长
    float curveStep = 0;

    if(largeDistance > smallDistance){
        curveStep = (ui->ll_high_curve->height()/2 - DEFAULT_CURVE_VERTAICAL_PADDING)/largeDistance;
    } else {
        curveStep = (ui->ll_high_curve->height()/2 - DEFAULT_CURVE_VERTAICAL_PADDING)/smallDistance;
    }

    qDebug() << "curveStep:" << curveStep;
    qDebug() << "centerY:" << centerY;


    for(int i = 0;i< DEFAULT_WEATHER_DAY;i++){
        pointY[i] = centerY - (highTemps[i] - averageTemp) * curveStep;
    }

    QPen pen = painter.pen();
    pen.setWidth(1);
    pen.setColor(QColor(255,160,122));
    painter.setBrush(QColor(255,160,122));

    for(int i = 0;i< DEFAULT_WEATHER_DAY;i++){
        qDebug() << "painter.drawHighCurve:" << "pointX[i]:" << pointX[i] << "pointY[i]:" << pointY[i];

        painter.drawEllipse(QPoint(pointX[i],pointY[i]),DEFAULT_CURVE_POINT_RADIUS,DEFAULT_CURVE_POINT_RADIUS);
        painter.drawText(pointX[i] - DEFAULT_TEXT_OFFSET_X,pointY[i] - DEFAULT_TEXT_OFFSET_Y,QString::number(highTemps[i]) + "℃");


        if(i < DEFAULT_WEATHER_DAY - 1){
            painter.drawLine(pointX[i],pointY[i],pointX[i+1],pointY[i+1]);
        }
    }
}

void UiUpdater::drawLowCurve(Ui::MainWindow *ui)
{
    for(int i = 0;i< DEFAULT_WEATHER_DAY;i++){
        qDebug() << "lowTemps[i]:" << lowTemps[i];
    }

    //后续的绘制用的是ll_low_curve的坐标系
    QPainter painter(ui->ll_low_curve);
    //抗锯齿
    painter.setRenderHint(QPainter::Antialiasing,true);

    qDebug() << "ui->ll_low_curve->x():" << ui->ll_low_curve->x();
    qDebug() << "ui->ll_low_curve->width():" << ui->ll_low_curve->width();


    int pointX[DEFAULT_WEATHER_DAY] = {0};
    for (int i = 0; i < DEFAULT_WEATHER_DAY; i++) {
        pointX[i] = ui->ll_low_curve->x() + DEFAULT_CURVE_PADDING
                + (ui->ll_low_curve->width() - 2 * DEFAULT_CURVE_PADDING)/(DEFAULT_WEATHER_DAY - 1) * i;

        qDebug() << "drawHighCurve pointX:" << pointX[i];

    }

    qDebug() << "ui->ll_low_curve->y():" << ui->ll_low_curve->y();
    qDebug() << "ui->ll_low_curve->height():" << ui->ll_low_curve->height();

    int pointY[DEFAULT_WEATHER_DAY] = {0};
    int centerY = ui->ll_low_curve->height()/2;

    qDebug() << "centerY:" << centerY;

    float averageTemp = 0.0f;


    float sum = 0;
    int largest = lowTemps[0];
    int smallest = lowTemps[0];


    for(int i = 0;i< DEFAULT_WEATHER_DAY;i++){
        sum += lowTemps[i];
        if(largest < lowTemps[i]){
            largest = lowTemps[i];
        }else if(smallest > lowTemps[i]){
            smallest = lowTemps[i];
        }
        qDebug() << "lowTemps[i]:" << lowTemps[i];
    }

    averageTemp = sum / DEFAULT_WEATHER_DAY;

    qDebug() << "sum:" << sum;
    qDebug() << "largest:" << largest;
    qDebug() << "smallest:" << smallest;
    qDebug() << "averageTemp:" << averageTemp;

    float largeDistance  = largest - averageTemp;
    float smallDistance  = averageTemp - smallest;

    qDebug() << "largeDistance:" << largeDistance;
    qDebug() << "smallDistance:" << smallDistance;

    //每一度对应的像素步长
    float curveStep = 0;

    if(largeDistance > smallDistance){
        curveStep = (ui->ll_low_curve->height()/2 - DEFAULT_CURVE_VERTAICAL_PADDING)/largeDistance;
    } else {
        curveStep = (ui->ll_low_curve->height()/2 - DEFAULT_CURVE_VERTAICAL_PADDING)/smallDistance;
    }

    qDebug() << "curveStep:" << curveStep;
    qDebug() << "centerY:" << centerY;


    for(int i = 0;i< DEFAULT_WEATHER_DAY;i++){
        pointY[i] = centerY - (lowTemps[i] - averageTemp) * curveStep;
    }

    QPen pen = painter.pen();
    pen.setWidth(1);
    pen.setColor(QColor(23,160,45));
    painter.setBrush(QColor(23,160,45));

    for(int i = 0;i< DEFAULT_WEATHER_DAY;i++){

        qDebug() << "painter.drawLowCurve:" << "pointX[i]:" << pointX[i] << "pointY[i]:" << pointY[i];

        painter.drawEllipse(QPoint(pointX[i],pointY[i]),DEFAULT_CURVE_POINT_RADIUS,DEFAULT_CURVE_POINT_RADIUS);
        painter.drawText(pointX[i] - DEFAULT_TEXT_OFFSET_X,pointY[i] - DEFAULT_TEXT_OFFSET_Y,QString::number(lowTemps[i]) + "℃");

        if(i < DEFAULT_WEATHER_DAY - 1){
            painter.drawLine(pointX[i],pointY[i],pointX[i+1],pointY[i+1]);
        }


    }


}
