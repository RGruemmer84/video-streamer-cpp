#ifndef BILATERALFILTER_H
#define BILATERALFILTER_H

#include "abstract_filter_class.h"
#include "Application/Utility/utilities.h"

using namespace util;

class BilateralFilter : public AbstractFilter
{
    int diameter;
    double sigma_clr;
    double sigma_space;

    public:
        BilateralFilter() : AbstractFilter()
        {
            filter_enabled = true;
            filter_type = Type::BILATERAL_FILTER;
            diameter = 5;
            sigma_clr = 20;
            sigma_space = 20;
        }

        void setParams(std::map<string, string> &keyValuePairs);
        void writeParams(FileIOUtility& writer);

        void setDiameter(int d) {diameter = d;}
        void setSigmaClear(double s) {sigma_clr = s;}
        void setSigmaSpace(double s) {sigma_space = s;}

        int getDiameter() {return diameter;}
        double getSigmaClear() {return sigma_clr;}
        double getSigmaSpace() {return sigma_space;}

        Mat FilterCurrentFrame(Mat inputFrame);
};

#endif // BILATERALFILTER_H
