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

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();
    ~MainWindow();
    void updateTable();

private slots:
    void addTask();
    void changeDB();
    void exitProgram();
    void cellSelected(int nRow, int nCol);

private:
    Ui::MainWindow *ui;
    void createActions();
    void createMenus();
    void createFilters(QHBoxLayout *layout);
    void initializeTable(QTableWidget *table);
    QRadioButton *rb_all;
    QRadioButton *rb_overdue;
    QRadioButton *rb_today;
    QRadioButton *rb_thisweek;
    QCheckBox *cb_completed;
    QTableWidget *table;
    QStringList tableHeader;
    QMenu *fileMenu;
    QAction *addTaskAct;
    QAction *changeDBAct;
    QAction *exitProgramAct;
    string path = "/home/carlos/Escritorio/database.txt";
};

#endif // MAINWINDOW_H