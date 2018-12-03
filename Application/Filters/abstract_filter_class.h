#ifndef ABSTRACTFILTER_H
#define ABSTRACTFILTER_H

//#include "globals.h"
#include "Application/Utility/file_io_utility_class.h"

#include <opencv/cv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

#include <map>
#include <iostream>
#include <memory>


using namespace cv;
using std::string;


class AbstractFilter
{
    public:

        /*              TYPE ENUM         */

        static const int NUM_FILTER_TYPES = 8;
        enum class Type : char
        {
            NONE                    = 0,
            BLUR                    = 1,
            GAUSS_BLUR              = 2,
            MEDIAN_BLUR             = 3,
            BILATERAL_FILTER        = 4,
            SOBEL                   = 5,
            LAPLACIAN               = 6,
            MORPH                   = 7,
            ESSENTIAL               = 8
        };

        /*              ENUM FUNCTIONS      */

        static auto TypeAsString(AbstractFilter::Type e)
        {
            const std::map<AbstractFilter::Type, const char*> EnumStrings
            {
                {AbstractFilter::Type::NONE,                "NONE" },
                {AbstractFilter::Type::BLUR,                "BLUR" },
                {AbstractFilter::Type::GAUSS_BLUR,          "GAUSS_BLUR" },
                {AbstractFilter::Type::MEDIAN_BLUR,         "MEDIAN_BLUR" },
                {AbstractFilter::Type::BILATERAL_FILTER,    "BILATERAL_FILTER" },
                {AbstractFilter::Type::SOBEL,               "SOBEL" },
                {AbstractFilter::Type::LAPLACIAN,           "LAPLACIAN" },
                {AbstractFilter::Type::MORPH,               "MORPH" },
                {AbstractFilter::Type::ESSENTIAL,           "ESSENTIAL" }
            };
            auto it = EnumStrings.find(e);
            return it == EnumStrings.end() ? "Out of range" : it->second;
        }

        static auto TypeAsString(int e)
        {
            const std::map<int, const char*> EnumStrings
            {
                {0,         "NONE" },
                {1,         "BLUR" },
                {2,         "GAUSS_BLUR" },
                {3,         "MEDIAN_BLUR" },
                {4,         "BILATERAL_FILTER"},
                {5,         "SOBEL" },
                {6,         "LAPLACIAN" },
                {7,         "MORPH" },
                {8,         "ESSENTIAL" }
            };
            auto it = EnumStrings.find(e);
            return it == EnumStrings.end() ? "Out of range" : it->second;
        }

        static int TypeFromString(string e)
        {
            const std::map<string, int> EnumStrings
            {
                {"NONE",                0},
                {"BLUR",                1},
                {"GAUSS_BLUR",          2},
                {"MEDIAN_BLUR",         3},
                {"BILATERAL_FILTER",    4},
                {"SOBEL",               5},
                {"LAPLACIAN",           6},
                {"MORPH",               7},
                {"ESSENTIAL",           8}
            };
            auto it = EnumStrings.find(e);
            return it == EnumStrings.end() ? 0 : it->second;
        }




        /*      Class Data Members      */

        bool                filter_enabled;
        Type                filter_type;



        /*       Constructor and initialze  */

        AbstractFilter() {filter_enabled = false; filter_type = Type::NONE;}


        /*          Filtering Functions     */

        virtual Mat FilterCurrentFrame(cv::Mat inputFrame) =0;

        /*         IO Serialization          */

        virtual void setParams(std::map<string, string> &keyValuePairs) =0;
        virtual void writeParams(FileIOUtility& writer) =0;

};

#endif // ABSTRACTFILTER_H
