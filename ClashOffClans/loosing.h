#ifndef LOOSING_H
#define LOOSING_H

#include <QDialog>
#include "level1.h"
#include <QMediaPlayer>
#include<QAudioOutput>

namespace Ui {
class Loosing;
}

class Loosing : public QDialog
{
    Q_OBJECT
     level1* level;
public:
    explicit Loosing( int damage, int creation, int ratio, float Speed, float Health, float duDamagee, int Dead, int troopRatio,QWidget *parent = nullptr);
    ~Loosing();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Loosing *ui;
    int TroobDamageRate;
    int TroobGeneratingRate;
    int ratio;
    float troopSpeed;
    float troopHealth;
    float duDamage;
    int troopDead;
    int troopRatio;

    QMediaPlayer* looser;
    QAudioOutput* audioOutputLooser;
};

#endif // LOOSING_H
