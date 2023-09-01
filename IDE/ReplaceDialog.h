#ifndef REPLACEDIALOG_H
#define REPLACEDIALOG_H

#include <QWidget>
#include <mainwindow.h>
#include <QPlainTextEdit>

QT_BEGIN_NAMESPACE
namespace Ui {
    class ReplaceDialog;
}
QT_END_NAMESPACE

class ReplaceDialog : public QWidget {
    Q_OBJECT

public:
    explicit ReplaceDialog(MainWindow *mainWindow, QWidget *parent = nullptr);
    ~ReplaceDialog();

protected:
    void cleanHighlight();
    void closeEvent(QCloseEvent *event);

private slots:
    void on_pushButton_cancel_clicked();

    void on_pushButton_replace_clicked();

private:
    Ui::ReplaceDialog *ui;
    QPlainTextEdit *textEditPointer;

};

#endif // REPLACEDIALOG_H
