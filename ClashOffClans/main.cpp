#include "start.h"
#include <QCursor>
#include <QPixmap>
#include <QLabel>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pix(":/new/img/cursor.png");
    pix = pix.scaled(40,40);
    QCursor customCursor(pix);
    a.setOverrideCursor(customCursor);

    Start w;
    w.show();
    return a.exec();
}
