#ifndef LAPLACIANFILTER_H
#define LAPLACIANFILTER_H

#include "abstract_filter_class.h"
#include "Application/Utility/utilities.h"

using namespace util;

class LaplacianFilter : public AbstractFilter
{
    int kernel;
    double scale;
    double ddepth;
    double delta;

    public:
        LaplacianFilter() : AbstractFilter()
        {
            filter_enabled = true;
            filter_type = Type::LAPLACIAN;
            kernel = 3;
            scale = 1;
            ddepth = CV_8U;
            delta = 0;
        }

        void setParams(std::map<string, string> &keyValuePairs);
        void writeParams(FileIOUtility& writer);

        void setKernel(int k)
        {
            if (k % 2 != 1 || k > 31) return;
            kernel = k;
        }

        int getKernel() {return kernel;}

        void setScale(double s) {scale = s;}
        double getScale() {return scale;}

        Mat FilterCurrentFrame(Mat inputFrame);
};

#endif // LAPLACIANFILTER_H
