#ifndef FILTER_CHAIN_EDITOR_WINDOW_H
#define FILTER_CHAIN_EDITOR_WINDOW_H

#include <QDialog>
#include <Application/Controller/app_controller_class.h>
#include <GUI/lynes_manager_tuner_window.h>

namespace Ui {
class FilterChainEditorWindow;
}

class FilterChainEditorWindow : public QDialog
{
    Q_OBJECT
    AppController *ctrl;
    Tuner_Window* tuner_window;

public:
    explicit FilterChainEditorWindow(QWidget *parent = 0, AppController*  ctrl = NULL);
    ~FilterChainEditorWindow();

    void InitializeGui();

private:
    Ui::FilterChainEditorWindow *ui;
    QImage image_to_display;

    bool tuningActive = false;
    std::vector<std::shared_ptr<AbstractFilter>> original_filter_chain;

    void InitializeVideoFormatBox();
    void InitializeCurrentChainBox();
    void ClearChainBox();

private slots:
    void updatePlayerUi(QImage frame_for_gui);

    //BUTTONS  (start, stop, cancel)
    void on_startTunerButton_clicked();
    void on_saveSetupButton_clicked();
    void on_cancelButton_clicked();

    //VIDEO_FORMAT (FPS and length)
    void on_durationLineEdit_textChanged(const QString &arg1);
    void on_fpsLineEdit_textChanged(const QString &arg1);
    void on_xPixelsLineEdit_textChanged(const QString &arg1);
    void on_yPixelsLineEdit_textChanged(const QString &arg1);
    void on_editFilterButton_clicked();
    void on_addFilterButton_clicked();
    void on_grayScaleCheckBox_clicked(bool checked);
    void on_toggleEnableDisableFilterButton_clicked();
    void on_removeFilterButton_clicked();
    void on_upButton_clicked();
    void on_downButton_clicked();

    void on_invertCheckBox_clicked(bool checked);
};

#endif // FILTER_CHAIN_EDITOR_WINDOW_H
