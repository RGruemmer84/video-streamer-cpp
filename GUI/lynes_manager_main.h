#ifndef LYNES_MANAGER_MAIN_H
#define LYNES_MANAGER_MAIN_H

#include <QMainWindow>
#include <QListView>
#include <QStringList>
#include <QAbstractItemModel>
#include <QStringListModel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QStyle>
#include <QDesktopWidget>

#include "globals.h"

#include <Application/Controller/app_controller_class.h>
#include <GUI/filter_chain_editor_window.h>
#include <GUI/lynes_manager_tuner_window.h>
#include <GUI/lynes_manager_edit_lyne_window.h>


namespace Ui {
class LynesManagerMain;
}

class LynesManagerMain : public QMainWindow
{
    Q_OBJECT

    public:

        AppController* ctrl;
        FilterChainEditorWindow* chain_editor;
        Tuner_Window* tuner_window;
        EditLyneWindow *edit_window;



        explicit LynesManagerMain(QWidget *parent = 0);
        ~LynesManagerMain();

    private:
        Ui::LynesManagerMain *ui;

    private:
        void InitializeGui();


    private slots:
        void on_addLyneButton_clicked();

        void on_LoadExistingLyneButton_clicked();

        void on_editLyneButton_clicked();

        void on_removeLyne_clicked();

        void on_exportLineButton_clicked();

        void on_tuneLyneButton_clicked();

        void on_previewLyneButton_clicked();



};

#endif // LYNES_MANAGER_MAIN_WINDOW_H
