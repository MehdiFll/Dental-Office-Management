#include "addt.h"
#include "ui_addt.h"
#include "login.h"

addt::addt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addt)
{
    ui->setupUi(this);
    ui->label_4->hide();
    login conn;
    QSqlQueryModel * m= new QSqlQueryModel();

    QSqlQuery* query= new QSqlQuery(conn.mydb);
    query->prepare("Select id from patients where etat=0 ");
    query->exec();
    m->setQuery(*query);
    ui->comboBox_n->setModel(m);
    conn.mydb.close();
    ui->label_testtotal->hide();
    ui->label_testverse->hide();
}

addt::~addt()
{
    delete ui;
}

void addt::on_pushButton_3_clicked()
{
    this->hide();
}

void addt::on_pushButton_2_clicked()
{
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
}

void addt::on_pushButton_clicked()
{
       login conn;


       QString nom,type,mtotal,mverse;
       QString id;
       nom=ui->comboBox_n->currentText();
       type=ui->comboBoxt->currentText();
       mtotal=ui->lineEdit->text();
       mverse=ui->lineEdit_2->text();

       if(mtotal=="") {ui->label_testtotal->setText("valeur invalid");ui->label_testtotal->show();ui->progressBar->setValue(50);
           ui->progressBar->show(); }

       else if (mverse==""){
           ui->label_testverse->setText("valeur invalid");ui->label_testverse->show();ui->progressBar->setValue(75);
                  ui->progressBar->show();ui->label_4->hide();
       }
       else {ui->label_4->hide();

       QSqlQuery* query= new QSqlQuery(conn.mydb);
       /* QSqlQuery* queryid= new QSqlQuery(conn.mydb);
        if(queryid->exec("select id from patients where nom='"+nom+"'and etat=0")) {
            while (queryid->next()) {
                id=queryid->value(0).toString(); }*/

       if(query->exec("select id_patient, type_traitement, montant_total from traitements where id='" +id+ "' and type_traitement='"+type+"'and montant_total='"+mtotal+"'")) {
           int count=0;
           while (query->next()) {
               count++;
           }
           if(count==1) {ui->label_4->setText("existe déjà"); ui->label_4->show();}
                 else {
               QSqlQuery* query1= new QSqlQuery(conn.mydb);
              query1->prepare("insert into traitements (id_patient,type_traitement,montant_total,montant_verse) values ('"+nom+"','"+type+"','"+mtotal+"','"+mverse+"')");

                      if(query1->exec())  {
                          ui->label_4->setText("traitement ajouté correctement...");
                          ui->label_4->show();
                          ui->progressBar->setValue(100);
                          ui->progressBar->show();
                             }
                      else {
                          ui->label_4->setText("erreur d'ajout");
                          ui->label_4->show();

                           }
                      }


    } }}
    //}


