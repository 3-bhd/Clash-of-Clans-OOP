#ifndef START_H
#define START_H

#include <QMainWindow>
#include "level1.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Start; }
QT_END_NAMESPACE

class Start : public QMainWindow
{
    Q_OBJECT
    level1* level;

public:
    Start(QWidget *parent = nullptr);
    ~Start();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Start *ui;

    int TroobDamageRate;
    int TroobGeneratingRate;
    float troopSpeed;
    float troopHealth;
    float duDamage;
    int troopDead;
    int troopRatio;
};
#endif // START_H
