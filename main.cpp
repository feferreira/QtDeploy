#include "widget.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load("trad_pt"/*,QCoreApplication::applicationDirPath()*/);
    a.installTranslator(&translator);

    Widget w;
    w.showe();

    return a.exec();
}
