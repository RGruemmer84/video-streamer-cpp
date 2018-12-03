#ifndef TUNER_WINDOW_H
#define TUNER_WINDOW_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QTime>
#include <Application/Controller/app_controller_class.h>
#include "Application/Filters/abstract_filter_class.h"
#include "Application/Filters/bilateral_filter_class.h"
#include "Application/Filters/blur_filter_class.h"
#include "Application/Filters/morph_filter_class.h"
#include "Application/Filters/essential_filter_class.h"
#include "Application/Filters/gaussian_filter_class.h"
#include "Application/Filters/laplacian_filter_class.h"
#include "Application/Filters/median_filter_class.h"
#include "Application/Filters/sobel_filter_class.h"

class AppController;

namespace Ui {
class Tuner_Window;
}

class Tuner_Window : public QDialog
{
    Q_OBJECT
    AppController *ctrl;


public:
    explicit Tuner_Window(QWidget *parent = 0, AppController*  ctrl = NULL);
    ~Tuner_Window();
    void InitializeGui();


private:
    Ui::Tuner_Window *ui;
    QImage image_to_display;


    void InitializeEssentialTab();
    void InitializeLowPassTab(AbstractFilter::Type t);
    void InitializeEdgeDetectionTab(AbstractFilter::Type t);

    void InitializeForBlur();
    void InitializeForGaussian();
    void InitializeForMedian();
    void InitializeForBilateral();



private slots:

    //Callback from engine to display frame to screen
    void updatePlayerUi(QImage frame_for_gui);


    //IMAGE ADJUST (brightness & contrast)
    void on_contrastSlider_sliderMoved(int position);
    void on_brightnessSlider_sliderMoved(int position);


    //GUASSIAN
    void on_guassianMatchKernelCheckBox_clicked(bool checked);
    void on_xKernalSizeDial_valueChanged(int value);
    void on_yKernalSizeDial_valueChanged(int value);

    //BILATERAL
    void on_sigmaClearLineEdit_editingFinished();
    void on_sigmaSpaceLineEdit_editingFinished();
    void on_bilateralDiameterLineEdit_editingFinished();


    //SOBEL
    void on_sobelXWeightSlider_valueChanged(int value);
    void on_sobelYWeightSlider_valueChanged(int value);
    void on_sobelGammaSlider_valueChanged(int value);
    void on_sobelKernalSizeSlider_valueChanged(int value);

    //LAPLACIAN
    void on_laplacianScaleSlider_valueChanged(int value);
    void on_laplacianKernalSlider_valueChanged(int value);

    //CANNY
//    void on_cannyHiThreshSlider_valueChanged(int value);
//    void on_cannyLoThreshSlider_valueChanged(int value);
//    void on_cannyKernalSizeSlider_valueChanged(int value);


    //MORPH
    void on_morphTypeLineEdit_editingFinished();
    void on_morphElementSlider_valueChanged(int value);
    void on_morphSizeSlider_valueChanged(int value);
    void on_morphIterationSlider_valueChanged(int value);
    void on_morphOperationSlider_valueChanged(int value);
};

#endif // TUNER_WINDOW_H
