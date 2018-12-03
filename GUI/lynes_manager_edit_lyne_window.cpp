#include "lynes_manager_edit_lyne_window.h"
#include "ui_lynes_manager_edit_lyne_window.h"

EditLyneWindow::EditLyneWindow(QWidget *parent, bool isNewLine, AppController* ctrl) :
    QDialog(parent),
    ui(new Ui::EditLyneWindow)
{
    ui->setupUi(this);
    this->ctrl = ctrl;
    this->isNewLine = isNewLine;
}

EditLyneWindow::~EditLyneWindow()
{
    delete ui;
}


void EditLyneWindow::InitializeGui()
{
    if (!isNewLine)
    {
        ui->objectIdLineEdit->setText(QString::fromStdString(           ctrl->cur_lyne->info_params.objectId));
        ui->businessNameLineEdit->setText(QString::fromStdString(       ctrl->cur_lyne->info_params.name));
        ui->regionLineEdit->setText(QString::fromStdString(             ctrl->cur_lyne->info_params.region));
        ui->businessTypeLineEdit->setText(QString::fromStdString(       ctrl->cur_lyne->info_params.type));
        ui->businessAddressLineEdit->setText(QString::fromStdString(    ctrl->cur_lyne->info_params.address));
        ui->businessPhoneLineEdit->setText(QString::fromStdString(      ctrl->cur_lyne->info_params.phone));

        ui->special1LineEdit->setText(QString::fromStdString(           ctrl->cur_lyne->info_params.special_1));
        ui->special2LineEdit->setText(QString::fromStdString(           ctrl->cur_lyne->info_params.special_2));
        ui->special3LineEdit->setText(QString::fromStdString(           ctrl->cur_lyne->info_params.special_3));
        ui->special4LineEdit->setText(QString::fromStdString(           ctrl->cur_lyne->info_params.special_4));

        ui->utcOffsetLineEdit->setText(QString::number(          ctrl->cur_lyne->info_params.utcOffset));

        ui->streamActiveCheckBox->setChecked(                           ctrl->cur_lyne->info_params.stream_active);
        ui->processIdLineEdit->setText(QString::fromStdString(          ctrl->cur_lyne->info_params.processId));

        if (ctrl->cur_lyne->info_params.processId.find("srv") == std::string::npos)
        {
            ui->camUrlLineEdit->setText(QString::fromStdString(         ctrl->cur_lyne->info_params.cam_url));
            ui->camUrlLineEdit->setEnabled(true);
        }
        else
        {
            ui->camUrlLineEdit->setText(QString("N/A"));
        }


    }

}

void EditLyneWindow::on_resetButton_clicked()
{

}

void EditLyneWindow::on_cancelButton_clicked()
{
    this->close();
}

void EditLyneWindow::on_saveButton_clicked()
{

}
