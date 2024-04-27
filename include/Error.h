#ifndef _ERROR_
#define _ERROR_

#include <string>
#include <stdexcept>


namespace axyz {
    namespace json {
        void Error(std::string message);
    };
};

#endif