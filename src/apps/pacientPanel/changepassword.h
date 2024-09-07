#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H

#include <QDialog>
#include <QMessageBox>

#include "dbworker.h"

namespace Ui {
class changePassword;
}

class changePassword : public QDialog
{
    Q_OBJECT

public:
    explicit changePassword(int p_userId, Dbworker* p_dbworker, QWidget *parent = nullptr);
    ~changePassword();

/*  Функция сеттер
 * - setUserId - установка ид пользователя.
*/
public:
    void setUserId      (int p_userID)      { userId = p_userID; }

/*  Функция геттер
 * - setUserId - получение ид пользователя.
*/
public:
    int getUserId       ()                  { return userId; }

private slots:
    void on_button_setPassword_clicked();

private:
    Ui::changePassword *ui;
    Dbworker *dbworker;
    int userId;
};

#endif // CHANGEPASSWORD_H
