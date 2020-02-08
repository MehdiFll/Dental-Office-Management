#include "addrdv.h"
#include "ui_addrdv.h"
#include "login.h"

addrdv::addrdv(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addrdv)
{
    ui->setupUi(this);
    ui->label_5->hide();
    login conn;
    QSqlQueryModel * m= new QSqlQueryModel();

    QSqlQuery* query= new QSqlQuery(conn.mydb);
    query->prepare("Select id from patients where etat=0 ");
    query->exec();
    m->setQuery(*query);
    ui->comboBox->setModel(m);
    conn.mydb.close();
    QDate c= QDate::currentDate();
    ui->dateEdit->setDate(c);
}

addrdv::~addrdv()
{
    delete ui;
}

void addrdv::on_pushButton_clicked()
{
    login conn;
    QSqlQuery* query= new QSqlQuery(conn.mydb);
    QString daterdv,heurerdv,idp,detailrdv;
    daterdv=ui->dateEdit->text();
    heurerdv=ui->timeEdit->text();
    idp=ui->comboBox->currentText();
    detailrdv=ui->plainTextEdit->toPlainText();

    if(query->exec("select * from rdv where id_pat='"+idp+"' and date='"+daterdv+"'")){
        int count=0;
        while (query->next()) {
            count++;
        }
        if(count==1) {ui->label_5->setText("existe déjà"); ui->label_5->show();}
                   else
                   {QSqlQuery* query1= new QSqlQuery(conn.mydb);

                   query1->prepare("insert into rdv (date,heure,id_pat,details_rdv) values ('"+daterdv+"','"+heurerdv+"','"+idp+"','"+detailrdv+"')");

                   if(query1->exec())  {
                       ui->label_5->setText("rendez-vous ajouté correctement...");
                       ui->label_5->show();

                   }
                   else {
                       ui->label_5->setText("erreur");
                       ui->label_5->show();

                   }}


 }



}

void addrdv::on_pushButton_3_clicked()
{
    this->hide();
    principal t;
    t.setWindowTitle("Tableau de bord");
    t.exec();
}
