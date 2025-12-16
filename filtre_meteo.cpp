#include "filtre_meteo.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

using namespace std;


filtre_meteo::filtre_meteo()
{
    m_data_non_filtr = "";
    m_vitesse_vent = 0.0;
    m_temperature = 0.0;
    m_pression_atmo = 0.0;
}

double filtre_meteo::kmENnoeuds(double kmh) const
{
    return kmh / 1.852;
}


QString filtre_meteo::trieData(QString Databrut)
{
    QString dataclean;
    m_data_non_filtr = Databrut;

    QJsonDocument jsonDoc = QJsonDocument::fromJson(Databrut.toUtf8());

    if (jsonDoc.isNull()) {
        qDebug() << "Erreur: JSON invalide";
        return "Erreur: JSON invalide";
    }

    QJsonObject jsonObj = jsonDoc.object();

    if (jsonObj.contains("wind") && jsonObj["wind"].isObject())
    {
        QJsonObject wind = jsonObj["wind"].toObject();

        if (wind.contains("speed")) {
            double vitesse_ms = wind["speed"].toDouble();
            double vitesse_kmh = vitesse_ms * 3.6;
            m_vitesse_vent = kmENnoeuds(vitesse_kmh);
        }
    }

    if (jsonObj.contains("main") && jsonObj["main"].isObject())
    {
        QJsonObject main = jsonObj["main"].toObject();

        if (main.contains("temp"))
        {
            m_temperature = main["temp"].toDouble();
        }

        if (main.contains("pressure"))
        {
            m_pression_atmo = main["pressure"].toDouble();
        }
    }

    dataclean = QString("Vitesse du vent: %1 noeuds\n"
                       "Température: %2 °C\n"
                       "Pression: %3 hPa")
                .arg(m_vitesse_vent)
                .arg(m_temperature)
                .arg(m_pression_atmo);

    qDebug() << "Données filtrées:" << dataclean;

    return dataclean;
}

double filtre_meteo::getVitesse_vent() const
{
    return m_vitesse_vent;
}

double filtre_meteo::getTemperature() const
{
    return m_temperature;
}

double filtre_meteo::getPression_atmo() const
{
    return m_pression_atmo;
}
