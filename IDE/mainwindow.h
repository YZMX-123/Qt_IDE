#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QPlainTextEdit* getTextEdit() const { return textEditPointer; }

private slots:
    void on_action_newFile_triggered();

    void on_action_openFile_triggered();

    void on_action_saveFile_triggered();

    void on_action_copy_triggered();

    void on_action_paste_triggered();

    void on_action_cut_triggered();

    void on_action_undo_triggered();

    void on_action_redo_triggered();

    void on_action_saveAs_triggered();

    void on_action_fullScreen_triggered();

    void on_action_settings_triggered();

    void on_action_find_triggered();

    void on_action_replace_triggered();

    void on_action_compile_triggered();

private:
    Ui::MainWindow *ui;
    QPlainTextEdit *textEditPointer;

};
#endif // MAINWINDOW_H
