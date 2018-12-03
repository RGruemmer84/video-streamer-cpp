#include "bilateral_filter_class.h"

void BilateralFilter::setParams(std::map<string, string> &keyValuePairs)
{
    diameter = atoi(keyValuePairs.at("diameter").c_str());
    sigma_clr = atof(keyValuePairs.at("sigma_clr").c_str());
    sigma_space = atof(keyValuePairs.at("sigma_space").c_str());
}

void BilateralFilter::writeParams(FileIOUtility& writer)
{
    writer.WriteKeyValue("filter", AbstractFilter::TypeAsString(AbstractFilter::Type::BILATERAL_FILTER));
    writer.WriteKeyValue("diameter", std::to_string(diameter));
    writer.WriteKeyValue("sigma_clr",  util::doubleToString(sigma_clr));
    writer.WriteKeyValue("sigma_space", util::doubleToString(sigma_space));
    writer.WriteKeyValue("filter", "end");


}

Mat BilateralFilter::FilterCurrentFrame(Mat inputFrame)
{
    Mat outputFrame;
    cv::bilateralFilter(inputFrame, outputFrame, diameter, sigma_clr, sigma_space, cv::BORDER_DEFAULT);
    return outputFrame;
}
