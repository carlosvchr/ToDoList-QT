#ifndef CREATEDATAFILEDIALOG_H
#define CREATEDATAFILEDIALOG_H

#include <QDialog>
#include <string>
#include "iomanager.h"
#include "mainwindow.h"

using namespace std;

namespace Ui {
class CreateDatafileDialog;
}

class CreateDatafileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateDatafileDialog(QWidget *parent = 0);
    inline void setOrigin(MainWindow *origin){ this->origin = origin; }
    ~CreateDatafileDialog();

private slots:
    void on_name_ed_textChanged(const QString &arg1);
    void on_pushButton_3_clicked();
    void on_folder_ed_textChanged(const QString &arg1);
    void on_createbtn_clicked();
    void on_examinebtn_clicked();

private:
    Ui::CreateDatafileDialog *ui;
    void checkFields();
    void updateOutputLabel();
    MainWindow *origin;
};

#endif // CREATEDATAFILEDIALOG_H
