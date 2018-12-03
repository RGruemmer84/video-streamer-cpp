#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <globals.h>
#include <Application/Lyne/lyne_class.h>
#include <Application/Cloud/cloud_controller_class.h>
#include <QObject>

#include <vector>
#include <string>

class Lyne;

class AppController : QObject
{
    Q_OBJECT
    string program_path;

    private:
        void Initialize();                                                  //Reads Data from DB and populates the lynes vector

    public:

        CloudController *cloud;
        std::vector<Lyne*> *lynes;                                                //ArrayList containing lyne objects
        Lyne* cur_lyne = NULL;
        std::shared_ptr<AbstractFilter> curFilterToTune = NULL;

        AppController();                                                    //Pointer to currently selected lyne
        ~AppController();

//        bool AddNewLyne();                                                  //Adds new lyne.  Creates DB field and AWS bucket
//        bool LoadExistingLyne();                                            //Loads existing lyne into lynes vector
//        bool RemoveLyne();                                                  //Removes lyne from DB and AWS
//        bool EditLyne();                                                    //Edits lyne info in DB
//        bool ExportLyne();                                                  //Assigns server ID to current lyne and removes from lynes vector

//        void PreviewLyne();                                                 //Previews output of currently selected lyne
//        void TuneLyne();                                                    //Tunes selected lyne

        static std::shared_ptr<AbstractFilter> CreateFilter(int type);
        void addNewFilter(int type);
        void saveCurFilterChain();

        std::vector<string> *GetLynesNameList();



};

#endif // APPCONTROLLER_H
