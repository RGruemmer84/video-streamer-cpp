#include "GUI/lynes_manager_main.h"
#include <QApplication>
#include <QStyle>
#include <QDesktopWidget>

AppController *ctrl;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LynesManagerMain w;
    w.setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            w.size(),
            qApp->desktop()->availableGeometry()
        )
    );
    w.show();

    return a.exec();
}
