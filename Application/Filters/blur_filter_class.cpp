#include "blur_filter_class.h"

void BlurFilter::setParams(std::map<string, string> &keyValuePairs)
{
    kernel = atoi(keyValuePairs.at("kernel").c_str());
}

void BlurFilter::writeParams(FileIOUtility& writer)
{
    writer.WriteKeyValue("filter", AbstractFilter::TypeAsString(AbstractFilter::Type::BLUR));
    writer.WriteKeyValue("kernel", std::to_string(kernel));
    writer.WriteKeyValue("filter","end");

}

Mat BlurFilter::FilterCurrentFrame(Mat inputFrame)
{
    Mat outputFrame;
    cv::blur(inputFrame, outputFrame, cv::Size(kernel,kernel));
    return outputFrame;
}
