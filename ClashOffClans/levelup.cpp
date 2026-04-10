#include "levelup.h"
#include "ui_levelup.h"
#include <QCoreApplication>
#include "level1.h"

LevelUp::LevelUp(float duDamagee, int dead, int troopRatio, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LevelUp)
{
    ui->setupUi(this);
    troopDead = dead;
    TroobDamageRate = 100;
    TroobGeneratingRate = 5000;
    troopSpeed = 100;
    troopHealth = 100;
    duDamage = duDamagee;
    this->troopRatio = troopRatio;

    QPixmap p1(":/new/img/TrobsW-standing.png");
    int w1 = ui->troob->width();
    int h1 = ui->troob->height();
    ui->troob->setPixmap(p1.scaled(w1,h1,Qt::KeepAspectRatio));


    winner = new QMediaPlayer(this);
    audioOutputWinner = new QAudioOutput(this);

    winner->setAudioOutput(audioOutputWinner);
    winner->setSource(QUrl("qrc:/new/audio/Win.mp3"));
    audioOutputWinner->setVolume(50);

    winner->play();
}

int LevelUp::ratio = 1;

LevelUp::~LevelUp()
{
    delete ui;
}

void LevelUp::on_pushButton_clicked()
{
    ratio++;

    TroobDamageRate+=100*ratio;
    TroobGeneratingRate-=800*ratio;
    troopSpeed-=10*ratio;
    troopHealth+=50*ratio;

    level2 = new level1(TroobDamageRate,TroobGeneratingRate,ratio, troopSpeed, troopHealth, duDamage, troopDead, troopRatio);

    hide();
    if(level2 != nullptr) {  // Check if level is not nullptr before showing it
        level2->show();
    }
}


void LevelUp::on_pushButton_2_clicked()
{
    QCoreApplication::quit();
}


void LevelUp::on_pushButton_3_clicked()
{
    level2 = new level1(TroobDamageRate,TroobGeneratingRate,ratio, troopSpeed, troopHealth, duDamage, troopDead, troopRatio);
    hide();
    if(level2 != nullptr) {  // Check if level is not nullptr before showing it
        level2->show();
    }
}

