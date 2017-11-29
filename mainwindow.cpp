#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "parser.h"

#include <QMenu>
#include <QFileDialog>
#include <QtXmlPatterns>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QMenu* mainMenu = new QMenu("Menu");
    mainMenu->addAction("&Open File", this, SLOT(OpenFile()), Qt::CTRL + Qt::Key_O);
    mainMenu->addAction("&Close All", this, SLOT(ClearTree()), Qt::CTRL + Qt::Key_C);
    mainMenu->addSeparator();
    mainMenu->addAction("&Exit", this, SLOT(CloseWindow()), Qt::CTRL + Qt::Key_Q);
    ui->menuBar->addMenu(mainMenu);

    connect(ui->pushButtonOpenFromFile, SIGNAL(clicked()), this, SLOT(OpenQuery()));
    connect(ui->pushButtonExecute, SIGNAL(clicked()), this, SLOT(ExecuteQuery()));

    mainLayout = new QGridLayout;
    mainLayout->addWidget(ui->treeView, 0, 0, 6, 4);
    mainLayout->addWidget(ui->lineEdit, 7, 0, 1, 3);
    mainLayout->addWidget(ui->pushButtonExecute, 7, 3, 1, 1);
    mainLayout->addWidget(ui->pushButtonOpenFromFile,  8, 0, 1, 4);
    mainWidget = new QWidget;
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);

    ui->treeView->setModel(ui->my_tree->model());
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
    QString filepath = QFileDialog::getOpenFileName(this, "Choose file", "/home", "*.xml");
    QString filename = filepath.section("/",-1,-1);
    QFile file(filepath);
    QXmlSimpleReader reader;
    AddressBookParser handler(ui->my_tree, filename);
    QXmlInputSource source(&file);
    reader.setContentHandler(&handler);
    reader.parse(source);
}

void MainWindow::OpenQuery() {
    QString filepath = QFileDialog::getOpenFileName(this, "Choose query-file", "/home", "*.xq");
    QString query = "";
    QFile file(filepath);
    if (file.open(QIODevice::ReadOnly)) {
        query = file.readAll();
        file.close();
        ui->lineEdit->setText(query);
        ExecuteQuery();
    } else {
        // throw exc window!
        // return
    }
}

void MainWindow::ExecuteQuery() {
    QString query = ui->lineEdit->text();
    if (query == "")
        return;

}
