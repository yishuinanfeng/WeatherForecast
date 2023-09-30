#include "uidatahandler.h"
#include "uiupdater.h"

#include <QList>
#include <ui_mainwindow.h>

UiUpdater::UiUpdater()
{


}

void UiUpdater::update(Ui::MainWindow *ui,WeatherData *weatherData)
{
    updateTodayWeather(ui,weatherData);
    updateTodayWeatherExtraInfo(ui,weatherData);
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
