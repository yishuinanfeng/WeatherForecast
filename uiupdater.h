#ifndef UIUPDATER_H
#define UIUPDATER_H

#include "mainwindow.h"
#include "weatherdata.h"


/**
 * @brief The UiUpdater class
 * 界面视图刷新逻辑处理器
 */
class UiUpdater
{
public:
    UiUpdater(Ui::MainWindow *ui);
    /**
     * @brief update
     * @param ui
     * 刷新界面视图
     */
    void update(Ui::MainWindow *ui,WeatherData *weatherData);

private:
    QList<QLabel*> weekViewList;
    QList<QLabel*> weekDayViewList;
    QList<QLabel*> typeIconViewList;
    QList<QLabel*> typeNameViewList;
    QList<QLabel*> airQualityViewList;
    QList<QLabel*> windViewList;
    QList<QLabel*> windValueViewList;

    void updateTodayWeather(Ui::MainWindow *ui,WeatherData *weatherData);
    void updateTodayWeatherExtraInfo(Ui::MainWindow *ui,WeatherData *weatherData);
    void updateRecentDayWeather(Ui::MainWindow *ui,WeatherData *weatherData);
    void updateTitle(Ui::MainWindow *ui,WeatherData *weatherData);
};

#endif // UIUPDATER_H
