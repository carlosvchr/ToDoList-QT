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

    ui->savebtn->setEnabled(false);

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
    ui->savebtn->setText("Modify");
}


NewTaskDialog::~NewTaskDialog()
{
    delete ui;
}


void NewTaskDialog::on_slider_valueChanged(int value)
{
    ui->percent_lbl->setText(QString::fromStdString(to_string(value)+"% Compl."));
    checkFields();
}


void NewTaskDialog::checkFields(){
    string sdatepicker(ui->datepicker->text().toUtf8().constData());
    string stitle(ui->title_et->text().toUtf8().constData());
    string spercent(ui->percent_lbl->text().toUtf8().constData());
    spercent = spercent.substr(0, spercent.find('%'));
    string sdescr(ui->description_ed->toPlainText().toUtf8().constData());

    //We check all fields are completed
    if(sdatepicker.length()!=10 || stitle.length()==0 || spercent.length()==0 || sdescr.length()==0){
        ui->savebtn->setEnabled(false);
    }else{
        ui->savebtn->setEnabled(true);
    }
}
void NewTaskDialog::on_description_ed_textChanged()
{
    checkFields();
}

void NewTaskDialog::on_title_et_textChanged(const QString &arg1)
{
    checkFields();
}

void NewTaskDialog::on_datepicker_userDateChanged(const QDate &date)
{
    checkFields();
}

void NewTaskDialog::on_savebtn_clicked()
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
    this->close();
}

void NewTaskDialog::on_cancelbtn_clicked()
{
    this->close();
}
