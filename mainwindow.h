#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "aboutdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_About_triggered();

    void on_action_N_triggered();

    void on_action_O_triggered();

    void on_action_S_triggered();

    void on_action_A_triggered();

    void on_action_X_triggered();

    void on_action_U_triggered();

    void on_action_Z_triggered();

    void on_action_T_triggered();

    void on_action_C_triggered();

    void on_action_P_triggered();

private:
    Ui::MainWindow *ui;
    AboutDialog aboutDialog;

    QString filename;
    QString raw;

};
#endif // MAINWINDOW_H
