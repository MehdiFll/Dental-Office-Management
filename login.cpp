#include "login.h"
#include "ui_login.h"
#include "principal.h"

login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);

    mydb= QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("ressources/bdd.db");
    if(!mydb.open()){
        ui->label->setText("Echec de connexion à la base de données");
    }
    else
        ui->label->setText(" ");
    ui->lineEdit_password->inputMask();
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_conn_clicked()
{
    QString username, password;
    username= ui->lineEdit_username->text();
    password= ui->lineEdit_password->text();


    QSqlQuery query;
    if(query.exec("select * from users where username='"+ username +"' and password='" + password+"'")){
        int count=0;
        while (query.next()) {
            count++;
        }
        if(count==1) {
            this->hide();
            principal p;
            p.setWindowTitle("Menu principal");
            p.setModal(true);
            p.exec();
        }
        if(count<1) {
            ui->label->setText("Nom d'utilisateur ou mot de passe erroné");
        }
        if(count>1) {
            ui->label->setText("Nom d'utilisateur dupliqué");
        }
    }

}
