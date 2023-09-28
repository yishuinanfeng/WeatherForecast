#ifndef UIDATAHANDLER_H
#define UIDATAHANDLER_H

#include "UiWeatherBean.h"
#include "weatherdata.h"

#include <QMap>
#include <QList>


/**
 * @brief The UiDataHandler class
 * 将原始数据实体对象转化为展示UI实体对象
 */
class UiDataHandler
{
private:
    QMap<QString,QString> weatherTypeMap;

public:
    UiDataHandler();

    UiTodayWeather* getTodayWeatherInfo(WeatherData *weather);

    UiTodayExtraInfo* getTodayWeatherExtraInfo(WeatherData *weather);

    QList<UiRecentDayWeather>* getRecentDayWeatherExtraInfo(WeatherData *weather);

    UiTitle* getTitleInfo(WeatherData *weather);
};

#endif // UIDATAHANDLER_H
