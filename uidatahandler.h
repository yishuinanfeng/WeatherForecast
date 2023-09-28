#ifndef UIDATAHANDLER_H
#define UIDATAHANDLER_H

#include "UiWeatherBean.h"
#include "weatherdata.h"



/**
 * @brief The UiDataHandler class
 * 将原始数据实体对象转化为展示UI实体对象
 */
class UiDataHandler
{
public:
    UiDataHandler();

    UiTodayWeather getTodayWeatherInfo(WeatherData *weather);

    UiTodayExtraInfo getTodayWeatherExtraInfo(WeatherData *weather);

    UiRecentDayWeather getRecentDayWeatherExtraInfo(WeatherData *weather);
};

#endif // UIDATAHANDLER_H
