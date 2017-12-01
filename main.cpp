#include "mainwindow.h"
#include "parser.h"

#include <QApplication>
#include <QDebug>
#include <QTreeWidget>
#include <QTreeWidgetItem>

#include <QXmlDefaultHandler>
#include <QXmlAttributes>


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    return app.exec();
}
