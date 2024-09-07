#include <QApplication>
#include "MainWindow.h"
#include <QTimer>

int main(int argc,char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    QTimer timer;
    QObject::connect(&timer,&QTimer::timeout,[&] {
        w.update_clock();
    });
    timer.start(100);

    return a.exec();
}
