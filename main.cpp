#include "cuegenerator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CUEGenerator w;
    w.show();

    return a.exec();
}
