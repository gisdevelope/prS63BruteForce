#include "prS63BruteForceClient.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    client::prS63BruteForceClient w;
    w.show();

    return a.exec();
}
