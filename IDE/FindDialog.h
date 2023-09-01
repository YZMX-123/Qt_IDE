#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QWidget>
#include <mainwindow.h>
#include <QPlainTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class FindDialog; }
QT_END_NAMESPACE

class FindDialog : public QWidget
{
    Q_OBJECT

public:
    explicit FindDialog(MainWindow *mainWindow, QWidget *parent = nullptr);
    ~FindDialog();

protected:
    void cleanHighlight();
    void closeEvent(QCloseEvent *event);

private slots:
    void on_pushButton_find_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::FindDialog *ui;
    QPlainTextEdit *textEditPointer;

    bool firstFind; // 标记是否是第一次查找
};

#endif // FINDDIALOG_H
