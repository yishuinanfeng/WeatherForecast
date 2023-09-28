#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <QDebugStateSaver>
#include <QList>
#include <QString>



/**
  * Copyright 2023 json.cn
  */

class CityInfo {

public:
    QString city;
    QString citykey;
    QString parent;
    QString updateTime;

    CityInfo(){
        city = "北京市";
        citykey = "101010100";
        parent = "北京";
        updateTime = "09:16";
    }

};


class Yesterday {

public:
    QString date;
    QString high;
    QString low;
    QString ymd;
    QString week;
    QString sunrise;
    QString sunset;
    int aqi;
    QString fx;
    QString fl;
    QString type;
    QString notice;

    Yesterday(){
        date = "24";
        high = "高温 20℃";
        low = "低温 16℃";
        ymd = "2023-09-24";
        week = "星期日";
        sunrise = "06:04";
        sunset = "18:09";
        aqi = 0;
        fx = "东南风";
        fl = "1级";
        type = "阴";
        notice = "不要被阴云遮挡住好心情";
    }

};


class Forecast {
public:
    QString date;
    QString high;
    QString low;
    QString ymd;
    QString week;
    QString sunrise;
    QString sunset;
    int aqi;
    QString fx;
    QString fl;
    QString type;
    QString notice;

    Forecast(){
        date = "24";
        high = "高温 20℃";
        low = "低温 16℃";
        ymd = "2023-09-24";
        week = "星期日";
        sunrise = "06:04";
        sunset = "18:09";
        aqi = 0;
        fx = "东南风";
        fl = "1级";
        type = "阴";
        notice = "不要被阴云遮挡住好心情";
    }

};

class Data {

public:
    QString shidu;
    int pm25;
    int pm10;
    QString quality;
    QString wendu;
    QString ganmao;
    QList<Forecast> forecast;
    Yesterday yesterday;

    Data(){
        forecast = QList<Forecast>();
        yesterday = Yesterday();
        pm25 = 28;
        pm10 = 54;
        quality = "良";
        wendu = "16";
        ganmao = "极少数敏感人群应减少户外活动";
    }

    // 重写QDebug输出运算符
        friend QDebug operator<<(QDebug debug, const Data& data) {
            QDebugStateSaver saver(debug);
            debug.nospace() << "WeatherData(pm25: " << data.pm25 << ", pm10: " << data.pm10 << ")";
            return debug;
        }
};

class WeatherData {

public:
    QString message;
    int status;
    QString date;
    QString time;
    CityInfo cityInfo;
    Data data;

    WeatherData(){
        message = "success感谢又拍云(upyun.com)提供CDN赞助";
        status = 200;
        date = "20230925";
        time = "2023-09-25 12:41:50";
        cityInfo = CityInfo();
        data = Data();
    }

    // 重写QDebug输出运算符
        friend QDebug operator<<(QDebug debug, const WeatherData& data) {
            QDebugStateSaver saver(debug);
            debug.nospace() << "WeatherData(date: " << data.date << ", time: " << data.time << ")";
            return debug;
        }

};


#endif // WEATHERDATA_H
