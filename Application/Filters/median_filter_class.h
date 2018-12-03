#ifndef MEDIANFILTER_H
#define MEDIANFILTER_H

#include "abstract_filter_class.h"

class MedianFilter : public AbstractFilter
{
    int kernel;

    public:
        MedianFilter() : AbstractFilter()
        {
            filter_enabled = true;
            filter_type = Type::MEDIAN_BLUR;
            kernel = 5;
        }

        void setParams(std::map<string, string> &keyValuePairs);
        void writeParams(FileIOUtility& writer);

        void setKernel(int k) {kernel = k;}
        int getKernel() {return kernel;}

        Mat FilterCurrentFrame(Mat inputFrame);
};

#endif // MEDIANFILTER_H
