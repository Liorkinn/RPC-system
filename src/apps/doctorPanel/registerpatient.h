#ifndef REGISTERPATIENT_H
#define REGISTERPATIENT_H

#include <QDialog>
#include <QMessageBox>

#include "dbworker.h"

namespace Ui {
class RegisterPatient;
}

class RegisterPatient : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterPatient(Dbworker *p_dbworker, QWidget *parent = nullptr);
    ~RegisterPatient();

private slots:
    void on_button_registratePatient_clicked();

/*  Переменные
 * - dbworker - объект для работы с БД.
*/
private:
    Ui::RegisterPatient *ui;
    Dbworker *dbworker;
};

#endif // REGISTERPATIENT_H
