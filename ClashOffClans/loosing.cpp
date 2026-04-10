#include "loosing.h"
#include "ui_loosing.h"
#include "level1.h"
#include <QCoreApplication>

Loosing::Loosing(int damage,int creation, int ratio, float Speed, float health, float duDamagee, int Dead, int troopRatio,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Loosing)
{
    this->troopRatio = troopRatio;
    ui->setupUi(this);
    troopDead = Dead;
    this->duDamage = duDamagee;
    this->troopHealth = health;
    TroobDamageRate = damage;
    TroobGeneratingRate = creation;
    this->troopSpeed = Speed;
    this->ratio = ratio;

    QPixmap p1(":/new/img/TrobsW-standing.png");
    int w1 = ui->troob->width();
    int h1 = ui->troob->height();
    ui->troob->setPixmap(p1.scaled(w1,h1,Qt::KeepAspectRatio));

    looser = new QMediaPlayer(this);
    audioOutputLooser = new QAudioOutput(this);

    looser->setAudioOutput(audioOutputLooser);
    looser->setSource(QUrl("qrc:/new/audio/Loser.mp3"));
    audioOutputLooser->setVolume(50);

    looser->play();
}

Loosing::~Loosing()
{
    delete ui;
}

void Loosing::on_pushButton_clicked()
{
    level = new level1(TroobDamageRate, TroobGeneratingRate,ratio, troopSpeed, troopHealth, duDamage, troopDead, troopRatio);

    hide();
    if(level != nullptr) {  // Check if level is not nullptr before showing it
        level->show();
    }
}


void Loosing::on_pushButton_2_clicked()
{
    QCoreApplication::quit();
}


