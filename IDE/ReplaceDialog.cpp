#include "ReplaceDialog.h"
#include "ui_ReplaceDialog.h"
#include <QDebug>
#include <QMessageBox>

ReplaceDialog::ReplaceDialog(MainWindow *mainWindow, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ReplaceDialog)
{
    ui->setupUi(this);
    textEditPointer = mainWindow->getTextEdit();
}

ReplaceDialog::~ReplaceDialog()
{
    delete ui;
}

void ReplaceDialog::cleanHighlight(){
    QTextCharFormat color;
    color.setForeground(Qt::black);  //设置字体颜色
    color.setBackground(Qt::white);  //设置背景颜色
    QTextCursor cursor = textEditPointer->textCursor();
    cursor.select(QTextCursor::Document);  // 选择整个文档
    cursor.mergeCharFormat(color);
}

void ReplaceDialog::on_pushButton_replace_clicked()
{
    QString findStr = ui->lineEdit_find->text();
    QString targetStr = ui->lineEdit_target->text();
    QTextDocument *document = textEditPointer->document();
    qDebug()<<textEditPointer->toPlainText();

    bool found = false; // 标记是否找到

    QTextCursor cursor(document);
    qDebug()<<cursor.position();
    cursor.beginEditBlock();
    qDebug()<<cursor.position();
    QTextCharFormat highlightColor(cursor.charFormat());
    highlightColor.setForeground(Qt::black);   //设置字体颜色
    highlightColor.setBackground(Qt::yellow);  //设置背景颜色

    QTextDocument::FindFlags options = QTextDocument::FindFlags();
    if(ui->checkBox_caseSensitive->isChecked()) // 被选中 区分大小写
    {
        options |= QTextDocument::FindCaseSensitively;
    }
    if(ui->checkBox_wholeWords->isChecked())    // 被选中 仅匹配完整的单词
    {
        options |= QTextDocument::FindWholeWords;
    }
    qDebug()<<options;

    int textLength = targetStr.length(); // 插入文本的长度
    while(!cursor.isNull() && !cursor.atEnd()&&findStr!="")
    {
        // 查找指定的文本
        cursor = document->find(findStr, cursor, options);
        qDebug()<<"while内: "<<cursor.position();
        if(!cursor.isNull())
        {
            if(!found) found = true;
            int startPosition = cursor.position();

            cursor.removeSelectedText();    // 删除，再插入targetStr
            cursor.insertText(targetStr);

            cursor.setPosition(startPosition);
            cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, textLength);
            cursor.mergeCharFormat(highlightColor); // 高亮替换后的文本

            cursor.setPosition(startPosition);
        }
    }
    cursor.endEditBlock();
    // 没找到
    if(!found){
        QMessageBox::warning(this, tr("查找"),tr("找不到%1").arg(findStr));
    }
}

void ReplaceDialog::closeEvent(QCloseEvent *event)
{
    cleanHighlight();
    this->close();
}

void ReplaceDialog::on_pushButton_cancel_clicked()
{
    this->close();
}
