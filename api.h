#ifndef API_H
#define API_H
#include <QDebug>

class API

{
public:
    API();
    //geter
    QString getville();
    QString getAPIkey();
    //seter
    void setAPIkey(QString api_key);
    void setville(QString ville);


private:
    QString m_API_key;
    QString m_ville;


};

#endif // API_H
