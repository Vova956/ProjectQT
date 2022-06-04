#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Contecting to driver of database
    db = QSqlDatabase :: addDatabase("QSQLITE");
    //Creating DB
    db.setDatabaseName("./DB.db");

    //Checking if it is opened or closed
    db.open()?qDebug("open"):qDebug("close");


    //Creating table
    query = new QSqlQuery(db);
    query->exec("CREATE TABLE Studentbook(Firstname TEXT, LastName TEXT, Telephone INT)");

    //Adding model
    model = new QSqlTableModel(this,db);
    model->setTable("Studentbook");
    model->select();

    //Connecting ui and DB
    ui->tableView->setModel(model);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    //Ading row to table
    model->insertRow(model->rowCount());
}


void MainWindow::on_pushButton_2_clicked()
{
    //Removing row
    model->removeRow(row);
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    //Remembering last row that was cklicked
    row = index.row();
}


void MainWindow::on_pushButton_3_clicked()
{
    //sorting model
    model->sort(1,Qt::AscendingOrder);
}

