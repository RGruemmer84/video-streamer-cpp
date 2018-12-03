#include "lynes_manager_tuner_window.h"
#include "ui_lynes_manager_tuner_window.h"

Tuner_Window::Tuner_Window(QWidget *parent, AppController* ctrl) :
    QDialog(parent),
    ui(new Ui::Tuner_Window)
{
    ui->setupUi(this);
    this->ctrl = ctrl;
}


Tuner_Window::~Tuner_Window()
{
    delete ui;
}


void Tuner_Window::InitializeGui()
{
    QObject::connect( ctrl->cur_lyne->engine, SIGNAL(processedFrame(QImage)), this, SLOT(updatePlayerUi(QImage)) );

    ui->tunerTitleLabel->setText(QString::fromStdString(AbstractFilter::TypeAsString(ctrl->curFilterToTune.get()->filter_type)));

    switch (ctrl->curFilterToTune.get()->filter_type)
    {
        //Low Pass
        case AbstractFilter::Type::BLUR:
            ui->tabWidget->setTabEnabled(0,false);
            ui->tabWidget->setTabEnabled(1,true);
            ui->tabWidget->setTabEnabled(2,false);
            InitializeForBlur();
            break;
        case AbstractFilter::Type::GAUSS_BLUR:
            ui->tabWidget->setTabEnabled(0,false);
            ui->tabWidget->setTabEnabled(1,true);
            ui->tabWidget->setTabEnabled(2,false);
            InitializeForGaussian();
            break;
        case AbstractFilter::Type::MEDIAN_BLUR:
            ui->tabWidget->setTabEnabled(0,false);
            ui->tabWidget->setTabEnabled(1,true);
            ui->tabWidget->setTabEnabled(2,false);
            InitializeForMedian();
            break;
        case AbstractFilter::Type::BILATERAL_FILTER:
            ui->tabWidget->setTabEnabled(0,false);
            ui->tabWidget->setTabEnabled(1,true);
            ui->tabWidget->setTabEnabled(2,false);
            InitializeForBilateral();
            break;


        //High Pass
        case AbstractFilter::Type::SOBEL:
            ui->tabWidget->setTabEnabled(0,false);
            ui->tabWidget->setTabEnabled(1,false);
            ui->tabWidget->setTabEnabled(2,true);
            InitializeEdgeDetectionTab(ctrl->curFilterToTune.get()->filter_type);
            break;
        case AbstractFilter::Type::LAPLACIAN:
            ui->tabWidget->setTabEnabled(0,false);
            ui->tabWidget->setTabEnabled(1,false);
            ui->tabWidget->setTabEnabled(2,true);
            InitializeEdgeDetectionTab(ctrl->curFilterToTune.get()->filter_type);
            break;
        case AbstractFilter::Type::MORPH:
            ui->tabWidget->setTabEnabled(0,false);
            ui->tabWidget->setTabEnabled(1,false);
            ui->tabWidget->setTabEnabled(2,true);
            InitializeEdgeDetectionTab(ctrl->curFilterToTune.get()->filter_type);
            break;


        //Essential
        case AbstractFilter::Type::ESSENTIAL:
            ui->tabWidget->setTabEnabled(0,true);
            ui->tabWidget->setTabEnabled(1,false);
            ui->tabWidget->setTabEnabled(2,false);
            InitializeEssentialTab();
            break;


        default:
            break;

    }




}

void Tuner_Window:: InitializeForBlur()
{
    InitializeLowPassTab(ctrl->curFilterToTune.get()->filter_type);

    ui->xKernalSizeDial->setValue( std::dynamic_pointer_cast<BlurFilter>(ctrl->curFilterToTune).get()->getKernel() );
    ui->yKernalSizeDial->setEnabled(                            false);
    ui->tabWidget->setCurrentIndex(1);
}

void Tuner_Window:: InitializeForGaussian()
{
    InitializeLowPassTab(ctrl->curFilterToTune.get()->filter_type);
    ui->guassianMatchKernelCheckBox->setEnabled(                true);
    ui->guassianMatchKernelCheckBox->setChecked(                true);
    ui->xKernalSizeDial->setEnabled(                            true);
    ui->xKernalSizeDial->setValue( std::dynamic_pointer_cast<GaussianFilter>(ctrl->curFilterToTune).get()->getXKernel() );


    if (!ui->guassianMatchKernelCheckBox->isChecked())

    {
        ui->yKernalSizeDial->setEnabled(                         true);
        ui->yKernalSizeDial->setValue( std::dynamic_pointer_cast<GaussianFilter>(ctrl->curFilterToTune).get()->getXKernel() );
    }
    else
    {
        ui->yKernalSizeDial->setEnabled(                        false);
    }

    ui->tabWidget->setCurrentIndex(1);
}

void Tuner_Window:: InitializeForMedian()
{
    InitializeLowPassTab(ctrl->curFilterToTune.get()->filter_type);
    ui->xKernalSizeDial->setValue( std::dynamic_pointer_cast<MedianFilter>(ctrl->curFilterToTune).get()->getKernel());
    ui->yKernalSizeDial->setEnabled(                            false);
    ui->tabWidget->setCurrentIndex(1);
}

void Tuner_Window:: InitializeForBilateral()
{
    InitializeLowPassTab(ctrl->curFilterToTune.get()->filter_type);

    ui->xKernalSizeDial->setEnabled(                            false);
    ui->yKernalSizeDial->setEnabled(                            false);

    ui->bilateralDiameterLabel->setEnabled(                     true);
    ui->bilateralDiameterLineEdit->setEnabled(                  true);
    ui->sigmaClearLabel->setEnabled(                            true);
    ui->sigmaClearLineEdit->setEnabled(                         true);
    ui->sigmaSpaceLabel->setEnabled(                            true);
    ui->sigmaSpaceLineEdit->setEnabled(                         true);

    ui->bilateralDiameterLineEdit->setText( QString::number( std::dynamic_pointer_cast<BilateralFilter>(ctrl->curFilterToTune).get()->getDiameter() ) );
    ui->sigmaClearLineEdit->setText( QString::number( std::dynamic_pointer_cast<BilateralFilter>(ctrl->curFilterToTune).get()->getSigmaClear() ) );
    ui->sigmaSpaceLineEdit->setText( QString::number( std::dynamic_pointer_cast<BilateralFilter>(ctrl->curFilterToTune).get()->getSigmaSpace() ) );

    ui->tabWidget->setCurrentIndex(1);
}



void Tuner_Window::InitializeEssentialTab()
{
    ui->imageAdjustGroupBox->setChecked(true);
    ui->tabWidget->setCurrentIndex(0);
}

void Tuner_Window::InitializeLowPassTab(AbstractFilter::Type t)
{
    ui->lowPassGroupBox->setChecked(                            true);


    switch (t)
    {
    case AbstractFilter::Type::BLUR:
        ui->guassianRadioButton->setEnabled(                        false);
        ui->guassianRadioButton->setChecked(                        false);
        ui->simpleRadioButton->setEnabled(                          true);
        ui->simpleRadioButton->setChecked(                          true);
        ui->medianRadioButton->setEnabled(                          false);
        ui->medianRadioButton->setChecked(                          false);
        ui->bilateralRadioButton->setEnabled(                       false);
        ui->bilateralRadioButton->setChecked(                       false);
        break;

    case AbstractFilter::Type::GAUSS_BLUR:
        ui->guassianRadioButton->setEnabled(                        true);
        ui->guassianRadioButton->setChecked(                        true);
        ui->simpleRadioButton->setEnabled(                          false);
        ui->simpleRadioButton->setChecked(                          false);
        ui->medianRadioButton->setEnabled(                          false);
        ui->medianRadioButton->setChecked(                          false);
        ui->bilateralRadioButton->setEnabled(                       false);
        ui->bilateralRadioButton->setChecked(                       false);
        break;

    case AbstractFilter::Type::MEDIAN_BLUR:
        ui->guassianRadioButton->setEnabled(                        false);
        ui->guassianRadioButton->setChecked(                        false);
        ui->simpleRadioButton->setEnabled(                          false);
        ui->simpleRadioButton->setChecked(                          false);
        ui->medianRadioButton->setEnabled(                          true);
        ui->medianRadioButton->setChecked(                          true);
        ui->bilateralRadioButton->setEnabled(                       false);
        ui->bilateralRadioButton->setChecked(                       false);
        break;

    case AbstractFilter::Type::BILATERAL_FILTER:
        ui->guassianRadioButton->setEnabled(                        false);
        ui->guassianRadioButton->setChecked(                        false);
        ui->simpleRadioButton->setEnabled(                          false);
        ui->simpleRadioButton->setChecked(                          false);
        ui->medianRadioButton->setEnabled(                          false);
        ui->medianRadioButton->setChecked(                          false);
        ui->bilateralRadioButton->setEnabled(                       true);
        ui->bilateralRadioButton->setChecked(                       true);
        break;

    case AbstractFilter::Type::NONE:
    case AbstractFilter::Type::SOBEL:
    case AbstractFilter::Type::LAPLACIAN:
    case AbstractFilter::Type::MORPH:
    case AbstractFilter::Type::ESSENTIAL:
            break;

    }


    ui->bilateralDiameterLabel->setEnabled(                     false);
    ui->bilateralDiameterLineEdit->setEnabled(                  false);
    ui->sigmaClearLabel->setEnabled(                            false);
    ui->sigmaClearLineEdit->setEnabled(                         false);
    ui->sigmaSpaceLabel->setEnabled(                            false);
    ui->sigmaSpaceLineEdit->setEnabled(                         false);

    ui->guassianMatchKernelCheckBox->setEnabled(                false);

}

void Tuner_Window::InitializeEdgeDetectionTab(AbstractFilter::Type t)
{
    ui->highPassGroupBox->setChecked(                           true);

    switch (t)
    {
    case AbstractFilter::Type::SOBEL:
        ui->sobelRadioButton->setEnabled(true);
        ui->sobelRadioButton->setChecked(true);
        ui->sobelXWeightSlider->setValue( std::dynamic_pointer_cast<SobelFilter>(ctrl->curFilterToTune).get()->getXWeight() );
        ui->sobelYWeightSlider->setValue( std::dynamic_pointer_cast<SobelFilter>(ctrl->curFilterToTune).get()->getYWeight() );
        ui->sobelGammaSlider->setValue( std::dynamic_pointer_cast<SobelFilter>(ctrl->curFilterToTune).get()->getGamma() );
        ui->sobelKernalSizeSlider->setValue( std::dynamic_pointer_cast<SobelFilter>(ctrl->curFilterToTune).get()->getKernel() );

        ui->laplacianRadioButton->setEnabled(false);
        ui->laplacianRadioButton->setChecked(false);
        ui->laplacianScaleSlider->setEnabled(false);
        ui->laplacianKernalSlider->setEnabled(false);
        ui->morphRadioButton->setEnabled(false);
        ui->morphRadioButton->setChecked(false);
        ui->morphElementSlider->setEnabled(false);
        ui->morphSizeSlider->setEnabled(false);
        ui->morphIterationSlider->setEnabled(false);
        ui->morphOperationSlider->setEnabled(false);

        break;

    case AbstractFilter::Type::LAPLACIAN:
        ui->laplacianRadioButton->setEnabled(true);
        ui->laplacianRadioButton->setChecked(true);
        ui->laplacianScaleSlider->setValue( std::dynamic_pointer_cast<LaplacianFilter>(ctrl->curFilterToTune).get()->getScale() );
        ui->laplacianKernalSlider->setValue( std::dynamic_pointer_cast<LaplacianFilter>(ctrl->curFilterToTune).get()->getKernel() );


        ui->sobelRadioButton->setEnabled(false);
        ui->sobelRadioButton->setChecked(false);
        ui->sobelXWeightSlider->setEnabled(false);
        ui->sobelYWeightSlider->setEnabled(false);
        ui->sobelGammaSlider->setEnabled(false);
        ui->sobelKernalSizeSlider->setEnabled(false);
        ui->morphRadioButton->setEnabled(false);
        ui->morphRadioButton->setChecked(false);
        ui->morphElementSlider->setEnabled(false);
        ui->morphSizeSlider->setEnabled(false);
        ui->morphIterationSlider->setEnabled(false);
        ui->morphOperationSlider->setEnabled(false);


        break;

    case AbstractFilter::Type::MORPH:

        ui->morphRadioButton->setEnabled(true);
        ui->morphRadioButton->setChecked(true);
        ui->morphElementSlider->setValue( std::dynamic_pointer_cast<MorphFilter>(ctrl->curFilterToTune).get()->getElement() );
        ui->morphSizeSlider->setValue( std::dynamic_pointer_cast<MorphFilter>(ctrl->curFilterToTune).get()->getSize() );
        ui->morphIterationSlider->setValue( std::dynamic_pointer_cast<MorphFilter>(ctrl->curFilterToTune).get()->getIterations() );
        ui->morphOperationSlider->setValue( std::dynamic_pointer_cast<MorphFilter>(ctrl->curFilterToTune).get()->getOperation() );


        ui->sobelRadioButton->setEnabled(false);
        ui->sobelRadioButton->setChecked(false);
        ui->sobelXWeightSlider->setEnabled(false);
        ui->sobelYWeightSlider->setEnabled(false);
        ui->sobelGammaSlider->setEnabled(false);
        ui->sobelKernalSizeSlider->setEnabled(false);
        ui->laplacianRadioButton->setEnabled(false);
        ui->laplacianRadioButton->setChecked(false);
        ui->laplacianScaleSlider->setEnabled(false);
        ui->laplacianKernalSlider->setEnabled(false);

        break;

    case AbstractFilter::Type::NONE:
    case AbstractFilter::Type::BLUR:
    case AbstractFilter::Type::BILATERAL_FILTER:
    case AbstractFilter::Type::GAUSS_BLUR:
    case AbstractFilter::Type::MEDIAN_BLUR:
    case AbstractFilter::Type::ESSENTIAL:
        break;
    }





    ui->tabWidget->setCurrentIndex(2);
}





//IMAGE ADJUST CALLBACKS

void Tuner_Window::on_contrastSlider_sliderMoved(int position)
{
    std::dynamic_pointer_cast<EssentialFilter>(ctrl->curFilterToTune).get()->setContrast(double(position)*.05);
}

void Tuner_Window::on_brightnessSlider_sliderMoved(int position)
{
    std::dynamic_pointer_cast<EssentialFilter>(ctrl->curFilterToTune).get()->setBrightness(position);
}




//LOW PASS FILTERS CALLBACKS

void Tuner_Window::on_xKernalSizeDial_valueChanged(int value)
{

    switch (ctrl->curFilterToTune->filter_type)
    {
        //Low Pass
        case AbstractFilter::Type::BLUR:
                if (value > 15 || value < 1) return;
                std::dynamic_pointer_cast<BlurFilter>(ctrl->curFilterToTune).get()->setKernel(value);
            break;

        case AbstractFilter::Type::GAUSS_BLUR:
            if (value % 2 != 1 || value < 1) return;

            if (ui->guassianMatchKernelCheckBox->isChecked())
            {
                std::dynamic_pointer_cast<GaussianFilter>(ctrl->curFilterToTune).get()->setXKernel(value);
                std::dynamic_pointer_cast<GaussianFilter>(ctrl->curFilterToTune).get()->setYKernel(value);
            }
            else
            {
                std::dynamic_pointer_cast<GaussianFilter>(ctrl->curFilterToTune).get()->setXKernel(value);
            }

            break;

        case AbstractFilter::Type::MEDIAN_BLUR:
                if (value % 2 != 1 || value < 1) return;

                std::dynamic_pointer_cast<MedianFilter>(ctrl->curFilterToTune).get()->setKernel(value);
            break;


        default:
            break;
    }

}

void Tuner_Window::on_yKernalSizeDial_valueChanged(int value)
{
    if (!ui->guassianMatchKernelCheckBox->isChecked() && value % 2 == 1 && value > 0 && value <256)
        std::dynamic_pointer_cast<GaussianFilter>(ctrl->curFilterToTune).get()->setYKernel(value);
}



void Tuner_Window::on_guassianMatchKernelCheckBox_clicked(bool checked)
{
    ui->yKernalSizeDial->setEnabled(!checked);
}



void Tuner_Window::on_sigmaClearLineEdit_editingFinished()
{
    std::dynamic_pointer_cast<BilateralFilter>(ctrl->curFilterToTune).get()->setSigmaClear( ui->sigmaClearLineEdit->text().toDouble() );
}

void Tuner_Window::on_sigmaSpaceLineEdit_editingFinished()
{
    std::dynamic_pointer_cast<BilateralFilter>(ctrl->curFilterToTune).get()->setSigmaSpace( ui->sigmaSpaceLineEdit->text().toDouble() );
}

void Tuner_Window::on_bilateralDiameterLineEdit_editingFinished()
{
    std::dynamic_pointer_cast<BilateralFilter>(ctrl->curFilterToTune).get()->setDiameter( ui->bilateralDiameterLineEdit->text().toDouble() );
}



//SOBEL CALLBACKS

void Tuner_Window::on_sobelXWeightSlider_valueChanged(int value)
{
    std::dynamic_pointer_cast<SobelFilter>(ctrl->curFilterToTune).get()->setXWeight( value );
}

void Tuner_Window::on_sobelYWeightSlider_valueChanged(int value)
{
    std::dynamic_pointer_cast<SobelFilter>(ctrl->curFilterToTune).get()->setYWeight( value );
}

void Tuner_Window::on_sobelGammaSlider_valueChanged(int value)
{
    std::dynamic_pointer_cast<SobelFilter>(ctrl->curFilterToTune).get()->setGamma( value );
}

void Tuner_Window::on_sobelKernalSizeSlider_valueChanged(int value)
{
    std::dynamic_pointer_cast<SobelFilter>(ctrl->curFilterToTune).get()->setKernel( value );
}




//LAPLACIAN CALLBACKS

void Tuner_Window::on_laplacianScaleSlider_valueChanged(int value)
{
    std::dynamic_pointer_cast<LaplacianFilter>(ctrl->curFilterToTune).get()->setScale( (double) value );
}

void Tuner_Window::on_laplacianKernalSlider_valueChanged(int value)
{
    std::dynamic_pointer_cast<LaplacianFilter>(ctrl->curFilterToTune).get()->setKernel( value );
}

//MORPH CALLBACKS
void Tuner_Window::on_morphTypeLineEdit_editingFinished()
{
    std::dynamic_pointer_cast<MorphFilter>(ctrl->curFilterToTune).get()->setType( ui->morphTypeLineEdit->text().toInt() );
}

void Tuner_Window::on_morphElementSlider_valueChanged(int value)
{
    std::dynamic_pointer_cast<MorphFilter>(ctrl->curFilterToTune).get()->setElement( value );
}

void Tuner_Window::on_morphSizeSlider_valueChanged(int value)
{
    std::dynamic_pointer_cast<MorphFilter>(ctrl->curFilterToTune).get()->setSize( value );
}

void Tuner_Window::on_morphIterationSlider_valueChanged(int value)
{
    std::dynamic_pointer_cast<MorphFilter>(ctrl->curFilterToTune).get()->setIterations( value );
}

void Tuner_Window::on_morphOperationSlider_valueChanged(int value)
{
    std::dynamic_pointer_cast<MorphFilter>(ctrl->curFilterToTune).get()->setOperation( value );
}


//CANNY CALLBACKS

//void Tuner_Window::on_cannyHiThreshSlider_valueChanged(int value)
//{
//    std::dynamic_pointer_cast<CannyFilter>(ctrl->curFilterToTune).get()->setHighThresh( value );
//}

//void Tuner_Window::on_cannyLoThreshSlider_valueChanged(int value)
//{
//    std::dynamic_pointer_cast<CannyFilter>(ctrl->curFilterToTune).get()->setLowThresh( value );
//}

//void Tuner_Window::on_cannyKernalSizeSlider_valueChanged(int value)
//{
//    std::dynamic_pointer_cast<CannyFilter>(ctrl->curFilterToTune).get()->setKernel( value );
//}


//SLOT CALL BACK FROM ENGINE SIGNAL
void Tuner_Window::updatePlayerUi(QImage frame_for_gui)
{
    //qDebug()<<"executing slot callback";

    if (!frame_for_gui.isNull())
    {
        ui->playerWindow->setAlignment(Qt::AlignCenter);
        ui->playerWindow->setPixmap(
            QPixmap::fromImage(frame_for_gui).scaled(ui->playerWindow->size(), Qt::KeepAspectRatio,Qt::FastTransformation));


    }
}


