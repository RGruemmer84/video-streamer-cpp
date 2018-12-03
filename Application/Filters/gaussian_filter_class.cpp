#include "gaussian_filter_class.h"

void GaussianFilter::setParams(std::map<string, string> &keyValuePairs)
{
    x_kernel = atoi(keyValuePairs.at("x_kernel").c_str());
    y_kernel = atoi(keyValuePairs.at("y_kernel").c_str());
}

void GaussianFilter::writeParams(FileIOUtility& writer)
{
    writer.WriteKeyValue("filter", AbstractFilter::TypeAsString(AbstractFilter::Type::GAUSS_BLUR));
    writer.WriteKeyValue("x_kernel", std::to_string(x_kernel));
    writer.WriteKeyValue("y_kernel", std::to_string(y_kernel));
    writer.WriteKeyValue("filter","end");
}

Mat GaussianFilter::FilterCurrentFrame(Mat inputFrame)
{
    Mat outputFrame;
    cv::GaussianBlur(inputFrame, outputFrame, cv::Size(x_kernel,y_kernel), SIGMA_X, SIGMA_Y);
    return outputFrame;
}
