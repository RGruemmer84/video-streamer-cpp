#-------------------------------------------------
#
# Project created by QtCreator 2016-08-18T23:07:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(Application/Application.pri)
include(GUI/GUI.pri)

CONFIG += c++14

TARGET = Lynes_Manager
TEMPLATE = app

#INCLUDEPATH += /usr/local/include/opencv
#LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_videoio

#INCLUDEPATH += /usr/local/include/cpprest
#INCLUDEPATH += /usr/local/include/aws

#LIBS += -lboost_system -lcrypto -lssl -lcpprest
#LIBS += -laws-cpp-sdk-core -laws-cpp-sdk-s3

INCLUDEPATH += /usr/local/include/opencv2
INCLUDEPATH += /usr/local/include/opencv

LIBS += -L/usr/local/lib
LIBS += -lopencv_shape -lopencv_stitching -lopencv_objdetect -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_ml -lopencv_imgproc -lopencv_flann -lopencv_core




SOURCES += main.cpp
HEADERS += globals.h

