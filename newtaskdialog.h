#ifndef NEWTASKDIALOG_H
#define NEWTASKDIALOG_H

#include <QDialog>
#include <string>
#include <vector>
#include <QMessageBox>
#include "iomanager.h"
#include "mainwindow.h"

using namespace std;

namespace Ui {
class NewTaskDialog;
}

class NewTaskDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewTaskDialog(QWidget *parent = 0);
    void setData(string duedate, string title, string percent, string description);
    void setPath(string path);
    inline void setOrigin(MainWindow *origin){ this->origin = origin; }
    string oldDuedate;
    string oldTitle;
    string oldPercent;
    string oldDescription;
    ~NewTaskDialog();

private slots:
    void on_slider_valueChanged(int value);
    void on_description_ed_textChanged();
    void on_title_et_textChanged(const QString &arg1);
    void on_datepicker_userDateChanged(const QDate &date);
    void on_savebtn_clicked();
    void on_cancelbtn_clicked();

private:
    void checkFields();
    Ui::NewTaskDialog *ui;
    bool newTask;
    string path;
    MainWindow *origin;
};

#endif // NEWTASKDIALOG_H
