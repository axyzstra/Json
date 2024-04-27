#include "Error.h"


namespace axyz {
    namespace json {
        void Error(std::string message) {
            throw std::logic_error(message);
        }
    };
};