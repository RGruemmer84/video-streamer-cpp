#include "GUI/lynes_manager_main.h"
#include "ui_lynes_manager_main.h"


LynesManagerMain::LynesManagerMain(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::LynesManagerMain)
{
    ui->setupUi(this);
    ctrl = new AppController();
    InitializeGui();
}


LynesManagerMain::~LynesManagerMain()
{
    delete ui;
    delete ctrl;
}

void LynesManagerMain::InitializeGui()
{
    Lyne* lyne;
    string stream_active;
    QTableWidgetItem* item;
    ui->activeLyneTableWidget->setRowCount(ctrl->lynes->size());

    for (unsigned int l = 0; l < ctrl->lynes->size(); l++)
    {
        lyne = ctrl->lynes->at(l);
        stream_active = (lyne->info_params.stream_active) ? "Enabled": "Disabled";

        item = new QTableWidgetItem( QString::fromStdString(lyne->info_params.objectId) );
        item->setTextAlignment(Qt::AlignHCenter);
        ui->activeLyneTableWidget->setItem( l, 0, item);

        item = new QTableWidgetItem( QString::fromStdString(lyne->info_params.name) );
        item->setTextAlignment(Qt::AlignHCenter);
        ui->activeLyneTableWidget->setItem( l, 1, item);

        item = new QTableWidgetItem( QString::fromStdString(lyne->info_params.processId) );
        item->setTextAlignment(Qt::AlignHCenter);
        ui->activeLyneTableWidget->setItem( l, 2, item);

        item = new QTableWidgetItem( QString::fromStdString(stream_active) );
        item->setTextAlignment(Qt::AlignHCenter);
        ui->activeLyneTableWidget->setItem( l, 3, item);
    }


}

void LynesManagerMain::on_addLyneButton_clicked()
{
    edit_window = new EditLyneWindow(this, true, ctrl);
    edit_window->InitializeGui();
    edit_window->show();
}

void LynesManagerMain::on_LoadExistingLyneButton_clicked()
{
    //ctrl->LoadExistingLyne();
}

void LynesManagerMain::on_editLyneButton_clicked()
{
    int rowIndex = ui->activeLyneTableWidget->currentRow();

    if (rowIndex != -1)
    {
          ctrl->cur_lyne = ctrl->lynes->at(rowIndex);
    }
    edit_window = new EditLyneWindow(this, false, ctrl);

    if (!edit_window->isNewLine && ctrl->cur_lyne == NULL)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error",
            "Please select a Lyne to edit");
        messageBox.setFixedSize(500,200);
    }
    else
    {
        edit_window->InitializeGui();
        edit_window->show();
    }
}

void LynesManagerMain::on_removeLyne_clicked()
{
    //ctrl->RemoveLyne();
}

void LynesManagerMain::on_exportLineButton_clicked()
{
    //ctrl->ExportLyne();
}

void LynesManagerMain::on_tuneLyneButton_clicked()
{
    int rowIndex = ui->activeLyneTableWidget->currentRow();

    if (rowIndex != -1)
    {
          ctrl->cur_lyne = ctrl->lynes->at(rowIndex);
    }
    //tuner_window = new Tuner_Window(this, ctrl);
    chain_editor = new FilterChainEditorWindow(this, ctrl);

    if (ctrl->cur_lyne == NULL)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error",
            "Please select a Lyne to edit");
        messageBox.setFixedSize(500,200);
    }
    else
    {
        chain_editor->InitializeGui();
        chain_editor->show();
        //tuner_window->InitializeGui();
        //tuner_window->show();
    }
}

void LynesManagerMain::on_previewLyneButton_clicked()
{
    //ctrl->PreviewLyne();
}


