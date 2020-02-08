#include "tache.h"
#include "ui_tache.h"
#include <QDebug>
#include <login.h>

tache::tache(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tache)
{
    ui->setupUi(this);
    QStringList strList;
    login conn;
    QSqlQuery* query= new QSqlQuery(conn.mydb);
    query->prepare("Select * from taches");
    query->exec();

    while (query->next()) {
       strList << (query->value(1).toString());
    }


    ui->widget->addItems(strList);

    QListWidgetItem* item = 0;
    for(int i = 0; i < ui->widget->count(); ++i){
        item = ui->widget->item(i);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked); }
    conn.mydb.close();
}

tache::~tache()
{
    delete ui;
}



void tache::on_pushButton_ajouter_clicked()
{
    login conn;
    QSqlQuery* query= new QSqlQuery(conn.mydb);
    QString t;
    t=ui->lineEdit->text();
    query->prepare("insert into taches (text) values ('"+t+"')");
    query->exec();
    QStringList strList;
    if(t!="") {
        if(query->exec()) {

            strList << t;
                }
    }

    ui->widget->addItems(strList);

    QListWidgetItem* item = 0;
    for(int i = 0; i < ui->widget->count(); ++i){
        item = ui->widget->item(i);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked); }
    conn.mydb.close();
}

void tache::on_pushButton_supprimer_clicked()
{
    login conn;
    QSqlQuery* query= new QSqlQuery(conn.mydb);
    QString c;
    QListWidgetItem* item = 0;
    for(int i = 0; i < ui->widget->count(); ++i){
        item = ui->widget->item(i);
        if(item->checkState() == Qt::Checked)
        {
            c=item->text();
            query->prepare("delete from taches where text='"+c+"'");
            if (query->exec()) item->setHidden(1);
        }

    }
    conn.mydb.close();
}
