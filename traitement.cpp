#include "traitement.h"
#include "ui_traitement.h"
#include "login.h"
#include "QMessageBox"
#include "principal.h"

traitement::traitement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::traitement)
{
    ui->setupUi(this);
    login conn;
    QSqlQueryModel * m= new QSqlQueryModel();
    ui->groupBox->hide();

    QSqlQuery* query= new QSqlQuery(conn.mydb);
    query->prepare("Select nom,prenom, type_traitement as 'Type de traitement' ,montant_total as 'Montant total', montant_verse as 'Montant versé', t.id as 'Pour verser' from patients p, traitements t where p.id=id_patient");
    query->exec();
    m->setQuery(*query);
    ui->tableView->setModel(m);
    conn.mydb.close();
}

traitement::~traitement()
{
    delete ui;
}

void traitement::on_tableView_activated(const QModelIndex &index)
{
    int count=0;
    id_index=ui->tableView->model()->data(index).toString();
    login conn;
    QSqlQuery* query= new QSqlQuery(conn.mydb);
    query->prepare("Select id from traitements where id='"+id_index+"'");
    query->exec();
    while (query->next()) {
         count++;
        }
    if (count==1) {
        ui->groupBox->show();
    }
    else ui->groupBox->hide();
}

void traitement::on_pushButton_clicked()
{
    int somme;
    int total;

    login conn;
    QSqlQuery* query= new QSqlQuery(conn.mydb);
    query->prepare("Select montant_verse from traitements where id='"+id_index+"'");
    query->exec();
    while (query->next()) {
    somme=ui->lineEdit->text().toInt()+query->value(0).toInt();
    }

    query->prepare("Select montant_total from traitements where id='"+id_index+"'");
    query->exec();
    while (query->next()) {
    total=query->value(0).toInt();
    }

    if (total<somme) {
        QMessageBox::information(this, "Erreur", "Le montant versé est supérieur au montant total ");
    }
    else {
    query->prepare("update traitements set montant_verse='"+ QString::number(somme) +"' where id='"+id_index+"'");
    if(query->exec()) {
        QMessageBox::information(this, "Succès", "Le nouveau montant versé est : " + QString::number(ui->lineEdit->text().toInt()));
        QSqlQueryModel * m= new QSqlQueryModel();

        query->prepare("Select nom,prenom, type_traitement as 'Type de traitement' ,montant_total as 'Montant total', montant_verse as 'Montant versé', t.id as 'Pour verser' from patients p, traitements t where p.id=id_patient");
        query->exec();
        m->setQuery(*query);
        ui->tableView->setModel(m);
        ui->groupBox->hide();
    }

 }

}

void traitement::on_pushButton_2_clicked()
{
    this->hide();
    principal t;
    t.setWindowTitle("Tableau de bord");
    t.exec();
}
