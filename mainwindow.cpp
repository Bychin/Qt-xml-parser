#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "parser.h"

#include <QMenu>
#include <QFileDialog>
#include <QtXmlPatterns>
#include <QErrorMessage>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    dock = new QDockWidget("Query answer", this, Qt::Popup);
    text = new QTextEdit;
    dock->resize(600, 400);
    dock->hide();

    QMenu* mainMenu = new QMenu("Menu");
    mainMenu->addAction("&Open File", this, SLOT(OpenFile()), Qt::CTRL + Qt::Key_O);
    mainMenu->addAction("&Close All", this, SLOT(ClearTree()), Qt::CTRL + Qt::Key_C);
    mainMenu->addSeparator();
    mainMenu->addAction("&Execute XQuery", this, SLOT(OpenQuery()), Qt::CTRL + Qt::Key_E);
    mainMenu->addSeparator();
    mainMenu->addAction("&Exit", this, SLOT(CloseWindow()), Qt::CTRL + Qt::Key_Q);
    ui->menuBar->addMenu(mainMenu);

    connect(ui->pushButtonExecute, SIGNAL(clicked()), this, SLOT(ExecuteQuery()));

    mainLayout = new QGridLayout;
    mainLayout->addWidget(ui->my_tree, 0, 0, 3, 2);
    mainLayout->addWidget(ui->textEdit, 4, 0, 2, 1);
    mainLayout->addWidget(ui->pushButtonExecute, 4, 1, 1, 1);
    mainWidget = new QWidget;
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::CloseWindow() {
    QApplication::quit();
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
    if (!reader.parse(source)) {
        (new QErrorMessage(this))->showMessage("Cannot parse file!");
    }
}

void MainWindow::OpenQuery() {
    QString filepath = QFileDialog::getOpenFileName(this, "Choose query-file", "/home", "*.xq");
    QFile file(filepath);
    if (file.open(QIODevice::ReadOnly)) {
        QString query = file.readAll();
        file.close();
        ui->textEdit->setText(query);
        ExecuteQuery();
    } else {
        (new QErrorMessage(this))->showMessage("Cannot open file with query!");
        return;
    }
}

void MainWindow::ExecuteQuery() {
    QString query = ui->textEdit->toPlainText();
    if (query == "")
        OpenQuery();
    else {
        QXmlQuery xml_query;
        xml_query.setQuery(query);
        if (!xml_query.isValid()) {
            (new QErrorMessage(this))->showMessage("The query is not valid!");
            return;
        }
        QString answer;
        if (!xml_query.evaluateTo(&answer)) {
            (new QErrorMessage(this))->showMessage("Cannot evaluate the query!");
            return;
        }
        text->setText(answer);
        dock->setWidget(text);
        dock->setFloating(true);
        dock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetClosable);
        dock->setAllowedAreas(Qt::NoDockWidgetArea);
        dock->show();
    }
}
