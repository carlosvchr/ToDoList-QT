#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iomanager.h"
#include <QHeaderView>

MainWindow::MainWindow()
{
    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    QWidget *topFiller = new QWidget;
    topFiller -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //topFiller->resize(topFiller->width(), 1);

    // MenuBar
    createActions();
    createMenus();

    // Filters
    QHBoxLayout *filtersLayout = new QHBoxLayout;
    createFilters(filtersLayout);
    //filtersLayout->setContentsMargins();

    //Table
    table = new QTableWidget(this);
    initializeTable(table);

    QVBoxLayout *layout = new QVBoxLayout;
    layout -> setMargin(8);
    layout -> addWidget(topFiller);
    layout -> addLayout(filtersLayout);
    layout -> addWidget(table);
    layout -> setStretch(0, 0);
    layout -> setStretch(1, 0);
    layout -> setStretch(2, 1);

    widget -> setLayout(layout);

    setWindowTitle("ToDo List QT");
    setMinimumSize(480, 320);
    resize(580, 480);
}

void MainWindow::createActions()
{
    addTaskAct = new QAction(tr("&Add Task"), this);
    addTaskAct -> setShortcuts(QKeySequence::New);
    addTaskAct -> setStatusTip(tr("Add new task to the list."));
    connect(addTaskAct, &QAction::triggered, this, &MainWindow::addTask);

    changeDBAct = new QAction(tr("&Change Database"), this);
    changeDBAct -> setStatusTip(tr("Change the database."));
    connect(changeDBAct, &QAction::triggered, this, &MainWindow::changeDB);

    exitProgramAct = new QAction(tr("&Exit"), this);
    connect(exitProgramAct, &QAction::triggered, this, &MainWindow::exitProgram);
}

void MainWindow::createFilters(QHBoxLayout *layout)
{
    rb_all = new QRadioButton;
    rb_overdue = new QRadioButton;
    rb_today = new QRadioButton;
    rb_thisweek = new QRadioButton;
    cb_completed = new QCheckBox;

    rb_all->setText(tr("&All"));
    rb_overdue->setText(tr("&Overdue"));
    rb_today->setText(tr("&Today"));
    rb_thisweek->setText(tr("&This Week"));
    cb_completed->setText(tr("&Completed"));

    QHBoxLayout *cbLayout = new QHBoxLayout;
    cbLayout -> setAlignment(Qt::AlignRight);
    cbLayout -> addWidget(cb_completed);

    layout->addWidget(rb_all);
    layout->addWidget(rb_overdue);
    layout->addWidget(rb_today);
    layout->addWidget(rb_thisweek);
    layout->addLayout(cbLayout);

    layout -> setStretch(0, 0);
    layout -> setStretch(1, 0);
    layout -> setStretch(2, 0);
    layout -> setStretch(3, 0);
    layout -> setStretch(4, 1);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(addTaskAct);
    fileMenu->addAction(changeDBAct);
    fileMenu->addAction(exitProgramAct);
}

void MainWindow::initializeTable(QTableWidget *table)
{
    table -> setRowCount(10);
    table -> setColumnCount(5);
    tableHeader << "Finished" << "DueDate" << "Title" << "% Complete" << "Description";
    table -> setHorizontalHeaderLabels(tableHeader);
    table -> horizontalHeader()->setStretchLastSection(true);
    table -> verticalHeader() -> setVisible(false);
    table -> setEditTriggers(QAbstractItemView::NoEditTriggers);
    table -> setSelectionBehavior(QAbstractItemView::SelectRows);
    table -> setSelectionMode(QAbstractItemView::SingleSelection);
    table -> setStyleSheet("QTableView {selection-background-color: #E0F7FA; selection-color: #000000;}");

    //inserting data
    updateTable();

    connect( table, SIGNAL( cellDoubleClicked (int, int) ),
     this, SLOT( cellSelected( int, int ) ) );
}

void MainWindow::addTask()
{

}

void MainWindow::changeDB()
{

}

void MainWindow::exitProgram()
{
    exit(0);
}

void MainWindow::cellSelected(int nRow, int nCol)
{

}

void MainWindow::updateTable(){
    vector<string*> data = IOManager::readFile(path);
    unsigned int i;
    for(i=0; i<data.size(); i++){
        QCheckBox *qcb = new QCheckBox;
        qcb->setStyleSheet(QStringLiteral("QCheckBox::indicator {subcontrol-position: center;}"));
        // Set the checkbox as not editable and check it if necessary
        qcb->setAttribute(Qt::WA_TransparentForMouseEvents, true);
        qcb->setFocusPolicy(Qt::NoFocus);
        qcb -> setChecked(stoi(data.at(i)[2]) == 100);

        table -> setAlternatingRowColors(true);
        table -> setCellWidget(i, 0, qcb);
        QTableWidgetItem *qdd = new QTableWidgetItem(QString::fromStdString(data.at(i)[0]));
        qdd -> setTextAlignment(Qt::AlignCenter);
        table -> setItem(i, 1, qdd);
        table -> setItem(i, 2, new QTableWidgetItem(QString::fromStdString(data.at(i)[1])));
        QTableWidgetItem *qtwi = new QTableWidgetItem(QString::fromStdString(data.at(i)[2]));
        qtwi -> setTextAlignment(Qt::AlignCenter);
        table -> setItem(i, 3, qtwi);
        table -> setItem(i, 4, new QTableWidgetItem(QString::fromStdString(data.at(i)[3])));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete rb_all;
    delete rb_overdue;
    delete rb_today;
    delete rb_thisweek;
    delete cb_completed;
    delete table;
    delete addTaskAct;
    delete changeDBAct;
    delete exitProgramAct;
    delete fileMenu;
}
