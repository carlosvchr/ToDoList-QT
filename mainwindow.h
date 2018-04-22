#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QCheckBox>
#include <QTableWidget>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <QFileDialog>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();
    inline void setPath(string path){ this->path = path; }
    ~MainWindow();

private slots:
    void addTask();
    void changeDB();
    void exitProgram();
    void newDatafile();
    void cellSelected(int nRow, int nCol);

public slots:
    void filter();

private:
    Ui::MainWindow *ui;
    void createMenus();
    void createFilters(QHBoxLayout *layout);
    void initializeTable();
    int getWeekNumber(tm t);
    void updateTable(vector<string*> data);
    string path;
    QRadioButton *rb_all;
    QRadioButton *rb_overdue;
    QRadioButton *rb_today;
    QRadioButton *rb_thisweek;
    QCheckBox *cb_completed;
    QTableWidget *table;
    QStringList tableHeader;
    QMenu *fileMenu;
    QAction *newDatafileAct;
    QAction *addTaskAct;
    QAction *changeDBAct;
    QAction *exitProgramAct;
};

#endif // MAINWINDOW_H
