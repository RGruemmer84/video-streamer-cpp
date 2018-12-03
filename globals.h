#ifndef GLOBAL_STRUCTS_H
#define GLOBAL_STRUCTS_H

#include <string>
#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

#include <QtGlobal>

using std::string;

static const bool COMPILE_FLAG_PI_BUILD = false;


typedef struct      //lyne_DB_entry_t
{
    string objectId;
    string s3_key;
    string s3_secret_key;
    string processId;
    string name;
    string type;
    string address;
    string phone;
    string hours[8];
    string region;
    double utcOffset;
    string special_1;
    string special_2;
    string special_3;
    string special_4;
    int numCameras;
    bool stream_active;
    string cam_url;
    string filter_entry_pointerID ;

} lyne_DB_entry_t;


typedef struct      //lyne_video_format_params_t
{
    int video_length_sec;
    int video_fps;
    double x_pixels;
    double y_pixels;
    bool is_gray_scale;
    bool is_inverted;

} lyne_video_format_params_t;




/*************** DEFAULTS *******************************/

static const lyne_DB_entry_t LYNE_ENTRY_HOGS_BREATH =
{
    "E8B885CC-44FF-59FE-FF7C-D6F7C4B26100",
    "AKIAIIWHGXQL62RJMNFA",
    "PjZPQg/nT2qRzS5rrfb4ud3gAuQOf3cbB8Cj+0nI",
    "svr_iEsMWw4X38",
    "Hog's Breath Saloon",
    "Restaurant",
    "400 Front St:Key West:FL:33040",
    "(305) 296-4222",
    {"12:00;01:30","12:00;01:31","12:00;01:32","12:00;01:33","12:00;03:34","12:00;03:35","12:00;01:36"},
    "Florida Keys",
    -8,
    "Hog Snort Cocktail $8",
    "Hogarita",
    "Key Lime Shooter",
    "Goombay Smash",
    1,
    true,
    "http://wse1.resortcams.com:80/live-audio/hogsbreath1.stream_aac/playlist.m3u8",
    "gt2cAoLfKZ"
};

static const lyne_DB_entry_t LYNE_ENTRY_SCHOONERS =
{
    "0D822CC4-C70E-D7EC-FF14-14A7DAC2A400",
    "AKIAIIWHGXQL62RJMNFA",
    "PjZPQg/nT2qRzS5rrfb4ud3gAuQOf3cbB8Cj+0nI",
    "svr_iEsMWw4X38",
    "Schooner's Warf",
    "Restaurant",
    "400 Front St:Key West:FL:33040",
    "(305) 296-4222",
    {"12:00;01:30","12:00;01:31","12:00;01:32","12:00;01:33","12:00;03:34","12:00;03:35","12:00;01:36"},
    "Florida Keys",
    -8,
    "Hog Snort Cocktail $8",
    "Hogarita",
    "Key Lime Shooter",
    "Goombay Smash",
    1,
    true,
    "rtmp://wowza.floridakeysmedia.com:8086/schoonerwharf/mp4:schoonerwharf.stream",
    "gt2cAoLfKZ"
};

static const lyne_DB_entry_t LYNE_ENTRY_SMOKIN_TUNA =
{
    "04D4C806-7433-0088-FFA5-D82FB4AABF00",
    "AKIAIIWHGXQL62RJMNFA",
    "PjZPQg/nT2qRzS5rrfb4ud3gAuQOf3cbB8Cj+0nI",
    "svr_iEsMWw4X38",
    "Smokin' Tuna",
    "Restaurant",
    "400 Front St:Key West:FL:33040",
    "(305) 296-4222",
    {"12:00;01:30","12:00;01:31","12:00;01:32","12:00;01:33","12:00;03:34","12:00;03:35","12:00;01:36"},
    "Florida Keys",
    -8,
    "Hog Snort Cocktail $8",
    "Hogarita",
    "Key Lime Shooter",
    "Goombay Smash",
    1,
    true,
    "rtmp://wowza.floridakeysmedia.com:8090/smokintunabar/mp4:smokintunabar.stream",
    "gt2cAoLfKZ"
};

static const lyne_DB_entry_t LYNE_ENTRY_IRISH_KEVINS =
{
    "4A11DAC4-FB11-24A3-FF88-B90FD1F62200",
    "AKIAIIWHGXQL62RJMNFA",
    "PjZPQg/nT2qRzS5rrfb4ud3gAuQOf3cbB8Cj+0nI",
    "svr_iEsMWw4X38",
    "Irish Kevin's",
    "Restaurant",
    "400 Front St:Key West:FL:33040",
    "(305) 296-4222",
    {"12:00;01:30","12:00;01:31","12:00;01:32","12:00;01:33","12:00;03:34","12:00;03:35","12:00;01:36"},
    "Florida Keys",
    -8,
    "Hog Snort Cocktail $8",
    "Hogarita",
    "Key Lime Shooter",
    "Goombay Smash",
    1,
    true,
    "rtmp://wowza.floridakeysmedia.com:8090/irishkevinsbar/mp4:irishkevinsbar.stream",
    "gt2cAoLfKZ"
};

static const lyne_DB_entry_t LYNE_ENTRY_SLOPPY_JOES =
{
    "F42AE529-F240-0BFA-FF26-659D144A8D00",
    "AKIAIIWHGXQL62RJMNFA",
    "PjZPQg/nT2qRzS5rrfb4ud3gAuQOf3cbB8Cj+0nI",
    "svr_iEsMWw4X38",
    "Sloppy Joes",
    "Restaurant",
    "400 Front St:Key West:FL:33040",
    "(305) 296-4222",
    {"12:00;01:30","12:00;01:31","12:00;01:32","12:00;01:33","12:00;03:34","12:00;03:35","12:00;01:36"},
    "Florida Keys",
    -8,
    "Hog Snort Cocktail $8",
    "Hogarita",
    "Key Lime Shooter",
    "Goombay Smash",
    1,
    true,
    "rtmp://wowza.floridakeysmedia.com:8090/sloppyjoesbar/mp4:sloppyjoesbar.stream",
    "gt2cAoLfKZ"
};


static const lyne_video_format_params_t STANDARD_VIDEO_FORMAT_PARAMS =
{
    30,                 //video_length_sec
    20,                 //video_fps
    384,                //x_pixels
    216,                 //y_pixels
    false,              //is_gray_scale
    false,              //is_inverted
};




#endif // GLOBAL_STRUCTS_H
