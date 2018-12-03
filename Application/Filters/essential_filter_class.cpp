#include "essential_filter_class.h"

void EssentialFilter::setParams(std::map<string, string> &keyValuePairs)
{
    contrast_alpha = atof(keyValuePairs.at("contrast_alpha").c_str());
    brightness_beta = atof(keyValuePairs.at("brightness_beta").c_str());
}

void EssentialFilter::writeParams(FileIOUtility& writer)
{
    writer.WriteKeyValue("filter", AbstractFilter::TypeAsString(AbstractFilter::Type::ESSENTIAL));
    writer.WriteKeyValue("contrast_alpha", util::doubleToString(contrast_alpha));
    writer.WriteKeyValue("brightness_beta", util::doubleToString(brightness_beta));
    writer.WriteKeyValue("filter","end");
}

Mat EssentialFilter::FilterCurrentFrame(Mat inputFrame)
{
    Mat outputFrame;
    inputFrame.convertTo(outputFrame, MATCH_INPUT_CHANNELS, contrast_alpha, brightness_beta);
    return outputFrame;
}
