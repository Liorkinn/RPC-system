#ifndef DOCTORPANEL_H
#define DOCTORPANEL_H

#include <QDialog>
#include <QCloseEvent>
#include <QMessageBox>

#include "changepassword.h"
#include "registerpatient.h"
#include "addcomputername.h"
#include "addcomponents.h"
#include "addconfiguration.h"

class Dbworker;

namespace Ui {
class DoctorPanel;
}

struct DoctorData {
    int userID;
    QString name;
    QString surname;
    QString patronymic;
    QString age;
    QString telephone;
    QString cabinetNumber;
    QString cabinetName;
    QString postType;
};

class DoctorPanel : public QDialog
{
    Q_OBJECT

public:
    explicit DoctorPanel(Dbworker *p_dbworker, QWidget *parent = nullptr);
    ~DoctorPanel();

    void setUserData(const int &p_userID, const QString &p_name, const QString &p_surname,
                     const QString &p_patronymic, const QString &p_age, const QString &p_telephone,
                     const QString &p_cabinetNumber, const QString &p_cabinetName, const QString &p_postType);

/*  Функции сеттеры
 * - setUserData - устанавливает данные о докторе (ФИО, должность и т.д.).
 * - setUserID - устанавливает текущий ид прользователя.
 * - setName - устанавливает имя пользователя.
 * - setSurname - устанавливает фамилию пользователя.
 * - setPatronymic - устанавливает отчество пользователя.
 * - setAge - устанавливает возраст пользователя.
 * - setTelephone - устанавливает телефон пользователя.
 * - setCabinetNumber - устанавливает номер кабинета пользователя.
 * - setCabinetName - устанавливает имя кабинета пользователя.
 * - setPostType - устанавливает должность пользователя.
*/
public:
    void setUserData           (const int& p_userID, const QString &p_name, const QString &p_surname, const QString &p_patronymic, const QString &p_age, const QString &p_telephone);

    void setUserID             (int p_userID)              { doctorData.userID = p_userID; }
    void setName               (QString p_name)            { doctorData.name = p_name; }
    void setSurname            (QString p_surname)         { doctorData.surname = p_surname; }
    void setPatronymic         (QString p_patronymic)      { doctorData.patronymic = p_patronymic; }
    void setAge                (QString p_age)             { doctorData.age = p_age; }
    void setTelephone          (QString p_telephone)       { doctorData.telephone = p_telephone; }
    void setCabinetNumber      (QString p_cabinetNum)      { doctorData.telephone = p_cabinetNum; }
    void setCabinetName        (QString p_cabinetName)     { doctorData.telephone = p_cabinetName; }
    void setPostType           (QString p_cabinetType)     { doctorData.telephone = p_cabinetType; }



/*  Функции геттеры
 * - getUserData - получение данных о докторе (ФИО, должность и т.д.).
 * - getUserID - получение текущего ид прользователя.
 * - getName - получение имя пользователя.
 * - getSurname - получение фамилии пользователя.
 * - getPatronymic - получение отчества пользователя.
 * - getAge - получение возраста пользователя.
 * - getTelephone - получение телефона пользователя.
 * - getCabinetNumber - получение номера кабинета пользователя.
 * - getCabinetName - получение имя кабинета пользователя.
 * - getPostType - получение должности пользователя.
*/
public:
    int getUserID              ()                          { return doctorData.userID; }
    QString getName            ()                          { return doctorData.name; }
    QString getSurname         ()                          { return doctorData.surname; }
    QString getPatronymic      ()                          { return doctorData.patronymic; }
    QString getAge             ()                          { return doctorData.age; }
    QString getTelephone       ()                          { return doctorData.telephone; }
    QString getCabinetNumber   ()                          { return doctorData.cabinetNumber; }
    QString getCabinetName     ()                          { return doctorData.cabinetName; }
    QString getPostType        ()                          { return doctorData.postType; }

private slots:
    void on_button_changePassword_clicked();

    void on_button_registrationUser_clicked();

    void on_button_addComponents_clicked();

    void on_button_configureComputer_clicked();

    void on_button_addComputerName_clicked();

signals:
    void closed();


/*  Переменные
 * - dbworker - объект для работы с БД.
 * - doctorData - объект структуры с пользовательскими данными доктора.
 * - appointPanel - объект формы записей пациентов.
 * - checkDyagPanel - объект формы постановки диагноза.
 * - changePwd - объект формы изменения пароля.
*/
private:
    Ui::DoctorPanel *ui;
    Dbworker* dbworker;
    DoctorData doctorData;
    changePassword *changePwd;
    RegisterPatient *registerPatient;
    AddComponents *addComponents;
    AddComputerName *addComputerName;
    AddConfiguration *addConfiguration;

};

#endif // DOCTORPANEL_H
