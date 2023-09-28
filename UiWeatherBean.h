#include <QString>

#ifndef UIWEATHERBEAN_H
#define UIWEATHERBEAN_H

#endif // UIWEATHERBEAN_H

/**
 * @brief The UiTodayWeather class
 * 直接显示在UI的数据实体类
 */

class UiTodayWeather{
public:
    QString icon;
    int tempture;
    QString city;
    QString temptureRange;
    QString decs;
};

class UiTodayExtraInfo{
public:
    QString icon;
    QString title;
    QString detail;
};

class UiRecentDayWeather{
    QString dayWeek;
    QString date;
    QString decs;
    QString icon;
    QString airQuality;
    QString windDirection;
    QString windDegree;
};


