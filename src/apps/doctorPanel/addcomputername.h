#ifndef ADDCOMPUTERNAME_H
#define ADDCOMPUTERNAME_H

#include <QDialog>
#include <QMessageBox>
#include "dbworker.h"

namespace Ui {
class AddComputerName;
}

class AddComputerName : public QDialog
{
    Q_OBJECT

public:
    explicit AddComputerName(Dbworker *p_dbworker, QWidget *parent = nullptr);
    ~AddComputerName();

public:
    void addComputer();
private slots:
    void on_button_addComputerName_clicked();

private:
    Ui::AddComputerName *ui;
    Dbworker *dbworker;
};

#endif // ADDCOMPUTERNAME_H
