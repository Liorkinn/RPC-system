#ifndef PICTUREDIALOG_H
#define PICTUREDIALOG_H

#include <QDialog>
#include <QPixmap>
#include <QDebug>

namespace Ui {
class PictureDialog;
}

class PictureDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PictureDialog(QString p_picture_path, QWidget *parent = nullptr);
    ~PictureDialog();

public:
    void displayImage       (QString &imagePath);

private:
    Ui::PictureDialog *ui;
    QString picturePath;
};

#endif // PICTUREDIALOG_H
