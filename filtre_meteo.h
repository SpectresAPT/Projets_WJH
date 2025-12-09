#include <QDebug>

#ifndef FILTRE_METEO_H
#define FILTRE_METEO_H


class filtre_meteo
{
public:
    filtre_meteo();
    QString   trieData(QString Databrut);

private :
    QString m_data_non_filtr;
};

#endif // FILTRE_METEO_H
