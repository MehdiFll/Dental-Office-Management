#include "liste_patient.h"
#include "ui_liste_patient.h"
#include "login.h"
#include "QMessageBox"
#include "principal.h"

Liste_patient::Liste_patient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Liste_patient)
{
    ui->setupUi(this);
    ui->groupBox->hide();
    login conn;
    QSqlQueryModel * m= new QSqlQueryModel();

    QSqlQuery* query= new QSqlQuery(conn.mydb);
    query->prepare("Select id as 'Numéro de série', nom as 'Nom', prenom as 'Prénom' , date_naissance as 'Date de naissance',tel as 'Numéro de téléphone', id as 'Pour modifier' from patients where etat=0");

    query->exec();
    m->setQuery(*query);
    ui->tableView->setModel(m);
  //  ui->listWidget->setModel(m);

    conn.mydb.close();
}

Liste_patient::~Liste_patient()
{
    delete ui;
}

void Liste_patient::on_tableView_activated(const QModelIndex &index)
{
    id_index=ui->tableView->model()->data(index).toString();
    login conn;
    QSqlQuery* query= new QSqlQuery(conn.mydb);
    query->prepare("Select * from patients where id='"+id_index+"'");
    query->exec();
    if (query->next()) {

        ui->groupBox->show();
        ui->lineEdit_n->setText(query->value(1).toString());
        ui->lineEdit_p->setText(query->value(4).toString());
        ui->lineEdit_3->setText(query->value(2).toString());
        ui->lineEdit_4->setText(query->value(3).toString());

    }
    else ui->groupBox->hide();

}

void Liste_patient::on_pushButton_clicked()
{
    QString nom,tel,date,prenom,id;
    nom=ui->lineEdit_n->text();
    prenom=ui->lineEdit_p->text();
    tel=ui->lineEdit_3->text();
    date=ui->lineEdit_4->text();
    id=prenom[0]+""+nom[0]+""+date[0]+""+date[1]+""+date[3]+""+date[4]+""+date[6]+""+date[7];

    login conn;
    QSqlQuery* query= new QSqlQuery(conn.mydb);

    query->prepare("update patients set nom='"+ nom +"', tel='"+ tel +"', date_naissance='"+ date +"', prenom='"+prenom+"', id='"+id+"' where id='"+id_index+"' ");
    if(query->exec()) {
          QMessageBox::information(this, "Succès", "Le patient a été mis à jour");

          QSqlQueryModel * m= new QSqlQueryModel();

          query->prepare("Select id as 'numéro de série',nom ,prenom,date_naissance as 'Date de naissance',tel as 'Numéro de téléphone', id as 'Pour modifier' from patients where etat=0");

          query->exec();
          m->setQuery(*query);
          ui->tableView->setModel(m);
          ui->groupBox->hide();

    }

}

void Liste_patient::on_pushButton_3_clicked()
{
    this->hide();
    principal t;
    t.setWindowTitle("Tableau de bord");
    t.exec();
}

void Liste_patient::on_Button_archivage_clicked()
{
    login conn;
    QSqlQuery* query= new QSqlQuery(conn.mydb);

    query->prepare("update patients set etat=1 where id='"+id_index+"' ");
    if(query->exec()) {
          QMessageBox::information(this, "Succès", "Le patient a été archivé");

          QSqlQueryModel * m= new QSqlQueryModel();

          query->prepare("Select id as 'numéro de série',nom ,prenom,date_naissance as 'Date de naissance',tel as 'Numéro de téléphone', id as 'Pour modifier' from patients where etat=0");

          query->exec();
          m->setQuery(*query);
          ui->tableView->setModel(m);
          ui->groupBox->hide();
    }
}
