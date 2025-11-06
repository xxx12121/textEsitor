#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QPlainTextEdit>

namespace Ui {
class FindDialog;
}

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDialog(QWidget *parent = nullptr);
    ~FindDialog();

    void find(QPlainTextEdit* editor);

private slots:
    void on_btnNext_clicked();

    void on_btnCancel_clicked();

private:
    Ui::FindDialog *ui;

    QPlainTextEdit *editor;
};

#endif // FINDDIALOG_H
