#ifndef GAUSSIANFILTER_H
#define GAUSSIANFILTER_H

#include "abstract_filter_class.h"

class GaussianFilter : public AbstractFilter
{
    #define SIGMA_X 0
    #define SIGMA_Y 0

    int x_kernel;
    int y_kernel;

    public:
        GaussianFilter() : AbstractFilter()
        {
            filter_enabled = true;
            filter_type = Type::GAUSS_BLUR;
            x_kernel = 3;
            y_kernel = 3;
        }

        void setParams(std::map<string, string> &keyValuePairs);
        void writeParams(FileIOUtility& writer);

        void setXKernel(int k) {x_kernel = k;}
        int getXKernel() {return x_kernel;}

        void setYKernel(int k) {y_kernel = k;}
        int getYKernel() {return y_kernel;}

        Mat FilterCurrentFrame(Mat inputFrame);
};

#endif // GAUSSIANFILTER_H
