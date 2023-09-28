#ifndef WEATHERDATATRANSFORMER_H
#define WEATHERDATATRANSFORMER_H

#include "weatherdata.h"
/**
 * @brief The WeatherDataTransformer class
 * 将网络数据转化为实体类
 */
class WeatherDataTransformer
{
public:
    WeatherDataTransformer();

    WeatherData parseJson(QByteArray *byteArray);

    CityInfo getCityInfoFromJson(QJsonObject *jsonObject);

    Data getDataFromJson(QJsonObject *jsonObject);
};

#endif // WEATHERDATATRANSFORMER_H
