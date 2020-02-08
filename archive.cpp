#include "archive.h"
#include "ui_archive.h"
#include "login.h"
#include "QMessageBox"
#include "principal.h"

Archive::Archive(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Archive)
{
    ui->setupUi(this);
    ui->pushButton_2->hide();
    login conn;
    QSqlQueryModel * m= new QSqlQueryModel();

    QSqlQuery* query= new QSqlQuery(conn.mydb);
    query->prepare("Select id as 'numéro de série',nom ,prenom,date_naissance as 'Date de naissance',tel as 'Numéro de téléphone', id as 'Pour reactiver' from patients where etat=1");

    query->exec();
    m->setQuery(*query);
    ui->tableView->setModel(m);
    conn.mydb.close();
}

Archive::~Archive()
{
    delete ui;
}

void Archive::on_pushButton_clicked()
{
    this->hide();
    principal t;
    t.setWindowTitle("Tableau de bord");
    t.exec();
}

void Archive::on_tableView_activated(const QModelIndex &index)
{
    id_index=ui->tableView->model()->data(index).toString();
    login conn;
    QSqlQuery* query= new QSqlQuery(conn.mydb);
    query->prepare("Select * from patients where id='"+id_index+"'");
    query->exec();
    if (query->next()) {

       ui->pushButton_2->show();

    }
    else ui->pushButton_2->hide();
    //qDebug()<<id_index;
}

void Archive::on_pushButton_2_clicked()
{
    login conn;
    QSqlQuery* query= new QSqlQuery(conn.mydb);

    query->prepare("update patients set etat=0 where id='"+id_index+"' ");
    if(query->exec()) {
          QMessageBox::information(this, "Succès", "Le patient a été réactivé");

          QSqlQueryModel * m= new QSqlQueryModel();

          query->prepare("Select id as 'numéro de série',nom ,prenom,date_naissance as 'Date de naissance',tel as 'Numéro de téléphone', id as 'Pour reactiver' from patients where etat=1");

          query->exec();
          m->setQuery(*query);
          ui->tableView->setModel(m);
          ui->pushButton_2->hide();
    }
}
