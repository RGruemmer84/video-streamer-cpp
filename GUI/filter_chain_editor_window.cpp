#include "filter_chain_editor_window.h"
#include "ui_filter_chain_editor_window.h"

FilterChainEditorWindow::FilterChainEditorWindow(QWidget *parent, AppController* ctrl) :
    QDialog(parent),
    ui(new Ui::FilterChainEditorWindow)
{
    ui->setupUi(this);
    this->ctrl = ctrl;
}

FilterChainEditorWindow::~FilterChainEditorWindow()
{
    delete ui;
}



void FilterChainEditorWindow::InitializeGui()
{
    QObject::connect( ctrl->cur_lyne->engine, SIGNAL(processedFrame(QImage)), this, SLOT(updatePlayerUi(QImage)) );

    ui->startTunerButton->setEnabled(true);
    ui->saveSetupButton->setEnabled(false);
    ui->cancelButton->setEnabled(false);

    InitializeVideoFormatBox();
    InitializeCurrentChainBox();
}

void FilterChainEditorWindow::InitializeVideoFormatBox(){
    ui->businessNameLabel->setText(QString::fromStdString(      ctrl->cur_lyne->info_params.name ));
    ui->durationLineEdit->setText(QString::number(              ctrl->cur_lyne->format_params.video_length_sec ));
    ui->fpsLineEdit->setText(QString::number(                   ctrl->cur_lyne->format_params.video_fps ));
    ui->xPixelsLineEdit->setText(QString::number(               ctrl->cur_lyne->format_params.x_pixels));
    ui->yPixelsLineEdit->setText(QString::number(               ctrl->cur_lyne->format_params.y_pixels));
    ui->grayScaleCheckBox->setChecked(                          ctrl->cur_lyne->format_params.is_gray_scale);
    ui->invertCheckBox->setChecked(                             ctrl->cur_lyne->format_params.is_inverted);
}

void FilterChainEditorWindow::InitializeCurrentChainBox(){
    QStringList list = QStringList();
    for (int i = 0; i <= AbstractFilter::NUM_FILTER_TYPES; i++) {
        list << AbstractFilter::TypeAsString(i);
    }

    ui->filterTypeComboBox->addItems(list);

    QStringList filterList;
    for (auto filter : ctrl->cur_lyne->engine->filterSetBuffer)
    {
        ui->filterChainListWidget->addItem(AbstractFilter::TypeAsString(filter->filter_type));
    }

}

void FilterChainEditorWindow::ClearChainBox()
{
    QStringList list = QStringList();
    ui->filterChainListWidget->clear();
    ui->filterTypeComboBox->clear();
}




//BUTTONS CALLBACKS
void FilterChainEditorWindow::on_startTunerButton_clicked()
{
    ui->videoFormatGroupBox->setEnabled(false);
    ui->cancelButton->setEnabled(true);
    ui->saveSetupButton->setEnabled(true);
    //original_filter_chain = new std::vector<LyneFilter*>(ctrl->cur_lyne->engine->filterSet);
    //original_filter_chain = std::shared_ptr<AbstractFilter>(ctrl->cur_lyne->engine->filterSet);
    //memcpy(original_filter_chain, &ctrl->cur_lyne->engine->filterSet, sizeof(ctrl->cur_lyne->engine->filterSet));
    ctrl->cur_lyne->StartEngine();
    tuningActive = true;
}

void FilterChainEditorWindow::on_saveSetupButton_clicked()
{
    ctrl->saveCurFilterChain();

}

void FilterChainEditorWindow::on_cancelButton_clicked()
{
    ctrl->cur_lyne->engine->filterSet = original_filter_chain;
    this->close();
}

//VIDEO FORMAT CALLBACKS
void FilterChainEditorWindow::on_durationLineEdit_textChanged(const QString &arg1)
{
    ctrl->cur_lyne->format_params.video_length_sec = arg1.toInt();
}

void FilterChainEditorWindow::on_fpsLineEdit_textChanged(const QString &arg1)
{
    ctrl->cur_lyne->format_params.video_fps = arg1.toInt();
}

void FilterChainEditorWindow::on_xPixelsLineEdit_textChanged(const QString &arg1)
{
    ctrl->cur_lyne->format_params.x_pixels = arg1.toDouble();
}

void FilterChainEditorWindow::on_yPixelsLineEdit_textChanged(const QString &arg1)
{
    ctrl->cur_lyne->format_params.x_pixels = arg1.toDouble();
}

void FilterChainEditorWindow::on_grayScaleCheckBox_clicked(bool checked)
{
    ctrl->cur_lyne->format_params.is_gray_scale = checked;
}

void FilterChainEditorWindow::on_invertCheckBox_clicked(bool checked)
{
    ctrl->cur_lyne->format_params.is_inverted = checked;
}

//SLOT CALL BACK FROM ENGINE SIGNAL
void FilterChainEditorWindow::updatePlayerUi(QImage frame_for_gui)
{
    //qDebug()<<"executing slot callback";

    if (!frame_for_gui.isNull())
    {
        ui->chainEditorPlayerWindow->setAlignment(Qt::AlignCenter);
        ui->chainEditorPlayerWindow->setPixmap(
            QPixmap::fromImage(frame_for_gui).scaled(ui->chainEditorPlayerWindow->size(), Qt::KeepAspectRatio,Qt::FastTransformation));


    }
}

void FilterChainEditorWindow::on_editFilterButton_clicked()
{
    if (!tuningActive)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error",
            "Please start tuner");
        messageBox.setFixedSize(500,200);
    }
    else if (ui->filterChainListWidget->size().isEmpty())
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error",
            "No Filters to edit");
        messageBox.setFixedSize(500,200);
    }
    else
    {
        int row = ui->filterChainListWidget->currentRow();
        if (row != -1)
        {
              //ctrl->curFilterToTune = &ctrl->cur_lyne->engine->slot[row];
              ctrl->curFilterToTune = ctrl->cur_lyne->engine->filterSet.at(row);
              tuner_window = new Tuner_Window(this, ctrl);
              tuner_window->InitializeGui();
              tuner_window->show();
        }
        else
        {QMessageBox messageBox;
            messageBox.critical(0,"Error",
                "Please select a filter to edit");
            messageBox.setFixedSize(500,200);
        }
    }


}

void FilterChainEditorWindow::on_addFilterButton_clicked()
{
    while (ctrl->cur_lyne->engine->filterSetBufferLocked)
    {
        for (int i = 0; i < 100000; i++){}
    }
    if (ctrl->cur_lyne->engine->filterSetBufferLocked) return;

    ctrl->cur_lyne->engine->filterSetBufferLocked = true;
    ctrl->addNewFilter(ui->filterTypeComboBox->currentIndex());
    ctrl->cur_lyne->engine->filterSetBufferLocked = false;

    ClearChainBox();
    InitializeCurrentChainBox();

    tuner_window = new Tuner_Window(this, ctrl);
    tuner_window->InitializeGui();
    tuner_window->show();
}



void FilterChainEditorWindow::on_removeFilterButton_clicked()
{
    if (!tuningActive)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error",
            "Please start tuner");
        messageBox.setFixedSize(500,200);
    }
    else if (ui->filterChainListWidget->size().isEmpty())
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error",
            "No Filters to remove");
        messageBox.setFixedSize(500,200);
    }
    else
    {
        int row = ui->filterChainListWidget->currentRow();
        if (row != -1)
        {

            while (ctrl->cur_lyne->engine->filterSetBufferLocked)
            {
                for (int i = 0; i < 100000; i++){}
            }
            if (ctrl->cur_lyne->engine->filterSetBufferLocked) return;

            ctrl->cur_lyne->engine->filterSetBufferLocked = true;
            ctrl->cur_lyne->engine->filterSetBuffer.erase(
                          ctrl->cur_lyne->engine->filterSetBuffer.begin() + row);
            ctrl->cur_lyne->engine->filterSetBufferLocked = false;
              ClearChainBox();
              InitializeCurrentChainBox();
        }
        else
        {QMessageBox messageBox;
            messageBox.critical(0,"Error",
                "Please select a filter to remove");
            messageBox.setFixedSize(500,200);
        }
    }
}

void FilterChainEditorWindow::on_upButton_clicked()
{
    if (!tuningActive)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error",
            "Please start tuner");
        messageBox.setFixedSize(500,200);
    }
    else if (ui->filterChainListWidget->size().isEmpty())
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error",
            "No Filters to move");
        messageBox.setFixedSize(500,200);
    }
    else
    {
        int row = ui->filterChainListWidget->currentRow();
        int filter_chain_size = ctrl->cur_lyne->engine->filterSetBuffer.size();
        if (row != -1)
        {

            if (row != 0 && filter_chain_size > 1) {
                while (ctrl->cur_lyne->engine->filterSetBufferLocked)
                {
                    for (int i = 0; i < 100000; i++){}
                }
                if (ctrl->cur_lyne->engine->filterSetBufferLocked) return;

                ctrl->cur_lyne->engine->filterSetBufferLocked = true;

                std::shared_ptr<AbstractFilter> temp = ctrl->cur_lyne->engine->filterSetBuffer.at(row);
                ctrl->cur_lyne->engine->filterSetBuffer.erase(
                            ctrl->cur_lyne->engine->filterSetBuffer.begin() + row);
                ctrl->cur_lyne->engine->filterSetBuffer.insert(
                            ctrl->cur_lyne->engine->filterSetBuffer.begin() + row - 1, temp);

                ctrl->cur_lyne->engine->filterSetBufferLocked = false;


                ClearChainBox();
                InitializeCurrentChainBox();
                ui->filterChainListWidget->setCurrentRow(row - 1);
            } else {
                QMessageBox messageBox;
                messageBox.critical(0,"Error",
                    "Cannot move filter up");
                messageBox.setFixedSize(500,200);
            }


        }
        else
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Error",
                "Please select a filter to move");
            messageBox.setFixedSize(500,200);
        }
    }
}

void FilterChainEditorWindow::on_downButton_clicked()
{
    if (!tuningActive)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error",
            "Please start tuner");
        messageBox.setFixedSize(500,200);
    }
    else if (ui->filterChainListWidget->size().isEmpty())
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error",
            "No Filters to move");
        messageBox.setFixedSize(500,200);
    }
    else
    {
        int row = ui->filterChainListWidget->currentRow();
        int filter_chain_size = ctrl->cur_lyne->engine->filterSet.size();
        if (row != -1)
        {
            if (row != filter_chain_size - 1 && filter_chain_size > 1) {

                while (ctrl->cur_lyne->engine->filterSetBufferLocked)
                {
                    for (int i = 0; i < 100000; i++){}
                }
                if (ctrl->cur_lyne->engine->filterSetBufferLocked) return;

                ctrl->cur_lyne->engine->filterSetBufferLocked = true;

                std::shared_ptr<AbstractFilter> temp = ctrl->cur_lyne->engine->filterSetBuffer.at(row);
                ctrl->cur_lyne->engine->filterSetBuffer.erase(
                            ctrl->cur_lyne->engine->filterSetBuffer.begin() + row);
                ctrl->cur_lyne->engine->filterSetBuffer.insert(
                            ctrl->cur_lyne->engine->filterSetBuffer.begin() + row + 1, temp);

                ctrl->cur_lyne->engine->filterSetBufferLocked = false;

                ClearChainBox();
                InitializeCurrentChainBox();
                ui->filterChainListWidget->setCurrentRow(row + 1);
            } else {
                QMessageBox messageBox;
                messageBox.critical(0,"Error",
                    "Cannot move filter down");
                messageBox.setFixedSize(500,200);
            }


        }
        else
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Error",
                "Please select a filter to move");
            messageBox.setFixedSize(500,200);
        }
    }
}

void FilterChainEditorWindow::on_toggleEnableDisableFilterButton_clicked()
{
    if (!tuningActive)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error",
            "Please start tuner");
        messageBox.setFixedSize(500,200);
    }
    else if (ui->filterChainListWidget->size().isEmpty())
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error",
            "No Filters to disable");
        messageBox.setFixedSize(500,200);
    }
    else
    {
        int row = ui->filterChainListWidget->currentRow();
        if (row != -1)
        {

            while (ctrl->cur_lyne->engine->filterSetBufferLocked)
            {
                for (int i = 0; i < 100000; i++){}
            }
            if (ctrl->cur_lyne->engine->filterSetBufferLocked) return;

            ctrl->cur_lyne->engine->filterSetBufferLocked = true;

              std::shared_ptr<AbstractFilter> temp = ctrl->cur_lyne->engine->filterSetBuffer.at(row);

              temp.get()->filter_enabled = !temp.get()->filter_enabled;
              ctrl->cur_lyne->engine->filterSetBufferLocked = false;

              ClearChainBox();
              InitializeCurrentChainBox();
              ui->filterChainListWidget->setCurrentRow(row);
        }
        else
        {QMessageBox messageBox;
            messageBox.critical(0,"Error",
                "Please select a filter to remove");
            messageBox.setFixedSize(500,200);
        }
    }
}


