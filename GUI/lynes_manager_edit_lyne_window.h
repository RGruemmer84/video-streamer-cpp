#ifndef LYNES_MANAGER_EDIT_LYNE_WINDOW_H
#define LYNES_MANAGER_EDIT_LYNE_WINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <Application/Controller/app_controller_class.h>


namespace Ui {
class EditLyneWindow;
}

class EditLyneWindow : public QDialog
{
    Q_OBJECT
    AppController *ctrl;


    public:     //members
        bool isNewLine;

    public:     //methods
        explicit EditLyneWindow(QWidget *parent = 0, bool isNewLine = false, AppController* ctrl = NULL);
        ~EditLyneWindow();
        void InitializeGui();



    private:    //members
        Ui::EditLyneWindow *ui;

    private:    //methods


    private slots:
        void on_resetButton_clicked();
        void on_cancelButton_clicked();
        void on_saveButton_clicked();

};

#endif // LYNES_MANAGER_EDIT_LYNE_WINDOW_H
