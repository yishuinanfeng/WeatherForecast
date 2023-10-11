#ifndef UIUPDATER_H
#define UIUPDATER_H


#include "weatherdata.h"

#include <ui_mainwindow.h>

#define DEFAULT_WEATHER_DAY 6
#define DEFAULT_CURVE_STEP 3
#define DEFAULT_CURVE_POINT_RADIUS 3
#define DEFAULT_TEXT_OFFSET_X 4
#define DEFAULT_TEXT_OFFSET_Y 4
#define DEFAULT_CURVE_PADDING 20
#define DEFAULT_CURVE_VERTAICAL_PADDING 15

/**
 * @brief The UiUpdater class
 * 界面视图刷新逻辑处理器
 */
class UiUpdater
{
public:
    UiUpdater(Ui::MainWindow *ui);
    ~UiUpdater();
    /**
     * @brief update
     * @param ui
     * 刷新界面视图
     */
    void update(Ui::MainWindow *ui,WeatherData *weatherData);

private:
    int highTemps[DEFAULT_WEATHER_DAY] = {0};
    int lowTemps[DEFAULT_WEATHER_DAY] = {0};
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
    void updateTempCurveData(Ui::MainWindow *ui,WeatherData *weatherData);

public:
    void drawHighCurve(Ui::MainWindow *ui);
    void drawLowCurve(Ui::MainWindow *ui);
};

#endif // UIUPDATER_H
