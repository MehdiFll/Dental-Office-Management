#include "addp.h"
#include "ui_addp.h"
#include "login.h"


addp::addp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addp)
{
    ui->setupUi(this);
    ui->label_4->hide();
    ui->progressBar->hide();
    ui->label_5->hide();
    ui->label_8->hide();
    ui->label_6->hide();
}

addp::~addp()
{
    delete ui;
}

void addp::on_pushButton_2_clicked()
{
    ui->lineEdit->setText("");
    ui->dateEdit->date().currentDate();
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->progressBar->hide();
    ui->label_5->hide();
    ui->label_8->hide();
    ui->label_6->hide();
}

void addp::on_pushButton_clicked()
{
   login conn;
   QSqlQuery* query= new QSqlQuery(conn.mydb);

   QString nom,prenom,datedenaissance, tel,id;
   nom=ui->lineEdit->text();
   prenom=ui->lineEdit_2->text();
   datedenaissance=ui->dateEdit->text();
   tel=ui->lineEdit_3->text();
   id=prenom[0]+""+nom[0]+""+datedenaissance[0]+""+datedenaissance[1]+""+datedenaissance[3]+""+datedenaissance[4]+""+datedenaissance[6]+""+datedenaissance[7];

   //debut

   query->exec("select count(*) from patients where id like '"+id+"%'");
   if(query->next()) {
       qDebug()<< query->value(0).toInt();
       qDebug()<< query->value(0).toString();
       if(query->value(0).toInt()>0) {
          qDebug() <<"yes22";
           id=prenom[0]+""+nom[0]+""+datedenaissance[0]+""+datedenaissance[1]+""+datedenaissance[3]+""+datedenaissance[4]+""+datedenaissance[6]+""+datedenaissance[7]+""+query->value(0).toString();
         }
       else id=prenom[0]+""+nom[0]+""+datedenaissance[0]+""+datedenaissance[1]+""+datedenaissance[3]+""+datedenaissance[4]+""+datedenaissance[6]+""+datedenaissance[7];
    }

   //fin





   if(nom=="") {ui->label_5->setText("valeur invalide");ui->label_5->show();ui->progressBar->setValue(25);
       ui->progressBar->show(); }

   else if(prenom=="") {ui->label_6->setText("valeur invalide");ui->label_6->show();ui->progressBar->setValue(50);
       ui->progressBar->show(); }
   else if (tel==""){
       ui->label_8->setText("valeur invalide");ui->label_8->show();ui->progressBar->setValue(75);
              ui->progressBar->show();ui->label_5->hide();
   }
   else {ui->label_5->hide();



   if(query->exec("select * from patients where nom='"+nom+"' and prenom='"+prenom+"'")){
       int count=0;
       while (query->next()) {
           count++;
       }
       if(count==1) {ui->label_4->setText("existe déjà"); ui->label_4->show();}
                  else
                  {QSqlQuery* query1= new QSqlQuery(conn.mydb);

                  query1->prepare("insert into patients (id,nom,date_naissance,tel,prenom) values ('"+id+"','"+nom+"','"+datedenaissance+"','"+tel+"','"+prenom+"')");

                  if(query1->exec())  {
                      ui->label_4->setText("patient ajouté correctement...");
                      ui->label_4->show();
                      ui->progressBar->setValue(100);
                      ui->progressBar->show();
                  }
                  else {
                      ui->label_4->setText("erreur");
                      ui->label_4->show();

                  }}


}}}

void addp::on_pushButton_3_clicked()
{
    this->hide();
}
