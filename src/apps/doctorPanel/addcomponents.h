#ifndef ADDCOMPONENTS_H
#define ADDCOMPONENTS_H

#include <QDialog>
#include <QMessageBox>
#include "dbworker.h"

namespace Ui {
class AddComponents;
}

class AddComponents : public QDialog
{
    Q_OBJECT

public:
    explicit AddComponents(Dbworker *p_dbworker, QWidget *parent = nullptr);
    ~AddComponents();

public:
    void addItemTypeComponents();

private slots:
    void on_button_addComponent_clicked();

private:
    Ui::AddComponents *ui;
    Dbworker *dbworker;
};

#endif // ADDCOMPONENTS_H
