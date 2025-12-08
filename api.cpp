#include "api.h"

API::API() {
    m_API_key="";
    m_ville="";
}

QString API::getville()
{
    return m_ville;
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
