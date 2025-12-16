#ifndef WJH_H
#define WJH_H
#include "api.h"
#include <QMainWindow>
#include "system_meteo.h"
#include "filtre_meteo.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onTempChanged(int value);
    void onventChanged(int value);
    void onatmoChanged(int value);
    void change_labels(int value);
    void change_labelsAPI(int value);
    void onAPIkeys(QString api);
    void onCITY (QString ville);
    void appelAPI();
    bool apierror(QString message);
    QString mettreAJourDirectionVent(double deg);
private:
    Ui::MainWindow *ui;
    API info;
    system_meteo a ;
    filtre_meteo fi;

};
#endif // WJH_H
