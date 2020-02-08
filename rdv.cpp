#include "rdv.h"
#include "ui_rdv.h"
#include "login.h"
#include "principal.h"
#include <QDebug>
#include "QMessageBox"

rdv::rdv(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rdv)
{
    ui->setupUi(this);
    ui->groupBox->hide();
    ui->tableView->hide();
}

rdv::~rdv()
{
    delete ui;
}

void rdv::on_calendarWidget_activated(const QDate &date)
{

    ui->groupBox->hide();
    d=date.toString("dd/MM/yyyy");

    login conn;
    QSqlQueryModel * m= new QSqlQueryModel();

    QSqlQuery* query= new QSqlQuery(conn.mydb);
    query->prepare("Select heure as 'Heure', id_pat as 'ID Patient', details_rdv as 'Détails du RDV', id_rdv as 'Pour modifier' from rdv where date='"+d+"'");
    query->exec();
    m->setQuery(*query);
    ui->tableView->setModel(m);
    conn.mydb.close();

    ui->tableView->show();

}

void rdv::on_tableView_activated(const QModelIndex &index)
{
    id_index=ui->tableView->model()->data(index).toString();
    login conn;
    QSqlQuery* query= new QSqlQuery(conn.mydb);
    query->prepare("Select * from rdv where id_rdv='"+id_index+"'");
    query->exec();

    if (query->next()) {
        ui->groupBox->show();
        QDate date= QDate::fromString(query->value(1).toString(),"dd/MM/yyyy");
        ui->dateEdit->setDate(date);
        ui->timeEdit->setTime(query->value(2).toTime());
        ui->plainTextEdit->setPlainText(query->value(4).toString());
    }
    else ui->groupBox->hide();
    conn.mydb.close();
}

void rdv::on_pushButton_2_clicked()
{
    QString daterdv,heurerdv,detailrdv;
    daterdv=ui->dateEdit->text();
    heurerdv=ui->timeEdit->text();
    detailrdv=ui->plainTextEdit->toPlainText();
    login conn;
    QSqlQuery* query= new QSqlQuery(conn.mydb);

    query->prepare("update rdv set date='"+daterdv+"', heure='"+heurerdv+"', details_rdv='"+detailrdv+"' where id_rdv='"+id_index+"' ");
    if(query->exec()) {
          QMessageBox::information(this, "Succès", "Le rdv a été mis à jour");

          QSqlQueryModel * m= new QSqlQueryModel();

          query->prepare("Select heure as 'Heure', id_pat as 'ID Patient', details_rdv as 'Détails du RDV', id_rdv as 'Pour modifier' from rdv where date='"+d+"'");

          query->exec();
          m->setQuery(*query);
          ui->tableView->setModel(m);
          ui->groupBox->hide();
    }
    conn.mydb.close();
}

void rdv::on_pushButton_clicked()
{
    login conn;
    QSqlQuery* query= new QSqlQuery(conn.mydb);

    query->prepare("delete from rdv where id_rdv='"+id_index+"' ");
    if(query->exec()) {
          QMessageBox::information(this, "Succès", "Le rdv a été supprimé");

          QSqlQueryModel * m= new QSqlQueryModel();

          query->prepare("Select heure as 'Heure', id_pat as 'ID Patient', details_rdv as 'Détails du RDV', id_rdv as 'Pour modifier' from rdv where date='"+d+"'");

          query->exec();
          m->setQuery(*query);
          ui->tableView->setModel(m);
          ui->groupBox->hide();
    }
    conn.mydb.close();
}

void rdv::on_pushButton_3_clicked()
{
    this->hide();
    principal t;
    t.setWindowTitle("Tableau de bord");
    t.exec();
}
