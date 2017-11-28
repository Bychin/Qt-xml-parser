#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "parser.h"

#include <QMenu>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QMenu* mainMenu = new QMenu("Menu");
    mainMenu->addAction("&Open File", this, SLOT(OpenFile()), Qt::CTRL + Qt::Key_O);
    mainMenu->addAction("&Close All", this, SLOT(ClearTree()), Qt::CTRL + Qt::Key_C);
    mainMenu->addSeparator();
    mainMenu->addAction("&Exit", this, SLOT(CloseWindow()), Qt::CTRL + Qt::Key_Q);

    AddressBookParser handler_ege(ui->my_tree, "EGE results");
    AddressBookParser handler_gia(ui->my_tree, "GIA results");
    QFile file_gia("/home/bychin/Рабочий стол/gia_results.xml");
    QFile file_ege("/home/bychin/Рабочий стол/ege_results.xml");
    QXmlInputSource source1(&file_gia);
    QXmlInputSource source2(&file_ege);
    QXmlSimpleReader reader;

    reader.setContentHandler(&handler_gia);
    reader.parse(source1);

    reader.setContentHandler(&handler_ege);
    reader.parse(source2);

    ui->menuBar->addMenu(mainMenu);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::CloseWindow() {
    CloseWindow();
}

void MainWindow::ClearTree() {
    ui->my_tree->clear();
}

void MainWindow::OpenFile() {
    QString str = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.xml");
    qDebug() << str;
    // open - parse - update tree
}
