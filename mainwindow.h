#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGridLayout* mainLayout;
    QWidget* mainWidget;

private slots:
    void CloseWindow();
    void ClearTree();
    void OpenFile();
    void OpenQuery();
    void ExecuteQuery();
};

#endif // MAINWINDOW_H
