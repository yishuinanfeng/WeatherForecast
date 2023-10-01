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
    UiUpdater();
    /**
     * @brief update
     * @param ui
     * 刷新界面视图
     */
    void update(Ui::MainWindow *ui,WeatherData *weatherData);

private:
    void updateTodayWeather(Ui::MainWindow *ui,WeatherData *weatherData);
    void updateTodayWeatherExtraInfo(Ui::MainWindow *ui,WeatherData *weatherData);
    void updateRecentDayWeather(Ui::MainWindow *ui,WeatherData *weatherData);
};

#endif // UIUPDATER_H
