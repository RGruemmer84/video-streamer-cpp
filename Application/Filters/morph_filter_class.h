#ifndef MORPHFILTER_H
#define MORPHFILTER_H

#include "abstract_filter_class.h"

class MorphFilter : public AbstractFilter
{

public:
    int type;       //0 = Dilation, 1 = Erosion, 2 = morphologyEx
    int element;
    int size;
    int iterations;
    int operation;

    MorphFilter() : AbstractFilter()
    {
        filter_enabled = true;
        filter_type = Type::MORPH;
        type = 0;
        element = 0;
        size = 1;
        iterations = 1;
        operation = 2;
    }


    void setParams(std::map<string, string> &keyValuePairs);
    void writeParams(FileIOUtility& writer);

    Mat FilterCurrentFrame(Mat inputFrame);

    void setType(int t){
        if (t >= 0 && t <= 2)
            type = t;
    }

    int getType() {return type;}

    void setElement(int e){
        if (e >= 0 && e <= 2)
            element = e;
    }

    int getElement() {return element;}

    void setSize(int s){
        if (s >= 1 && s <= 50)
            size = s;
    }

    int getSize() {return size;}

    void setIterations(int i){
        if (i >= 1 && i <= 50)
            iterations = i;
    }

    int getIterations() {return iterations;}

    void setOperation(int o){
        if (o >= 2 && o <= 6)
            operation = o;
    }

    int getOperation() {return operation;}
};

#endif // MORPHFILTER_H
