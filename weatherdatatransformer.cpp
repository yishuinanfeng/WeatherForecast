#include "weatherdatatransformer.h"

#include <QJsonObject>
#include <QJsonParseError>
#include <QDebug>
#include <QJsonArray>

WeatherDataTransformer::WeatherDataTransformer()
{

}

WeatherData WeatherDataTransformer::parseJson(QByteArray *byteArray)
{
    QJsonParseError error;
    // 将QByteArray转换为QJsonDocument
    QJsonDocument jsonDoc = QJsonDocument::fromJson(*byteArray,&error);

    if(error.error != QJsonParseError::NoError){
        return WeatherData();
    }

    WeatherData weatherData;
    // 检查转换是否成功
    if (!jsonDoc.isNull()) {
        // 将QJsonDocument转换为QJsonObject
        QJsonObject jsonObj = jsonDoc.object();

        // 访问JSON对象的键值对
        QString date = jsonObj["date"].toString();
        QString time = jsonObj["time"].toString();

        weatherData.date = date;
        weatherData.time = time;

        QJsonObject cityObject = jsonObj.value("cityInfo").toObject();
        QJsonObject dataObject = jsonObj.value("data").toObject();

        weatherData.cityInfo = getCityInfoFromJson(&cityObject);
        weatherData.data = getDataFromJson(&dataObject);

        // 打印键值对
//        qDebug() << "date: " << date;
//        qDebug() << "time: " << time;
    } else {
        qDebug() << "Failed to parse JSON.";
    }

//    qDebug() << "weatherData: " << weatherData;

    return weatherData;
}

CityInfo WeatherDataTransformer::getCityInfoFromJson(QJsonObject *cityObject)
{
    CityInfo cityInfo;

    cityInfo.city = cityObject->value("city").toString();
    cityInfo.citykey = cityObject->value("citykey").toString();
    cityInfo.parent = cityObject->value("parent").toString();
    cityInfo.updateTime = cityObject->value("updateTime").toString();

    return cityInfo;
}

Data WeatherDataTransformer::getDataFromJson(QJsonObject *dataObject)
{
    Data data;

    data.shidu = dataObject->value("updateTime").toString();
    data.pm25 = dataObject->value("updateTime").toInt();
    data.pm10 = dataObject->value("updateTime").toInt();
    data.quality = dataObject->value("updateTime").toString();
    data.wendu = dataObject->value("updateTime").toString();
    data.ganmao = dataObject->value("updateTime").toString();

    QJsonArray forecast = dataObject->value("forecast").toArray();
    // 使用迭代器遍历QJsonArray
    for (QJsonArray::const_iterator it = forecast.constBegin(); it != forecast.constEnd(); ++it) {
        QJsonValue value = *it;
        QJsonObject jsonObj = value.toObject();
        // 处理每个元素
        Forecast forecast;
        forecast.date = jsonObj.value("aqi").toString();
        forecast.high = jsonObj.value("high").toString();
        forecast.low = jsonObj.value("low").toString();
        forecast.ymd = jsonObj.value("ymd").toString();
        forecast.week = jsonObj.value("week").toString();
        forecast.sunrise = jsonObj.value("sunrise").toString();
        forecast.sunset = jsonObj.value("sunset").toString();
        forecast.aqi = jsonObj.value("aqi").toInt();
        forecast.fx = jsonObj.value("fx").toString();
        forecast.fl = jsonObj.value("fl").toString();
        forecast.type = jsonObj.value("type").toString();
        forecast.notice = jsonObj.value("notice").toString();
        data.forecast.append(forecast);
    }

    return data;
}
