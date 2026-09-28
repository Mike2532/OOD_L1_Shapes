#ifndef OOD_L1_SHAPES_PARSER_H
#define OOD_L1_SHAPES_PARSER_H
#include <memory>
#include <sstream>

#include "../model/picture/Picture.h"
#include "dataConsturctor/DataConstructor.h"
#include "exception/UnknownUserCommandException.h"

namespace parser {
    class Parser
    {
        static constexpr auto ADD_SHAPE_COMMAND = "addshape";
        static constexpr auto MOVE_SHAPE_COMMAND = "moveshape";
        static constexpr auto MOVE_PICTURE_COMMAND = "movepicture";
        static constexpr auto DELETE_SHAPE_COMMAND = "deleteshape";
        static constexpr auto LIST_COMMAND = "list";
        static constexpr auto CHANGE_COLOR_COMMAND = "changecolor";
        static constexpr auto CHANGE_SHAPE_COMMAND = "changeshape";
        static constexpr auto DRAW_SHAPE_COMMAND = "drawshape";
        static constexpr auto DRAW_PICTURE_COMMAND = "drawpicture";

    public:
        Parser(std::shared_ptr<model::Picture> picture)
            : m_picture(std::move(picture))
        {
        }

        void ListenAndServe();
    private:
        std::shared_ptr<model::Picture> m_picture;
        DataConstructor m_dataConstructor = DataConstructor();

        void ExecuteUserCommand(std::string userCommand, std::stringstream& input);
    };
}

#endif //OOD_L1_SHAPES_PARSER_H