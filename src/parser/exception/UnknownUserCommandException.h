#ifndef OOD_L1_SHAPES_UNKNOWNUSERCOMMANDEXCEPTION_H
#define OOD_L1_SHAPES_UNKNOWNUSERCOMMANDEXCEPTION_H

namespace parser {
    class UnknownUserCommandException : public std::invalid_argument
    {
    public:
        explicit UnknownUserCommandException()
            : std::invalid_argument("unknown user command")
        {
        }
    };
}

#endif //OOD_L1_SHAPES_UNKNOWNUSERCOMMANDEXCEPTION_H