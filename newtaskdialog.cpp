#include "newtaskdialog.h"
#include "ui_newtaskdialog.h"

NewTaskDialog::NewTaskDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTaskDialog)
{
    ui->setupUi(this);

    ui->datepicker->setDisplayFormat("yyyy/MM/dd");

    QDate date = QDate::currentDate();
    ui->datepicker->setDate(date);

    ui->slider->setRange(0, 100);
    ui->slider->setSingleStep(5);

    this->newTask = true;
}

void NewTaskDialog::setPath(string path)
{
    this->path = path;
}

void NewTaskDialog::setData(string duedate, string title, string percent, string description)
{
    this->oldDuedate = duedate;
    this->oldTitle = title;
    this->oldPercent = percent;
    this->oldDescription = description;
    string *sdate = IOManager::split(duedate, '/');
    QDate *sd = new QDate(stoi(sdate[0]), stoi(sdate[1]), stoi(sdate[2]));
    ui->datepicker->setDate(*sd);
    ui->title_et->setText(QString::fromStdString(title));
    ui->slider->setValue(stoi(percent));
    ui->description_ed->setPlainText(QString::fromStdString(description));
    this->newTask = false;
}


NewTaskDialog::~NewTaskDialog()
{
    delete ui;
}

void NewTaskDialog::on_buttonBox_accepted()
{
    vector<string*> lines = IOManager::readFile(path);
    unsigned int i;
    string sdatepicker(ui->datepicker->text().toUtf8().constData());
    string stitle(ui->title_et->text().toUtf8().constData());
    string spercent(ui->percent_lbl->text().toUtf8().constData());
    spercent = spercent.substr(0, spercent.find('%'));
    string sdescr(ui->description_ed->toPlainText().toUtf8().constData());
    string s = "";
    if(newTask){
        for(i=0; i<lines.size(); i++){
            s+=lines.at(i)[0]+";"+lines.at(i)[1]+";"+lines.at(i)[2]+";"+lines.at(i)[3]+"\n";
        }
        s += sdatepicker+";"+stitle+";"+spercent+";"+sdescr;
    }else{
        for(i=0; i<lines.size(); i++){
            if(lines.at(i)[0].compare(oldDuedate) == 0 && lines.at(i)[1].compare(oldTitle) == 0 &&
                    lines.at(i)[2].compare(oldPercent) == 0 && lines.at(i)[3].compare(oldDescription) == 0){
                s += sdatepicker+";"+stitle+";"+spercent+";"+sdescr+"\n";
            }else{
                s+=lines.at(i)[0]+";"+lines.at(i)[1]+";"+lines.at(i)[2]+";"+lines.at(i)[3]+"\n";
            }
        }
    }
    IOManager::writeFile(path, s);
    lines.clear();
    origin->filter();
}

void NewTaskDialog::on_buttonBox_rejected()
{
    this->close();
}


void NewTaskDialog::on_slider_valueChanged(int value)
{
    ui->percent_lbl->setText(QString::fromStdString(to_string(value)+"% Complete"));
}
