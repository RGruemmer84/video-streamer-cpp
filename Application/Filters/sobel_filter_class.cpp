#include "sobel_filter_class.h"
#include <sstream>

void SobelFilter::setParams(std::map<string, string> &keyValuePairs)
{
    scale = atof(keyValuePairs.at("scale").c_str());
    ddepth = atoi(keyValuePairs.at("ddepth").c_str());
    delta = atof(keyValuePairs.at("delta").c_str());

    grad_xx_order = atoi(keyValuePairs.at("grad_xx_order").c_str());
    grad_xy_order = atoi(keyValuePairs.at("grad_xy_order").c_str());
    grad_yx_order = atoi(keyValuePairs.at("grad_yx_order").c_str());
    grad_yy_order = atoi(keyValuePairs.at("grad_yy_order").c_str());

    x_kernel = atoi(keyValuePairs.at("x_kernel").c_str());
    y_kernel = atoi(keyValuePairs.at("y_kernel").c_str());

    x_gain = atof(keyValuePairs.at("x_gain").c_str());
    y_gain = atof(keyValuePairs.at("y_gain").c_str());
    dc_offset = atof(keyValuePairs.at("dc_offset").c_str());
    gamma = atof(keyValuePairs.at("gamma").c_str());
}

void SobelFilter::writeParams(FileIOUtility& writer)
{
    writer.WriteKeyValue("filter", AbstractFilter::TypeAsString(AbstractFilter::Type::SOBEL));

    writer.WriteKeyValue("scale", util::doubleToString(scale));
    writer.WriteKeyValue("ddepth", std::to_string(ddepth));
    writer.WriteKeyValue("delta", doubleToString(delta));

    writer.WriteKeyValue("grad_xx_order", std::to_string(grad_xx_order));
    writer.WriteKeyValue("grad_xy_order", std::to_string(grad_xy_order));
    writer.WriteKeyValue("grad_yx_order", std::to_string(grad_yx_order));
    writer.WriteKeyValue("grad_yy_order", std::to_string(grad_yy_order));

    writer.WriteKeyValue("x_kernel", std::to_string(x_kernel));
    writer.WriteKeyValue("y_kernel", std::to_string(y_kernel));

    writer.WriteKeyValue("x_gain",      util::doubleToString(x_gain));
    writer.WriteKeyValue("y_gain",      util::doubleToString(y_gain));
    writer.WriteKeyValue("dc_offset",   util::doubleToString(dc_offset));
    writer.WriteKeyValue("gamma",       util::doubleToString(gamma));

    writer.WriteKeyValue("filter","end");

}

Mat SobelFilter::FilterCurrentFrame(Mat inputFrame)
{
    Mat outputFrame;
    Mat sobel_grad_x_mat;
    Mat sobel_grad_y_mat;
    Mat sobel_grad_x_abs_mat;
    Mat sobel_grad_y_abs_mat;

    cv::Sobel(inputFrame,sobel_grad_x_mat,ddepth,grad_xx_order,grad_xy_order,x_kernel,1,delta,cv::BORDER_DEFAULT);
    cv::convertScaleAbs(sobel_grad_x_mat, sobel_grad_x_abs_mat);

    cv::Sobel(inputFrame,sobel_grad_y_mat,ddepth,grad_yx_order,grad_yy_order,y_kernel,1,delta,cv::BORDER_DEFAULT);
    cv::convertScaleAbs(sobel_grad_y_mat, sobel_grad_y_abs_mat);

    cv::addWeighted(sobel_grad_x_abs_mat,x_gain,sobel_grad_y_abs_mat,y_gain,gamma,outputFrame);

    return outputFrame;
}
