#include "Application/Controller/app_controller_class.h"
#include <stdio.h>
#include <unistd.h>
#include <iostream>

AppController::AppController()
{

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
       fprintf(stdout, "Current working dir: %s\n", cwd);
    else
       perror("getcwd() error");

    program_path = string(cwd);
    //system(("mkdir -p " + PROGRAM_PATH).c_str());
    Initialize();
}


void AppController::Initialize()
{
    //cloud = new CloudController();
    lynes = new std::vector<Lyne*>();



    Lyne *new_lyne = new Lyne(this);
    new_lyne->SetParamsAndInitialize(LYNE_ENTRY_HOGS_BREATH, STANDARD_VIDEO_FORMAT_PARAMS, program_path);
    lynes->push_back(new_lyne);

    new_lyne = new Lyne(this);
    new_lyne->SetParamsAndInitialize(LYNE_ENTRY_IRISH_KEVINS, STANDARD_VIDEO_FORMAT_PARAMS, program_path);
    lynes->push_back(new_lyne);

    new_lyne = new Lyne(this);
    new_lyne->SetParamsAndInitialize(LYNE_ENTRY_SCHOONERS, STANDARD_VIDEO_FORMAT_PARAMS, program_path);
    lynes->push_back(new_lyne);

    new_lyne = new Lyne(this);
    new_lyne->SetParamsAndInitialize(LYNE_ENTRY_SLOPPY_JOES, STANDARD_VIDEO_FORMAT_PARAMS, program_path);
    lynes->push_back(new_lyne);

    new_lyne = new Lyne(this);
    new_lyne->SetParamsAndInitialize(LYNE_ENTRY_SMOKIN_TUNA, STANDARD_VIDEO_FORMAT_PARAMS, program_path);
    lynes->push_back(new_lyne);
}

AppController::~AppController()
{
    delete lynes;
    delete cur_lyne;
}

void AppController::addNewFilter(int type)
{
    curFilterToTune = CreateFilter(type);
    //cur_lyne->engine->filterSet.push_back(curFilterToTune);
    cur_lyne->engine->filterSetBuffer.push_back(curFilterToTune);
}

std::shared_ptr<AbstractFilter> AppController::CreateFilter(int type)
{
    switch (static_cast<AbstractFilter::Type>(type))
    {
        case AbstractFilter::Type::BILATERAL_FILTER:
            return std::make_shared<BilateralFilter>();
        case AbstractFilter::Type::BLUR:
            return std::make_shared<BlurFilter>();
        case AbstractFilter::Type::MORPH:
            return std::make_shared<MorphFilter>();
        case AbstractFilter::Type::ESSENTIAL:
            return std::make_shared<EssentialFilter>();
        case AbstractFilter::Type::GAUSS_BLUR:
            return std::make_shared<GaussianFilter>();
        case AbstractFilter::Type::LAPLACIAN:
            return std::make_shared<LaplacianFilter>();
        case AbstractFilter::Type::MEDIAN_BLUR:
            return std::make_shared<MedianFilter>();
        case AbstractFilter::Type::SOBEL:
            return std::make_shared<SobelFilter>();
        case AbstractFilter::Type::NONE:
            return NULL;
        default:
            return NULL;
    }


}

void AppController::saveCurFilterChain()
{
    cur_lyne->engine->storeFilterChain();
}

std::vector<string>* AppController::GetLynesNameList()
{
    std::vector<string>* str_list = new std::vector<string>();
    for (auto *l : *lynes)
    {
        str_list->push_back(l->info_params.name);
    }
    return str_list;
}




//bool AppController::AddNewLyne()
//{

//    return false;
//}

//bool AppController::LoadExistingLyne()
//{

//    return false;
//}

//bool AppController::RemoveLyne()
//{

//    return false;
//}

//bool AppController::EditLyne()
//{

//    return false;
//}

//bool AppController::ExportLyne()
//{

//    return false;
//}


//void AppController::TuneLyne()
//{

//}

//void AppController::PreviewLyne()
//{


//}
