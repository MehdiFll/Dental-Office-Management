#ifndef TACHE_H
#define TACHE_H

#include "QListWidgetItem"
#include <QDialog>

namespace Ui {
class tache;
}

class tache : public QDialog
{
    Q_OBJECT

public:
    explicit tache(QWidget *parent = 0);
    ~tache();

    Ui::tache *ui;
private slots:
    void on_pushButton_ajouter_clicked();
    void on_pushButton_supprimer_clicked();
};

#endif // TACHE_H
