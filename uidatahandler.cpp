#include "uidatahandler.h"

#include <QDateTime>

UiDataHandler::UiDataHandler()
{
    weatherTypeMap.insert("暴雪",":/res/type/BaoXue.png");
    weatherTypeMap.insert("暴雨",":/res/type/BaoYu.png");
    weatherTypeMap.insert("暴雨到大暴雨",":/res/type/BaoYuDaoDaBaoYu.png");
    weatherTypeMap.insert("大暴雨",":/res/type/DaBaoYu.png");
    weatherTypeMap.insert("大暴雨到特大暴雨",":/res/type/DaBaoYuDaoTeDaBaoYu.png");
    weatherTypeMap.insert("大到暴雪",":/res/type/DaDaoBaoXue.png");
    weatherTypeMap.insert("大到暴雨",":/res/type/DaDaoBaoYu.png");
    weatherTypeMap.insert("大雪",":/res/type/DaXue.png");
    weatherTypeMap.insert("大雨",":/res/type/DaYu.png");
    weatherTypeMap.insert("中雨",":/res/type/DongYu.png");
    weatherTypeMap.insert("小雨",":/res/type/XiaoYu.png");
    weatherTypeMap.insert("多云",":/res/type/DuoYun.png");
    weatherTypeMap.insert("浮尘",":/res/type/FuChen.png");
    weatherTypeMap.insert("雷阵雨",":/res/type/LeiZhenYu.png");
    weatherTypeMap.insert("雷阵雨伴有冰雹",":/res/type/LeiZhenYuBanYouBingBao.png");
    weatherTypeMap.insert("霾",":/res/type/Mai.png");
    weatherTypeMap.insert("强沙尘暴",":/res/type/QiangShaChenBao.png");
    weatherTypeMap.insert("晴",":/res/type/Qing.png");
    weatherTypeMap.insert("沙尘暴",":/res/type/ShaChenBao.png");
    weatherTypeMap.insert("特大暴雨",":/res/type/TeDaBaoYu.png");
    weatherTypeMap.insert("无数据",":/res/type/undefined.png");
    weatherTypeMap.insert("雾",":/res/type/Wu.png");
    weatherTypeMap.insert("小到中雪",":/res/type/XiaoDaoZhongXue.png");
    weatherTypeMap.insert("小到中雨",":/res/type/XiaoDaoZhongYu.png");
    weatherTypeMap.insert("小雪",":/res/type/XiaoXue.png");
    weatherTypeMap.insert("雪",":/res/type/Xue.png");
    weatherTypeMap.insert("扬沙",":/res/type/YangSha.png");
    weatherTypeMap.insert("阴",":/res/type/Yin.png");
    weatherTypeMap.insert("雨",":/res/type/Yu.png");
    weatherTypeMap.insert("雨夹雪",":/res/type/YuJiaXue.png");
    weatherTypeMap.insert("阵雪",":/res/type/ZhenXue.png");
    weatherTypeMap.insert("阵雨",":/res/type/ZhenYu.png");
    weatherTypeMap.insert("中到大雪",":/res/type/ZhongDaoDaXue.png");
    weatherTypeMap.insert("中到大雨",":/res/type/ZhongDaoDaYu.png");
    weatherTypeMap.insert("中雪",":/res/type/ZhongXue.png");
    weatherTypeMap.insert("中雨",":/res/type/ZhongYu.png");

}

UiTodayWeather* UiDataHandler::getTodayWeatherInfo(WeatherData *weather)
{
    UiTodayWeather *uiTodayWeather = new UiTodayWeather();
    QString type = weather->data.forecast[0].type;
    uiTodayWeather->icon = weatherTypeMap[type];
    uiTodayWeather->city = weather->cityInfo.city;
    uiTodayWeather->tempture = weather->data.wendu + "℃";
    uiTodayWeather->type = type;


    QString highTemp = weather->data.forecast[1].high;
    QString lowTemp = weather->data.forecast[1].low;
    if(weather->data.forecast[1].high.split(" ").size() > 1){
       highTemp = weather->data.forecast[1].high.split(" ")[1];
    }

    if(weather->data.forecast[1].low.split(" ").size() > 1){
       lowTemp = weather->data.forecast[1].low.split(" ")[1];
    }
    uiTodayWeather->temptureRange = lowTemp + "~" + highTemp;
    return uiTodayWeather;
}

UiTodayExtraInfo* UiDataHandler::getTodayWeatherExtraInfo(WeatherData *weather)
{
    UiTodayExtraInfo* uiTodayExtraInfo = new UiTodayExtraInfo();
    uiTodayExtraInfo->ganmao = weather->data.ganmao;
    QList<UiTodayExtraInfoItem> extraInfoItemList = QList<UiTodayExtraInfoItem>();
    UiTodayExtraInfoItem uiTodayExtraInfoItem;
    uiTodayExtraInfoItem.icon = ":/res/wind.png";
    uiTodayExtraInfoItem.title = weather->data.forecast[0].fx;
    uiTodayExtraInfoItem.degree = weather->data.forecast[0].fl;
    extraInfoItemList.append(uiTodayExtraInfoItem);

    uiTodayExtraInfoItem.icon = ":/res/pm25.png";
    uiTodayExtraInfoItem.title = "PM2.5";
    uiTodayExtraInfoItem.degree = QString::number(weather->data.pm25);
    extraInfoItemList.append(uiTodayExtraInfoItem);

    uiTodayExtraInfoItem.icon = ":/res/humidity.png";
    uiTodayExtraInfoItem.title = "湿度";
    uiTodayExtraInfoItem.degree = weather->data.shidu;
    extraInfoItemList.append(uiTodayExtraInfoItem);

    uiTodayExtraInfoItem.icon = ":/res/aqi.png";
    uiTodayExtraInfoItem.title = "空气质量";
    uiTodayExtraInfoItem.degree = weather->data.quality;
    extraInfoItemList.append(uiTodayExtraInfoItem);

    uiTodayExtraInfo->extraInfoItemList = extraInfoItemList;
    return uiTodayExtraInfo;
}

QList<UiRecentDayWeather>* UiDataHandler::getRecentDayWeatherExtraInfo(WeatherData *weather)
{
    QList<UiRecentDayWeather> *uiRecentDayWeatherList = new QList<UiRecentDayWeather>();
    UiRecentDayWeather uiRecentDayWeather = UiRecentDayWeather();
    QString date = weather->date;
    qDebug() << "getRecentDayWeatherExtraInfo date: " << date;

    QString month = QDateTime::fromString(date,"yyyyMMdd").toString("yyyy/MM/dd").split("/")[1];
    for (QList<Forecast>::const_iterator it = weather->data.forecast.constBegin(); it != weather->data.forecast.constEnd(); ++it) {
        Forecast forecast = *it;
        uiRecentDayWeather.dayWeek = forecast.week;
        uiRecentDayWeather.date = month + "/" + forecast.date;
        uiRecentDayWeather.type = forecast.type;
        uiRecentDayWeather.icon = weatherTypeMap[forecast.type];

        if(forecast.aqi > 300){
            uiRecentDayWeather.airQuality = "严重";
            uiRecentDayWeather.style = "background-color: rgb(110, 0, 0);";

        }else if (forecast.aqi > 250 && 300 <= forecast.aqi) {
            uiRecentDayWeather.airQuality = "重度";
            uiRecentDayWeather.style = "background-color: rgb(170, 0, 0);";

        }else if(forecast.aqi > 200 && 250 <= forecast.aqi){
            uiRecentDayWeather.airQuality = "中度";
            uiRecentDayWeather.style = "background-color: rgb(200, 20, 0);";

        }
        else if(forecast.aqi > 150 && 200 <= forecast.aqi){
            uiRecentDayWeather.airQuality = "轻度";
            uiRecentDayWeather.style = "background-color: rgb(235, 17, 27);";

        }else if(forecast.aqi > 100 && 150 <= forecast.aqi){
            uiRecentDayWeather.airQuality = "轻微";
            uiRecentDayWeather.style = "background-color: rgb(255, 87, 97);";

        }
        else if(forecast.aqi > 50 && 100 <= forecast.aqi){
            uiRecentDayWeather.airQuality = "良";
            uiRecentDayWeather.style = "background-color: rgb(255, 187, 23);";
        }
        else if(forecast.aqi > 0 || 50 <= forecast.aqi){
            uiRecentDayWeather.airQuality = "优";
            uiRecentDayWeather.style = "background-color: rgb(121, 184, 0);";
        }

        uiRecentDayWeather.dayWeek = forecast.week;
        uiRecentDayWeather.windDirection = forecast.fx;
        uiRecentDayWeather.windDegree = forecast.fl;

        uiRecentDayWeatherList->append(uiRecentDayWeather);
    }

    return uiRecentDayWeatherList;
}

UiTitle *UiDataHandler::getTitleInfo(WeatherData *weather)
{
    UiTitle *uiTitle = new UiTitle();
    Forecast todayForecast = weather->data.forecast[1];
    uiTitle->title = todayForecast.ymd + todayForecast.week;
    return uiTitle;
}
