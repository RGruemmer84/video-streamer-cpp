#include "Application/Utility/utilities.h"
#include <sstream>

namespace util
{

    string doubleToString(double in)
    {
        std::ostringstream strs;
        strs << in;
        std::string str = strs.str();
        return str;
    }

}
