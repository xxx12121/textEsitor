#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QLabel>
#include "aboutdialog.h"
#include "finddialog.h"
#include "replacedialog.h"

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
    void closeEvent(QCloseEvent *event);

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

    void on_action_F_triggered();

    void on_action_R_triggered();


    void on_action_Tool_triggered();

    void on_action_Statu_triggered();

    void on_action_All_triggered();

    void on_action_Font_triggered();

    void on_action_Color_triggered();

    void on_action_FontBackgroundColor_triggered();

    void on_action_EditorBackgroundColor_triggered();

    void on_action_L_triggered();

    void on_action_W_triggered();

    void on_plainTextEdit_textChanged();

    void on_plainTextEdit_cursorPositionChanged();

    void on_plainTextEdit_selectionChanged();

private:
    Ui::MainWindow *ui;
    AboutDialog aboutDialog;
    FindDialog findDialog;
    ReplaceDialog replaceDialog;

    QString filename;
    QString raw;

    QLabel *info, *position, *user;

    void setEditable(bool f);

};
#endif // MAINWINDOW_H
