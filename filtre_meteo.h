#include <QDebug>

#ifndef FILTRE_METEO_H
#define FILTRE_METEO_H


class filtre_meteo
{
public:
    filtre_meteo();
    QString   trieData(QString Databrut);

    double getVitesse_vent() const;
    double getTemperature() const;
    double getPression_atmo() const;
    double getLongitude() const;
    double getLatitude() const;
    double getDegre_vent() const;

private :
    QString m_data_non_filtr;
    double m_vitesse_vent;
    double m_temperature;
    double m_pression_atmo;
    double kmENnoeuds(double kmh) const;
    double m_longitude;
    double m_latitude;
    double m_deg_vent;
};

#endif // FILTRE_METEO_H
