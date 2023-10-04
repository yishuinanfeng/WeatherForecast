#include <QList>
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
    QString icon = "";
    QString tempture = "";
    QString city = "";
    QString temptureRange = "";
    QString type = "";
};

class UiTodayExtraInfoItem{
public:
    UiTodayExtraInfoItem(){}

    QString icon = "";
    QString title = "";
    QString degree = "";
};

class UiTodayExtraInfo{
public:
    QString ganmao = "";
    QList<UiTodayExtraInfoItem> extraInfoItemList = QList<UiTodayExtraInfoItem>();
};

class UiRecentDayWeather{
public:
    QString dayWeek = "";
    QString date = "";
    QString type = "";
    QString icon = "";
    QString airQuality = "";
    QString windDirection = "";
    QString style = "";
    QString windDegree = "";
};

class UiTitle{
public:
    QString title = "";
};


