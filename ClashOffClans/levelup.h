#ifndef LEVELUP_H
#define LEVELUP_H

#include <QDialog>
#include "level1.h"
#include <QMediaPlayer>
#include<QAudioOutput>

namespace Ui {
class LevelUp;
}

class LevelUp : public QDialog
{
    Q_OBJECT
        level1* level2;

public:
    explicit LevelUp(float duDamagee, int dead, int troopRatio,QWidget *parent = nullptr);
    ~LevelUp();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::LevelUp *ui;
    int troopDead;
    int TroobDamageRate;
    int TroobGeneratingRate;
    float troopSpeed;
    float troopHealth;
    float duDamage;
    int troopRatio;

    QMediaPlayer* winner;
    QAudioOutput* audioOutputWinner;


    static int ratio;
};

#endif // LEVELUP_H
