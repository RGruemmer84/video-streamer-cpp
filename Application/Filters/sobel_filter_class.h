#ifndef SOBELFILTER_H
#define SOBELFILTER_H

#include "abstract_filter_class.h"
#include "Application/Utility/utilities.h"

using namespace util;

class SobelFilter : public AbstractFilter
{

    double scale;
    int ddepth;
    double delta;

    int grad_xx_order;
    int grad_xy_order;
    int grad_yx_order;
    int grad_yy_order;

    int x_kernel;
    int y_kernel;

    double x_gain;
    double y_gain;
    double dc_offset;
    double gamma;


    public:
        SobelFilter() : AbstractFilter()
        {
            filter_enabled = true;
            filter_type = Type::SOBEL;
            scale = 1;
            ddepth = CV_16S;
            delta = 0;
            grad_xx_order = 1;
            grad_xy_order = 0;
            grad_yx_order = 0;
            grad_yy_order = 1;
            x_kernel = 3;
            y_kernel = 3;
            x_gain = 0.5;
            y_gain = 0.5;
            dc_offset = 0;
            gamma = 0;
        }

        void setParams(std::map<string, string> &keyValuePairs);
        void writeParams(FileIOUtility& writer);

        void setKernel(int k)
        {
            if (k == 1 || k == 3 || k == 5 || k == 7)
            {
                x_kernel = k;
                y_kernel = k;
            }
        }
        int getKernel() {return x_kernel;}

        void setGamma(double g) {gamma = g;}
        double getGamma() {return gamma;}

        void setXWeight(double g) {x_gain = g;}
        void setYWeight(double g) {y_gain = g;}
        double getXWeight() {return x_gain;}
        double getYWeight() {return y_gain;}

        Mat FilterCurrentFrame(Mat inputFrame);
};

#endif // SOBELFILTER_H
