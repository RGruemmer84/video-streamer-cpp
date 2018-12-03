#ifndef BLURFILTER_H
#define BLURFILTER_H

#include "abstract_filter_class.h"


class BlurFilter : public AbstractFilter
{
    int kernel;

    public:
        BlurFilter() : AbstractFilter()
        {
            filter_enabled = true;
            filter_type = Type::BLUR;
            kernel = 2;
        }

        void setParams(std::map<string, string> &keyValuePairs);
        void writeParams(FileIOUtility& writer);

        void setKernel(int k) {kernel = k;}
        int getKernel() {return kernel;}

        Mat FilterCurrentFrame(Mat inputFrame);
};

#endif // BLURFILTER_H
