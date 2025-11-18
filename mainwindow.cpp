#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>
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

    setEditable(false);

    ui->action_Tool->setChecked(true);
    ui->action_Statu->setChecked(true);
    ui->action_W->setChecked(true);
    ui->action_L->setChecked(true);

    info = new QLabel(" length:0  lines:1 ");
    position = new QLabel(" Ln:1  Col:1 ");
    user = new QLabel(" 陈圳鑫 ");

    ui->statusbar->addPermanentWidget(info);
    ui->statusbar->addPermanentWidget(position);
    ui->statusbar->addPermanentWidget(user);
    ui->statusbar->show();

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

void MainWindow::setEditable(bool f){
    ui->plainTextEdit->setEnabled(f);
    ui->action_S->setEnabled(f);
    ui->action_A->setEnabled(f);
    ui->action_C->setEnabled(f);
    ui->action_T->setEnabled(f);
    ui->action_P->setEnabled(f);
    ui->action_U->setEnabled(f);
    ui->action_Z->setEnabled(f);
    ui->action_F->setEnabled(f);
    ui->action_R->setEnabled(f);
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
    setEnabled(true);
    ui->plainTextEdit->clear();
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

    setEditable(true);

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



void MainWindow::on_action_Tool_triggered()
{
    ui->toolBar->setHidden(!ui->action_Tool->isChecked());
}


void MainWindow::on_action_Statu_triggered()
{
    ui->statusbar->setHidden(!ui->action_Statu->isChecked());
}


void MainWindow::on_action_All_triggered()
{
    ui->plainTextEdit->selectAll();
}


void MainWindow::on_action_Font_triggered()
{
    bool ok;
    QFont font =QFontDialog::getFont(&ok,ui->plainTextEdit->font(),this,"选择字体");
    if(ok){
        ui->plainTextEdit->setFont(font);
    }
}


void MainWindow::on_action_Color_triggered()
{
    QColor color = QColorDialog::getColor();
    if(color.isValid()){
        ui->plainTextEdit->setStyleSheet(QString("QPlainTextEdit {color:%1;}").arg(color.name()));
    }
}


void MainWindow::on_action_FontBackgroundColor_triggered()
{
    QColor color = QColorDialog::getColor();
    QTextCursor cursor = ui->plainTextEdit->textCursor();
    QTextCursor origin = cursor;
    QTextCharFormat format;
    format.setBackground(color);
    cursor.movePosition(QTextCursor::Start);
    cursor.movePosition(QTextCursor::End, QTextCursor::KeepAnchor);
    cursor.setCharFormat(format);
    ui->plainTextEdit->setTextCursor(origin);
}


void MainWindow::on_action_EditorBackgroundColor_triggered()
{
    QColor color = QColorDialog::getColor();
    if(color.isValid()){
        ui->plainTextEdit->setStyleSheet(QString("QPlainTextEdit {background-color:%1;}").arg(color.name()));
    }
}


void MainWindow::on_action_L_triggered()
{
    ui->plainTextEdit->setLineNumberHidden(!ui->action_L->isChecked());
}


void MainWindow::on_action_W_triggered()
{
    ui->plainTextEdit->setLineWrapMode(ui->action_W->isChecked()?QPlainTextEdit::WidgetWidth:QPlainTextEdit::NoWrap);
}


void MainWindow::on_plainTextEdit_textChanged()
{
    int length = ui->plainTextEdit->toPlainText().length();
    int lines = ui->plainTextEdit->blockCount();
    info->setText(QString(" length:%1  lines:%2 ").arg(length).arg(lines));
}


void MainWindow::on_plainTextEdit_cursorPositionChanged()
{
    QTextCursor cursor = ui->plainTextEdit->textCursor();
    int Ln = cursor.blockNumber() + 1;
    int Col = cursor.columnNumber() + 1;
    position->setText(QString(" Ln:%1  Col:%2 ").arg(Ln).arg(Col));
}

