#include "doctorpanel.h"
#include "ui_doctorpanel.h"

#include "dbworker.h"

DoctorPanel::DoctorPanel(Dbworker *p_dbworker, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DoctorPanel),
    dbworker(p_dbworker)
{
    ui->setupUi(this);
    this->setFixedSize(480, 281);
}

void DoctorPanel::setUserData(const int& p_userID, const QString &p_name, const QString &p_surname, const QString &p_patronymic,
                              const QString &p_age, const QString &p_telephone, const QString &p_cabinetNumber, const QString &p_cabinetName, const QString &p_postType)
{
    QString name = p_name;
    QString surname = p_surname;
    QString patronymic = p_patronymic;
    QString age = p_age;
    QString telephone = p_telephone;
    QString cabinetNumber = p_cabinetNumber;
    QString cabinetName = p_cabinetName;
    QString postType = p_postType;

    QString textInitialUser = QString("%1 %2 %3").arg(name).arg(surname).arg(patronymic);
    QString textAge = QString("%1 %2").arg("Возраст: ").arg(age);
    QString textTelephone = QString("%1 %2").arg("Телефон: ").arg(telephone);
    QString textCabinetInformation = QString ("%1 %2 %3").arg("Кабинет: ").arg(cabinetNumber + " - ").arg(cabinetName);
    QString textPostType = QString("%1 %2").arg("Должность: ").arg(postType);

    if (textInitialUser.isEmpty() || textAge.isEmpty() || textTelephone.isEmpty() || textCabinetInformation.isEmpty() || textPostType.isEmpty()) {
        return;
    }

    setUserID(p_userID);
    setName(p_name);
    setSurname(p_surname);
    setPatronymic(p_patronymic);
    setAge(p_age);
    setTelephone(p_telephone);
    setCabinetNumber(p_cabinetNumber);
    setCabinetName(p_cabinetName);
    setPostType(p_postType);

    ui->label_FIO->setText(textInitialUser);
    ui->label_age->setText(textAge);
    ui->label_telephone->setText(textTelephone);
    ui->label_cabinet->setText(textCabinetInformation);
    ui->label_post->setText(textPostType);
}

DoctorPanel::~DoctorPanel()
{
    delete ui;
}

void DoctorPanel::on_button_changePassword_clicked()
{
    changePwd = new changePassword(getUserID(), dbworker);
    changePwd->setWindowTitle("Изменение пароля");
    changePwd->show();
}
