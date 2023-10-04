#include <QString>
#include <QMap>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <qdebug.h>


#ifndef CITYCODEUTIL_H
#define CITYCODEUTIL_H

#endif // CITYCODEUTIL_H

class CityCodeUtil{
private:
    static QMap<QString,QString> cityCodeMap;

    static void initCityCode(){
        QString path = "://res/citycode.json";
        QFile cityFile(path);
        cityFile.open(QIODevice::ReadOnly | QIODevice::Text);
        QByteArray cityData = cityFile.readAll();
        cityFile.close();

        QJsonParseError err;
        QJsonDocument document = QJsonDocument::fromJson(cityData,&err);
        if(err.error != QJsonParseError::NoError){
            qDebug() << "initCityCode error:" << err.error;
            return;
        }

        if(!document.isArray()){
            qDebug() << "!document.isArray()";
            return;
        }

        QJsonArray cityArray = document.array();
        for(int i = 0; i < cityArray.size(); i++){
            QJsonValueRef cityJsonObject = cityArray[i];
            QString cityName = cityJsonObject.toObject().value("city_name").toString();
            QString cityCode = cityJsonObject.toObject().value("city_code").toString();
            qDebug() << "cityName:" + cityName + "cityCode" + cityCode;
            if(cityCode.size() > 0){
                cityCodeMap.insert(cityName,cityCode);
            }
        }
    }
public:
    static QString getCityCode(QString cityName){
        if(cityCodeMap.isEmpty()){
            initCityCode();
        }

        QString result = cityCodeMap[cityName];

        if(cityName.contains("市")){
            cityName = cityName.remove("市");
            result = cityCodeMap[cityName];
        }

        if(result == nullptr){
            result = "";
        }

        return result;
    }
};

QMap<QString,QString> CityCodeUtil::cityCodeMap = {};
