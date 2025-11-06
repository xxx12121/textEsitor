#ifndef REPLACEDIALOG_H
#define REPLACEDIALOG_H

#include <QDialog>
#include <QPlainTextEdit>

namespace Ui {
class ReplaceDialog;
}

class ReplaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReplaceDialog(QWidget *parent = nullptr);
    ~ReplaceDialog();

    void replace(QPlainTextEdit *editor);

private slots:
    void on_btnNext_clicked();

    void on_btnReplace_clicked();

    void on_btnAll_clicked();

    void on_btnCancel_clicked();

private:
    Ui::ReplaceDialog *ui;

    QPlainTextEdit *editor;
};

#endif // REPLACEDIALOG_H
