#include "morph_filter_class.h"


void MorphFilter::setParams(std::map<string, string> &keyValuePairs)
{
    type = atoi(keyValuePairs.at("type").c_str());
    element = atoi(keyValuePairs.at("element").c_str());
    size = atoi(keyValuePairs.at("size").c_str());
    iterations = atoi(keyValuePairs.at("iterations").c_str());
    operation = atoi(keyValuePairs.at("operation").c_str());
}

void MorphFilter::writeParams(FileIOUtility& writer)
{
    writer.WriteKeyValue("filter", AbstractFilter::TypeAsString(AbstractFilter::Type::MORPH));
    writer.WriteKeyValue("type", std::to_string(type));
    writer.WriteKeyValue("element", std::to_string(element));
    writer.WriteKeyValue("size", std::to_string(size));
    writer.WriteKeyValue("iterations", std::to_string(iterations));
    writer.WriteKeyValue("operation", std::to_string(operation));
    writer.WriteKeyValue("filter","end");

}

Mat MorphFilter::FilterCurrentFrame(Mat inputFrame)
{
    return inputFrame;
    //TODO:  switch off type and do appropriate morph filter
//    Mat outputFrame;

//    return outputFrame;
}
