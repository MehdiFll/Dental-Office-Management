#ifndef LISTE_PATIENT_H
#define LISTE_PATIENT_H

#include <QDialog>

namespace Ui {
class Liste_patient;
}

class Liste_patient : public QDialog
{
    Q_OBJECT

public:
    explicit Liste_patient(QWidget *parent = 0);
    ~Liste_patient();
    QString id_index;

private slots:
    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_Button_archivage_clicked();

private:
    Ui::Liste_patient *ui;
};

#endif // LISTE_PATIENT_H
