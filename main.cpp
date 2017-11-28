#include "mainwindow.h"
#include "parser.h"

#include <QApplication>
#include <QDebug>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include <QXmlDefaultHandler>
#include <QXmlAttributes>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
