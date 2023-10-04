#include "uidatahandler.h"
#include "uiupdater.h"

#include <QList>
#include <QStyle>
#include <ui_mainwindow.h>

UiUpdater::UiUpdater(Ui::MainWindow *ui)
{
    weekViewList = QList<QLabel*>();
    typeIconViewList= QList<QLabel*>();
    typeNameViewList= QList<QLabel*>();
    airQualityViewList= QList<QLabel*>();
    windViewList= QList<QLabel*>();
    windValueViewList= QList<QLabel*>();

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

void UiUpdater::update(Ui::MainWindow *ui,WeatherData *weatherData)
{
    updateTodayWeather(ui,weatherData);
    updateTodayWeatherExtraInfo(ui,weatherData);
    updateRecentDayWeather(ui,weatherData);
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
        if(i < weekViewList.size()){
            weekViewList[i]->setText(uiRecentDayWeatherList->at(i).dayWeek);
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
