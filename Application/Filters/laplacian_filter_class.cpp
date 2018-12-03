#include "laplacian_filter_class.h"

void LaplacianFilter::setParams(std::map<string, string> &keyValuePairs)
{
    kernel = atoi(keyValuePairs.at("kernel").c_str());
    scale = atof(keyValuePairs.at("scale").c_str());
    ddepth = atof(keyValuePairs.at("ddepth").c_str());
    delta = atof(keyValuePairs.at("delta").c_str());

}

void LaplacianFilter::writeParams(FileIOUtility& writer)
{
    writer.WriteKeyValue("filter", AbstractFilter::TypeAsString(AbstractFilter::Type::LAPLACIAN));
    writer.WriteKeyValue("kernel", std::to_string(kernel));
    writer.WriteKeyValue("scale", util::doubleToString(scale));
    writer.WriteKeyValue("ddepth", util::doubleToString(ddepth));
    writer.WriteKeyValue("delta", util::doubleToString(delta));
    writer.WriteKeyValue("filter","end");
}

Mat LaplacianFilter::FilterCurrentFrame(Mat inputFrame)
{
    Mat outputFrame;
    cv::Laplacian(inputFrame, outputFrame, ddepth, kernel, scale, delta, cv::BORDER_DEFAULT);
    return outputFrame;
}
