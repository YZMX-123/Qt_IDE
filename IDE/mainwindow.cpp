#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <FindDialog.h>
#include <ReplaceDialog.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    textEditPointer = ui->plainTextEdit;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_newFile_triggered()
{

}

void MainWindow::on_action_openFile_triggered()
{

}

void MainWindow::on_action_saveFile_triggered()
{

}

void MainWindow::on_action_saveAs_triggered()
{

}

// 复制
void MainWindow::on_action_copy_triggered()
{
    ui->plainTextEdit->copy();
}
// 粘贴
void MainWindow::on_action_paste_triggered()
{
    ui->plainTextEdit->paste();
}
// 剪切
void MainWindow::on_action_cut_triggered()
{
    ui->plainTextEdit->cut();
}
// 撤销
void MainWindow::on_action_undo_triggered()
{
    ui->plainTextEdit->undo();
}
// 重做
void MainWindow::on_action_redo_triggered()
{
    ui->plainTextEdit->redo();
}
// 查找 打开查找窗口
void MainWindow::on_action_find_triggered()
{
    FindDialog *findDlg = new FindDialog(this);
    findDlg->show();
}
// 替换
void MainWindow::on_action_replace_triggered()
{
    ReplaceDialog *replaceDlg = new ReplaceDialog(this);
    replaceDlg->show();
}

void MainWindow::on_action_fullScreen_triggered()
{

}

void MainWindow::on_action_settings_triggered()
{

}

void MainWindow::on_action_compile_triggered()
{
    // 这样写好像有些奇怪，可能不能直接这样放在这里。
    // 而且编译结果需要输出到界面的textBrowser。这里之后大概需要更改。
    QString code = ui -> plainTextEdit -> toPlainText();
    FILE* file = fopen("temp.c", "w");
    fprintf(file,"%s",code.toUtf8().constData());
    fclose(file);
    system("gcc -o temp temp.c");
    system("temp.exe");
    //remove("temp.c");
}
