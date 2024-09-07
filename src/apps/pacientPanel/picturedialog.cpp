#include "picturedialog.h"
#include "ui_picturedialog.h"

const QString ERROR_PICTURE = "/home/liora/picturesComputer/error.png";

PictureDialog::PictureDialog(QString p_picture_path, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PictureDialog)
{
    ui->setupUi(this);
    picturePath = p_picture_path;
    displayImage(picturePath);
    this->setWindowTitle("Изображение компьютера");
}

PictureDialog::~PictureDialog()
{
    delete ui;
}

void PictureDialog::displayImage(QString &imagePath)
{
    QPixmap pixmap(imagePath);

   // Проверяем, удалось ли загрузить изображение
   if (pixmap.isNull()) {
       QPixmap pixmapError(ERROR_PICTURE);
       ui->label_picture->setScaledContents(true);
       ui->label_picture->setPixmap(pixmapError);
       return;
   }

   ui->label_picture->setScaledContents(true);

   ui->label_picture->setPixmap(pixmap);


}
