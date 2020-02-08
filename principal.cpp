#include "principal.h"
#include "ui_principal.h"
#include "liste_patient.h"
#include "addp.h"
#include "addt.h"
#include "login.h"
#include "traitement.h"
#include "archive.h"
#include "addrdv.h"
#include "rdv.h"
#include<QtSql>
#include<QDebug>
#include<QFileInfo>
#include "tache.h"



principal::principal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::principal)
{
    QDate d=QDate::currentDate();
    ui->setupUi(this);
    ui->label->setText(d.toString("dddd dd MMMM yyyy"));
}

principal::~principal()
{
    delete ui;
}

void principal::on_pushButton_a_clicked()
{
    this->hide();
    Liste_patient p;
    p.setWindowTitle("Patients");
    p.setModal(true);
    p.exec();

}

void principal::on_pushButton_c_clicked()
{
    addp c;
    c.setWindowTitle("Ajouter un patient");
    c.setModal(true);
    c.exec();
}


void principal::on_pushButton_b_clicked()
{
    this->hide();
    traitement t;
    t.setWindowTitle("Liste des traitements");
    t.exec();
}

void principal::on_pushButton_d_clicked()
{
    addt t;
    t.setWindowTitle("Ajouter nouveau traitement");
    t.exec();
}

void principal::on_pushButton_e_clicked()
{
    this->hide();
    Archive v;
    v.setWindowTitle("Archive des patients");
    v.exec();
}

void principal::on_pushButton_f_clicked()
{
    this->hide();
    addrdv r;
    r.setWindowTitle("Ajouter nouveau rendez-vous");
    r.exec();
}

void principal::on_pushButton_clicked()
{
    rdv rdv;
    rdv.setWindowTitle("Liste des rendez-vous");
    rdv.exec();
    this->hide();
}

void principal::on_pushButton_g_clicked()
{
    tache w;
    w.setWindowTitle("Organisateur des tâches");
    w.exec();
}
