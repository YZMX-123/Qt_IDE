#include "FindDialog.h"
#include "ui_FindDialog.h"
#include <QDebug>
#include <QMessageBox>

FindDialog::FindDialog(MainWindow *mainWindow, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FindDialog)
{
    ui->setupUi(this);
    textEditPointer = mainWindow->getTextEdit();
    firstFind = true;
}

FindDialog::~FindDialog()
{
    delete ui;
}

void FindDialog::on_pushButton_find_clicked()
{
    if(firstFind) firstFind = false;
    else cleanHighlight();

    QString findStr = ui->lineEdit->text();
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
    qDebug()<<QTextDocument::FindBackward;
    while(!cursor.isNull() && !cursor.atEnd()&&findStr!="")
    // 当QTextCursor对象不为空且没有到达文档末尾，并且指定的文本不为空
    {
        // 查找指定的文本
        cursor = document->find(findStr, cursor, options);
        qDebug()<<"while内: "<<cursor.position();
        // find(const QString &subString, QTextCursor cursor, QTextDocument::FindFlags options = QTextDocument::FindFlags())
        // subString：要查找的子字符串。
        // cursor：指定查找的起始位置，一般为当前光标的位置。
        // options：查找选项，可以控制匹配的方式和范围，如大小写敏感、查找方向等。
        if(!cursor.isNull())
        {
            if(!found) found = true;
            cursor.mergeCharFormat(highlightColor);
            // mergeCharFormat函数将highlightColor中指定的字符格式应用到当前文本位置
        }
    }
    cursor.endEditBlock();
    // 没找到
    if(!found){
        QMessageBox::warning(this, tr("查找"),tr("找不到%1").arg(findStr));
    }
}

void FindDialog::cleanHighlight(){
    QTextCharFormat color;
    color.setForeground(Qt::black);  //设置字体颜色
    color.setBackground(Qt::white);  //设置背景颜色
    QTextCursor cursor = textEditPointer->textCursor();
    cursor.select(QTextCursor::Document);  // 选择整个文档
    cursor.mergeCharFormat(color);
}

void FindDialog::on_pushButton_cancel_clicked()
{
    cleanHighlight();
    this->close();
}

void FindDialog::closeEvent(QCloseEvent *event)
{
    cleanHighlight();
    this->close();
}
