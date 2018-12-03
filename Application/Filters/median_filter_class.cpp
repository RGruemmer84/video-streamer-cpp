#include "median_filter_class.h"

void MedianFilter::setParams(std::map<string, string> &keyValuePairs)
{
    kernel = atoi(keyValuePairs.at("kernel").c_str());
}

void MedianFilter::writeParams(FileIOUtility& writer)
{
    writer.WriteKeyValue("filter", AbstractFilter::TypeAsString(AbstractFilter::Type::MEDIAN_BLUR));
    writer.WriteKeyValue("kernel", std::to_string(kernel));
    writer.WriteKeyValue("filter","end");
}

Mat MedianFilter::FilterCurrentFrame(Mat inputFrame)
{
    Mat outputFrame;
    cv::medianBlur(inputFrame, outputFrame, kernel);
    return outputFrame;
}
