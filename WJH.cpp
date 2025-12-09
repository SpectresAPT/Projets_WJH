#include "WJH.h"
#include "ui_WJH.h"

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
    if (longueur_api == 32) {
        ui->label_api->setText("Votre cle API est valide");
        ui->label_api->setStyleSheet("color: green;");
        info.setAPIkey(api);

    }
    else {
        ui->label_api->setText("Votre cle API est invalide");
        ui->label_api->setStyleSheet("color: red;");
    }

}

void MainWindow::onCITY(QString ville) {
    qDebug() << "Nouvelle Ville : " << ville;
    info.setville(ville);

}

void MainWindow::appelAPI() {

    QString api_key;
    QString ville;

    qDebug() << "config appel API ";
    api_key=info.getAPIkey();
    qDebug() << "nouvelle API KEY";

    ville=info.getville();
    qDebug() << "nouvelle ville : " << ville;

    qDebug() << "lancement appel API ";
    info.setmeteo_data(info.apiRequest(api_key,ville));
    qDebug() << info.getmeteo_data();
    QString cleanDataM = fi.trieData(info.getmeteo_data());


}
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
