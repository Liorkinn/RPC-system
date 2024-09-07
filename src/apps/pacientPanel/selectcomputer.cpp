#include "selectcomputer.h"
#include "ui_selectcomputer.h"

SelectComputer::SelectComputer(Dbworker *p_dbworker, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectComputer)
{
    ui->setupUi(this);

    dbworker = p_dbworker;
    setComponentData("CPU", ui->comboBox_cpu);
    setComponentData("RAM", ui->comboBox_ram);
    setComponentData("GPU", ui->comboBox_gpu);
    setComponentData("Storage", ui->comboBox_storage);
    setComponentData("BP", ui->comboBox_blockPower);
}

SelectComputer::~SelectComputer()
{
    delete ui;
}

bool SelectComputer::setComponentData(const QString& componentName, QComboBox* comboBox)
{
    QVariantList componentData = dbworker->getComponents(componentName);

    if (componentData.isEmpty()) {
        return false;
    }

    QStringList listComponent;

    foreach (QVariant componentOption, componentData) {
        QVariantMap componentOptionMap = componentOption.toMap();
        listComponent.append(componentOptionMap["option_name"].toString());
    }

    comboBox->addItems(listComponent);

    return true;
}

bool SelectComputer::setDescriptionData(const QString &componentName, QLineEdit *lineEdit)
{
    QString descriptionData = dbworker->getDescriptionComponent(componentName);

    if (descriptionData.isEmpty()) {
        return false;
    }
    lineEdit->setText(descriptionData);
    return true;
}

void SelectComputer::on_comboBox_ram_currentTextChanged(const QString &arg1)
{
    QString currentRamText = ui->comboBox_ram->currentText();
    setDescriptionData(currentRamText, ui->lineEdit_ram);
}

void SelectComputer::on_comboBox_gpu_currentTextChanged(const QString &arg1)
{
    QString currentRamText = ui->comboBox_gpu->currentText();
    setDescriptionData(currentRamText, ui->lineEdit_gpu);
}

void SelectComputer::on_comboBox_cpu_currentTextChanged(const QString &arg1)
{
    QString currentRamText = ui->comboBox_cpu->currentText();
    setDescriptionData(currentRamText, ui->lineEdit_cpu);
}

void SelectComputer::on_comboBox_storage_currentTextChanged(const QString &arg1)
{
    QString currentRamText = ui->comboBox_storage->currentText();
    setDescriptionData(currentRamText, ui->lineEdit_storage);
}

void SelectComputer::on_comboBox_blockPower_currentTextChanged(const QString &arg1)
{
    QString currentRamText = ui->comboBox_blockPower->currentText();
    setDescriptionData(currentRamText, ui->lineEdit_blockPower);
}

void SelectComputer::on_button_selectComputer_clicked()
{
    ui->listWidget_computers->clear();

    QString currentRam = ui->comboBox_ram->currentText();
    QString currentGpu = ui->comboBox_gpu->currentText();
    QString currentCpu = ui->comboBox_cpu->currentText();
    QString currentStorage = ui->comboBox_storage->currentText();
    QString currentBlockPower = ui->comboBox_blockPower->currentText();

    QStringList listComputers = dbworker->getRecommendedComputers(currentRam, currentGpu, currentCpu, currentStorage, currentBlockPower);

    if (listComputers.isEmpty()) {
        ui->listWidget_computers->addItem("Компьютеры не найдены");
        return;
    }
    ui->listWidget_computers->addItems(listComputers);
}

void SelectComputer::on_listWidget_computers_itemDoubleClicked(QListWidgetItem *item)
{
    if (item->text() == "Компьютеры не найдены") {
        return;
    }
    QString pathImage = dbworker->getPicturePath(item->text());

    pictureDialog = new PictureDialog(pathImage);
    pictureDialog->show();
}









