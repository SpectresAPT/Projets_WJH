#include "WJH.h"
#include "ui_WJH.h"
#include <iostream>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connecter le signal au slot
    connect(ui->input_temp, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::onTempChanged);

    connect(ui->input_vent, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::onventChanged);

    connect(ui->input_atmo, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::onatmoChanged);

    connect(ui->input_api_keys, &QLineEdit::textChanged,
            this, &MainWindow::onAPIkeys);

    connect(ui->input_ville, &QLineEdit::textChanged,
            this, &MainWindow::onCITY);

    connect(ui->API_Start_B, &QPushButton::clicked,
            this, &MainWindow::appelAPI);

}


MainWindow::~MainWindow()
{
    delete ui;
}




// Définition de la fonction slot
void MainWindow::onTempChanged(int value)
{
    qDebug() << "Nouvelle température:" << value;
    a.set_d_temp(value);
    change_labels(a.get_danger());




}

void MainWindow::onventChanged(int value)
{
    qDebug() << "Nouvelle vent:" << value;
    a.set_d_vent(value);
    change_labels(a.get_danger());


}

void  MainWindow::onatmoChanged(int value)
{
    qDebug() << "Nouvelle P atmo:" << value;
    a.set_d_atmo(value);
    change_labels(a.get_danger());


}

void MainWindow::onAPIkeys(QString api) {
    qDebug() << "Nouvelle cle API:" << api;
    int longueur_api = api.length();
    qDebug() << longueur_api;
    info.setAPIkey(api);
}

void MainWindow::onCITY(QString ville) {
    qDebug() << "Nouvelle Ville : " << ville;
    info.setville(ville);

}

bool MainWindow::apierror(QString message)
{
    if (message.contains("cod\":\"404\"")) {
        qDebug() << "Erreur 400 - Mauvaise requête (message serveur = " << message << ")";
        ui->log_API->setText(QString("Erreur 400 - Mauvaise requête. Message serveur = %1").arg(message));
        ui->log_API->setStyleSheet("color: red;");
        return true;
    }
    else if (message.contains("cod\":\"401\"")) {
        qDebug() << "Erreur 401 - Non autorisé, authentification requise (message serveur = " << message << ")";
        ui->log_API->setText(QString("Erreur 401 - Authentification requise. Message serveur = %1").arg(message));
        ui->log_API->setStyleSheet("color: red;");
        return true;
    }
    else if (message.contains("cod\":\"403\"")) {
        qDebug() << "Erreur 403 - Accès interdit (message serveur = " << message << ")";
        ui->log_API->setText(QString("Erreur 403 - Accès interdit. Message serveur = %1").arg(message));
        ui->log_API->setStyleSheet("color: red;");
        return true;
    }
    else if (message.contains("cod\":\"405\"")) {
        qDebug() << "Erreur 405 - Méthode non autorisée (message serveur = " << message << ")";
        ui->log_API->setText(QString("Erreur 405 - Méthode non autorisée. Message serveur = %1").arg(message));
        ui->log_API->setStyleSheet("color: red;");
        return true;
    }
    else if (message.contains("cod\":\"408\"")) {
        qDebug() << "Erreur 408 - Délai d'attente dépassé (message serveur = " << message << ")";
        ui->log_API->setText(QString("Erreur 408 - Délai d'attente dépassé. Message serveur = %1").arg(message));
        ui->log_API->setStyleSheet("color: red;");
        return true;
    }
    else if (message.contains("cod\":\"429\"")) {
        qDebug() << "Erreur 429 - Trop de requêtes, veuillez réessayer plus tard (message serveur = " << message << ")";
        ui->log_API->setText(QString("Erreur 429 - Trop de requêtes. Message serveur = %1").arg(message));
        ui->log_API->setStyleSheet("color: orange;");
        return true;
    }
    // Erreurs 5xx - Erreurs Serveur
    else if (message.contains("cod\":\"500\"")) {
        qDebug() << "Erreur 500 - Erreur interne du serveur (message serveur = " << message << ")";
        ui->log_API->setText(QString("Erreur 500 - Erreur interne du serveur. Message serveur = %1").arg(message));
        ui->log_API->setStyleSheet("color: red;");
        return true;
    }
    else if (message.contains("cod\":\"502\"")) {
        qDebug() << "Erreur 502 - Mauvaise passerelle (message serveur = " << message << ")";
        ui->log_API->setText(QString("Erreur 502 - Mauvaise passerelle. Message serveur = %1").arg(message));
        ui->log_API->setStyleSheet("color: red;");
        return true;
    }
    else if (message.contains("cod\":\"503\"")) {
        qDebug() << "Erreur 503 - Service temporairement indisponible (message serveur = " << message << ")";
        ui->log_API->setText(QString("Erreur 503 - Service indisponible. Message serveur = %1").arg(message));
        ui->log_API->setStyleSheet("color: orange;");
        return true;
    }
    else if (message.contains("cod\":\"504\"")) {
        qDebug() << "Erreur 504 - Délai d'attente de la passerelle dépassé (message serveur = " << message << ")";
        ui->log_API->setText(QString("Erreur 504 - Délai d'attente dépassé. Message serveur = %1").arg(message));
        ui->log_API->setStyleSheet("color: red;");
        return true;
    }
    // Cas par défaut ( code == 200)
    else {
        qDebug () << "pas d'erreur dans la reseption API";
        ui->log_API->setText("Pas d'erreur pour la moment");
        ui->log_API->setStyleSheet("color: green;");
        return false;
    }
}
void MainWindow::appelAPI() {
    QString api_key;
    QString ville;
    qDebug() << "config appel API ";
    api_key=info.getAPIkey();
    qDebug() << "longeur clée API " << api_key.length() ;
    if (api_key.length()==32){

        qDebug() << "nouvelle API KEY Appliquer";
        ui->label_api->setText("la clée API est vide.");
        qDebug()<<"clé API est valide | appel API non lancer";
        ui->label_api->setStyleSheet("color: green;");

        ville=info.getville();
        qDebug() << "nouvelle ville : " << ville;
        qDebug() << "lancement appel API ";
        info.setmeteo_data(info.apiRequest(api_key,ville));
        qDebug() << "meteo data :" << info.getmeteo_data();
        QString dataClear = fi.trieData(info.getmeteo_data());
        QString message = info.getmeteo_data();

        //gestion erreur API
        if (apierror(message)==false){


            ui->label_API_vent->setText(QString("vitesse de vent en noeud : %1").arg(fi.getVitesse_vent()));
            ui->label_API_temp->setText(QString("température en °C : %1").arg(fi.getTemperature()));
            ui->label_API_atmo->setText(QString("pression atmospherique : %1").arg(fi.getPression_atmo()));
            ui->City_long->setText(QString("longitude de la ville : %1").arg(fi.getLongitude()));
            ui->City_lat->setText(QString("latitude de la ville : %1").arg(fi.getLatitude()));


            a.set_d_atmo(fi.getPression_atmo());
            a.set_d_temp(fi.getTemperature());
            a.set_d_vent(fi.getVitesse_vent());
            change_labelsAPI(a.get_danger());

            QString degW = mettreAJourDirectionVent(fi.getDegre_vent());
            ui->deg_vent->setText(degW);




        }
        else {
            ui->label_api->setText("Votre clé API est invalide");
            ui->label_api->setStyleSheet("color: red;");
            qDebug()<<"clé API est invalide | appel API non lancer";
        }


    }

}

QString MainWindow::mettreAJourDirectionVent(double deg) {

    // Conversion en int pour faciliter les comparaisons (le cast est automatique)
    int d = static_cast<int>(deg);

    // Sécurité au cas où on reçoit des doubles bizarres, bien que vous ayez dit que c'est normalisé.
    // (Optionnel si vous êtes sûr de vos données 0-359)
    // d = d % 360;
    // if (d < 0) d += 360;

    if ((d >= 337 && d <= 359) || (d >= 0 && d < 22)) {
        return "↑"; // Nord
    } else if (d >= 22 && d < 67) {
        return "⬈"; // Nord-Est
    } else if (d >= 67 && d < 112) {
        return "→"; // Est
    } else if (d >= 112 && d < 157) {
        return "⬊"; // Sud-Est
    } else if (d >= 157 && d < 202) {
        return "↓"; // Sud
    } else if (d >= 202 && d < 247) {
        return "⬋"; // Sud-Ouest
    } else if (d >= 247 && d < 292) {
        return "←"; // Ouest
    } else if (d >= 292 && d < 337) {
        return "⬉"; // Nord-Ouest
    }

    return "?";
}


void MainWindow::change_labelsAPI(int value) {
    switch (value) {
    case 0:
        ui->message_API->setText("DÉCOLLAGE AUTORISÉ (conditions météorologiques favorables)");
        ui->message_API->setStyleSheet("color: green; font-size: 14pt; font-weight: bold;");
        break;
    case 1:

        ui->message_API->setText("DÉCOLLAGE DANGEREUX (conditions météorologiques défavorables)");
        ui->message_API->setStyleSheet("color: orange; font-size: 14pt; font-weight: bold;");
        break;
    case 2:
        ui->message_API->setText("INTERDICTION DE DÉCOLLAGE (conditions météorologiques défavorables)");
        ui->message_API->setStyleSheet("color: red; font-size: 14pt; font-weight: bold;");

        break;
    default:
        break;
    }}

void MainWindow::change_labels(int value) {
    switch (value) {
    case 0:
        ui->message->setText("DÉCOLLAGE AUTORISÉ (conditions météorologiques favorables)");
        ui->message->setStyleSheet("color: green; font-size: 14pt; font-weight: bold;");
        break;
    case 1:

        ui->message->setText("DÉCOLLAGE DANGEREUX (conditions météorologiques défavorables)");
        ui->message->setStyleSheet("color: orange; font-size: 14pt; font-weight: bold;");
        break;
    case 2:
        ui->message->setText("INTERDICTION DE DÉCOLLAGE (conditions météorologiques défavorables)");
        ui->message->setStyleSheet("color: red; font-size: 14pt; font-weight: bold;");

        break;
    default:
        break;
    }
    /*
    if (value) {
        ui->message->setText("INTERDICTION DE DÉCOLLAGE (conditions météorologiques défavorables)");
        ui->message->setStyleSheet("color: red; font-size: 14pt; font-weight: bold;");
    } else {
        ui->message->setText("DÉCOLLAGE AUTORISÉ (conditions météorologiques favorables)");
        ui->message->setStyleSheet("color: green; font-size: 14pt; font-weight: bold;");
    }

*/
}
