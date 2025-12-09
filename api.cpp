#include "api.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QObject>
#include <QUrl>

API::API() {
    m_API_key="";
    m_ville="";
    m_meteo_data="";

}

QString API::getville()
{
    return m_ville;
}

QString API::getmeteo_data()
{
    return m_meteo_data;
}

QString API::getAPIkey()
{
    return m_API_key;
}

void API::setAPIkey(QString api_key){
    m_API_key=api_key;
}

void API::setville(QString ville){
    m_ville=ville;
}

void API::setmeteo_data(QString meteo_data){
    m_meteo_data=meteo_data;
}



QString API::apiRequest(QString API_key,QString ville){

    QString   url="https://api.openweathermap.org/data/2.5/weather?q=" + ville + ",fr&appid=" + API_key + "&units=metric&lang=fr";

    QNetworkAccessManager manager;

    QNetworkRequest req;
    req.setUrl(QUrl(url));

    QEventLoop loop;
    QNetworkReply* reply = manager.get(req);

    // On attend que la réponse arrive
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    // Lecture de la réponse
    QString reponse = QString::fromUtf8(reply->readAll());

    reply->deleteLater();
    return reponse;
}
