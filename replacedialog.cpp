#include "replacedialog.h"
#include "ui_replacedialog.h"

ReplaceDialog::ReplaceDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ReplaceDialog)
{
    ui->setupUi(this);
    ui->radioDown->setChecked(true);
    this->setWindowTitle("替换");
    this->setWindowIcon(QIcon::fromTheme("accessories-character-map"));
}

ReplaceDialog::~ReplaceDialog()
{
    delete ui;
}

void ReplaceDialog::replace(QPlainTextEdit *editor){
    this->editor = editor;
}
void ReplaceDialog::on_btnNext_clicked()
{
    QString text = editor->toPlainText();
    QString target = ui->target->displayText();
    if (!text.contains(target))
        return;
    QTextCursor cursor = editor->textCursor();
    Qt::CaseSensitivity cs = ui->checkBoxCaseSensitive->isChecked()?Qt::CaseSensitive:Qt::CaseInsensitive;
    int currentPos = cursor.position();
    int targetLen = target.length();
    int startPos = -1;

    if(ui->radioDown->isChecked()){
        startPos = text.indexOf(target, currentPos, cs);

        if (startPos == -1) {
            startPos = text.indexOf(target, 0, cs);
        }
    }else{
        if (currentPos >= targetLen) {
            startPos = text.lastIndexOf(target, currentPos - targetLen -1, cs);
        }

        if (startPos == -1) {
            startPos = text.lastIndexOf(target, cs);
        }
    }

    cursor.setPosition(startPos);
    cursor.setPosition(startPos + targetLen, QTextCursor::KeepAnchor);
    editor->setTextCursor(cursor);
    editor->ensureCursorVisible();
}


void ReplaceDialog::on_btnReplace_clicked()
{
    if(editor->textCursor().hasSelection()){
        editor->insertPlainText(ui->replaceTo->displayText());
    }
}


void ReplaceDialog::on_btnAll_clicked()
{
    Qt::CaseSensitivity cs = ui->checkBoxCaseSensitive->isChecked()?Qt::CaseSensitive:Qt::CaseInsensitive;
    QString text = editor->toPlainText();
    text.replace(ui->target->displayText(),ui->replaceTo->displayText(),cs);
    editor->setPlainText(text);
}


void ReplaceDialog::on_btnCancel_clicked()
{
    this->close();
}

