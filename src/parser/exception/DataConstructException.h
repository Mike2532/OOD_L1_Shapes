#ifndef OOD_L1_SHAPES_DATACONSTRUCTEXCEPTION_H
#define OOD_L1_SHAPES_DATACONSTRUCTEXCEPTION_H
#include <stdexcept>

namespace parser {
    class DataConstructException : public std::invalid_argument
    {
    public:
        explicit DataConstructException(const std::string& message)
            : std::invalid_argument(message)
        {
        }
    };
}

#endif //OOD_L1_SHAPES_DATACONSTRUCTEXCEPTION_H