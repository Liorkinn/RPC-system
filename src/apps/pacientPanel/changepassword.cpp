#include "changepassword.h"
#include "ui_changepassword.h"

changePassword::changePassword(int p_userId, Dbworker *p_dbworker, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changePassword)
{
    ui->setupUi(this);
    this->setFixedSize(274, 109);
    dbworker = p_dbworker;
    setUserId(p_userId);
}

changePassword::~changePassword()
{
    delete ui;
}

void changePassword::on_button_setPassword_clicked()
{
    QString oldPassword = ui->lineEdit_oldPassword->text();
    QString newPassword = ui->lineEdit_newPassword->text();

    if (oldPassword.isEmpty() || newPassword.isEmpty()) {
        QMessageBox::warning(0, "Изменение пароля", "Пожалуйста, заполните все поля");
        return;
    }

    bool success = dbworker->changeUserPassword(getUserId(), oldPassword, newPassword); // Замените 1 на id нужного пользователя
    if (success) {
        QMessageBox::information(0, "Изменение пароля", "Пароль успешно изменен.");
    } else {
        QMessageBox::warning(0, "Изменение пароля", "Пароль не изменен.");
    }
}
