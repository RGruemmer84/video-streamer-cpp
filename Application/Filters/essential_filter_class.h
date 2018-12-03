#ifndef ESSENTIALFILTER_H
#define ESSENTIALFILTER_H

#include "abstract_filter_class.h"
#include "Application/Utility/utilities.h"

using namespace util;


class EssentialFilter : public AbstractFilter
{
    #define MATCH_INPUT_CHANNELS -1

    double contrast_alpha;
    double brightness_beta;

    public:
        EssentialFilter() : AbstractFilter()
        {
            filter_enabled = true;
            filter_type = Type::ESSENTIAL;
            contrast_alpha = 1;
            brightness_beta = 0;
        }

        void setParams(std::map<string, string> &keyValuePairs);
        void writeParams(FileIOUtility& writer);

        void setBrightness(double b) {brightness_beta = b;}
        double getBrightness() {return brightness_beta;}

        void setContrast(double c) {contrast_alpha = c;}
        double getContrast() {return contrast_alpha;}

        Mat FilterCurrentFrame(Mat inputFrame);
};

#endif // ESSENTIALFILTER_H
