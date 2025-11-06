#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QInputDialog>
#include <QFileDialog>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , aboutDialog()
    , findDialog()
{
    filename = "";
    raw = "";

    ui->setupUi(this);
    ui->plainTextEdit->setEnabled(false);

    ui->action_S->setEnabled(false);
    ui->action_A->setEnabled(false);

    this->setWindowTitle("文本编辑器");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::closeEvent(QCloseEvent *event) {
    if(raw != ui->plainTextEdit->toPlainText()){
        QMessageBox::StandardButton reply = QMessageBox::question(this,tr("未保存"),tr("是否要保存当前内容？"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (reply == QMessageBox::Yes) {
            ui->action_S->trigger();
        } else if(reply == QMessageBox::Cancel){
            event->ignore();
        }
    }
}


void MainWindow::on_action_About_triggered()
{
    aboutDialog.show();
}


void MainWindow::on_action_N_triggered()
{
    if(raw != ui->plainTextEdit->toPlainText()){
        QMessageBox::StandardButton reply = QMessageBox::question(this,tr("未保存"),tr("是否要保存当前内容？"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (reply == QMessageBox::Yes) {
            ui->action_S->trigger();
        } else if(reply == QMessageBox::Cancel){
            return;
        }
    }
    raw = "";
    ui->plainTextEdit->setEnabled(true);
    ui->plainTextEdit->clear();
    ui->action_S->setEnabled(true);
    ui->action_A->setEnabled(true);
    this->setWindowTitle("未命名.txt");
    filename.clear();
}


void MainWindow::on_action_O_triggered()
{
    if(raw != ui->plainTextEdit->toPlainText()){
        QMessageBox::StandardButton reply = QMessageBox::question(this,tr("未保存"),tr("是否要保存当前内容？"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (reply == QMessageBox::Yes) {
            ui->action_S->trigger();
        } else if(reply == QMessageBox::Cancel){
            return;
        }
    }

    filename = QFileDialog::getOpenFileName(this,"打开文件","../../text/","文本文件(*.txt)");
    if(filename.isEmpty())
        return;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("错误"), tr("无法打开文件：%1").arg(file.errorString()));
        return;
    }

    this->setWindowTitle(QFileInfo(filename).fileName());
    ui->plainTextEdit->setEnabled(true);
    ui->action_S->setEnabled(true);
    ui->action_A->setEnabled(true);

    QTextStream in(&file);
    raw = in.readAll();
    ui->plainTextEdit->setPlainText(raw);
    file.close();
}


void MainWindow::on_action_S_triggered()
{
    if(filename.isEmpty()){
        ui->action_A->trigger();
        return;
    }
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(this, tr("错误"), tr("无法保存文件：%1").arg(file.errorString()));
        return;
    }
    QTextStream out(&file);
    raw = ui->plainTextEdit->toPlainText();
    out<<raw;
    QMessageBox::information(this,"提示","保存成功");
    file.close();
}


void MainWindow::on_action_A_triggered()
{
    QString dir = QFileDialog::getExistingDirectory(this,"选择文件路径","../../text/");
    if(dir.isEmpty())
        return;
    QString  newfilename = QInputDialog::getText(this, "文件保存", "请输入新文件名：");
    if(newfilename.isEmpty())
        return;
    filename =dir + "/" + newfilename + ".txt";
    this->setWindowTitle(QFileInfo(filename).fileName());
    ui->action_S->trigger();
}


void MainWindow::on_action_X_triggered()
{
    this->close();
}


void MainWindow::on_action_U_triggered()
{
    ui->plainTextEdit->undo();
}


void MainWindow::on_action_Z_triggered()
{
    ui->plainTextEdit->redo();
}


void MainWindow::on_action_T_triggered()
{
    ui->plainTextEdit->cut();
}


void MainWindow::on_action_C_triggered()
{
    ui->plainTextEdit->copy();
}


void MainWindow::on_action_P_triggered()
{
    ui->plainTextEdit->paste();
}


void MainWindow::on_action_F_triggered()
{
    findDialog.show();
    findDialog.find(ui->plainTextEdit);
}


void MainWindow::on_action_R_triggered()
{
    replaceDialog.show();
    replaceDialog.replace(ui->plainTextEdit);
}

