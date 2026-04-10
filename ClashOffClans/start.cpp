#include "start.h"
#include "ui_start.h"

Start::Start(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Start)
{
    ui->setupUi(this);
    TroobDamageRate = 100;
    TroobGeneratingRate = 5000;
    troopSpeed = 100;
    troopHealth = 100;
    duDamage = 150;
    troopDead = 0;
    troopRatio = 0;

    QPixmap p1(":/new/img/TrobsW-standing.png");
    int w1 = ui->troob->width();
    int h1 = ui->troob->height();
    ui->troob->setPixmap(p1.scaled(w1,h1,Qt::KeepAspectRatio));

    QPixmap p2(":/new/img/c5.png");
    int w2 = ui->cannon->width();
    int h2 = ui->cannon->height();
    ui->cannon->setPixmap(p2.scaled(w2,h2,Qt::KeepAspectRatio));
}

Start::~Start()
{
    delete ui;
    if(level){
        delete level;
    }
    level = nullptr;  // Set level to nullptr after deleting it
}

void Start::on_pushButton_clicked()
{
    level = new level1(TroobDamageRate, TroobGeneratingRate,1, troopSpeed, troopHealth, duDamage, troopDead, troopRatio);

    hide();
    if(level != nullptr) {  // Check if level is not nullptr before showing it
        level->show();
    }
}
