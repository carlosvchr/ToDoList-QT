#include "createdatafiledialog.h"
#include "ui_createdatafiledialog.h"

CreateDatafileDialog::CreateDatafileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateDatafileDialog)
{
    ui->setupUi(this);
    ui->folder_ed->setReadOnly(true);
    ui->createbtn->setEnabled(false);
}

CreateDatafileDialog::~CreateDatafileDialog()
{
    delete ui;
}


void CreateDatafileDialog::on_pushButton_3_clicked()
{
    this->close();
}


void CreateDatafileDialog::on_name_ed_textChanged(const QString &arg1)
{
    updateOutputLabel();
    checkFields();
}

void CreateDatafileDialog::on_folder_ed_textChanged(const QString &arg1)
{
    updateOutputLabel();
    checkFields();
}

void CreateDatafileDialog::updateOutputLabel(){
    string sfolder(ui->folder_ed->text().toUtf8().constData());
    string stitle(ui->name_ed->text().toUtf8().constData());
    QString outputstringlbl = QString::fromStdString(sfolder + QString(QDir::separator()).toUtf8().constData() + stitle + ".txt");
    ui->outputlbl->setText(outputstringlbl);
}


void CreateDatafileDialog::checkFields(){
    string sfolder(ui->folder_ed->text().toUtf8().constData());
    string stitle(ui->name_ed->text().toUtf8().constData());

    if(sfolder.length()>0 && stitle.length()>0){
        ui->createbtn->setEnabled(true);
    }else{
        ui->createbtn->setEnabled(false);
    }
}

void CreateDatafileDialog::on_createbtn_clicked()
{
    string sfolder(ui->folder_ed->text().toUtf8().constData());
    string stitle(ui->name_ed->text().toUtf8().constData());
    origin->setPath(sfolder + QString(QDir::separator()).toUtf8().constData() + stitle + ".txt");
    origin->filter();
    this->close();
}

void CreateDatafileDialog::on_examinebtn_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Select Directory"), NULL, QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->folder_ed->setText(dir);
}
