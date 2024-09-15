#include "addcomponents.h"
#include "ui_addcomponents.h"

AddComponents::AddComponents(Dbworker *p_dbworker, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddComponents)
{
    ui->setupUi(this);
    dbworker = p_dbworker;
    addItemTypeComponents();
}

AddComponents::~AddComponents()
{
    delete ui;
}

void AddComponents::addItemTypeComponents()
{
    QStringList listTypeComponents = dbworker->getComponentTypes();

    if (listTypeComponents.isEmpty()) {
        return;
    }
    ui->comboBox_typeComponent->addItems(listTypeComponents);
}

void AddComponents::on_button_addComponent_clicked()
{
    int componentIndex = ui->comboBox_typeComponent->currentIndex() + 1;
    QString componentName = ui->lineEdit_componentName->text();
    QString componentDescription = ui->lineEdit_description->text();

    if (componentName.isEmpty() || componentDescription.isEmpty()) {
        QMessageBox::warning(0, "Комплектующее", "Пожалуйста, заполните все поля!");
        return;
    }
    qDebug() << componentIndex;
    bool isAddComponent = dbworker->addComponent(componentIndex, componentName, componentDescription);

    if (isAddComponent) {
        QMessageBox::information(0, "Комплектующее", "Комплектующего добавлено успешно!");
        return;
    }
    QMessageBox::critical(0, "Комплектующее", "Ошибка добавления комплектующего!");
}
