#include "Parser.h"

namespace parser {
    void Parser::ListenAndServe()
    {
        std::cout << "welcome to shapes cli" << std::endl;
        std::cout << "> " << std::flush;

        std::string userInput;
        while (std::getline(std::cin, userInput)) {
            try {
                if (userInput.empty()) {
                    continue;
                }

                std::stringstream stream(userInput);

                std::string userCommand;
                stream >> userCommand;

                ExecuteUserCommand(userCommand, stream);
            } catch (const std::exception& e) {
                std::cout << e.what() << std::endl << std::flush;
            }

            std::cout << "> " << std::flush;;
        }
    }

    void parser::Parser::ExecuteUserCommand(std::string userCommand, std::stringstream &input)
    {
        std::transform(userCommand.begin(), userCommand.end(), userCommand.begin(), [](unsigned char c) {
            return std::tolower(c);
        });

        if (userCommand == ADD_SHAPE_COMMAND) {
            const auto data = m_dataConstructor.ConstructAddShapeData(input);
            m_picture->AddShape(data);
            return;
        }
        if (userCommand == MOVE_SHAPE_COMMAND) {
            const auto data = m_dataConstructor.ConstructMoveShapeData(input);
            m_picture->MoveShape(data);
            return;
        }
        if (userCommand == MOVE_PICTURE_COMMAND) {
            auto data = m_dataConstructor.ConstructMovePictureData(input);
            m_picture->MovePicture(data);
            return;
        }
        if (userCommand == DELETE_SHAPE_COMMAND) {
            auto data = m_dataConstructor.ConstructDeleteShapeData(input);
            m_picture->DeleteShape(data);
            return;
        }
        if (userCommand == LIST_COMMAND) {
            m_picture->List();
            return;
        }
        if (userCommand == CHANGE_COLOR_COMMAND) {
            auto data = m_dataConstructor.ConstructChangeColorData(input);
            m_picture->ChangeColor(data);
            return;
        }
        if (userCommand == CHANGE_SHAPE_COMMAND) {
            auto data = m_dataConstructor.ConstructChangeShapeData(input);
            m_picture->ChangeShape(data);
            return;
        }
        if (userCommand == DRAW_SHAPE_COMMAND) {
            auto data = m_dataConstructor.ConstructDrawShapeData(input);
            m_picture->DrawShape(data);
            return;
        }
        if (userCommand == DRAW_PICTURE_COMMAND) {
            m_picture->DrawPicture();
            return;
        }

        throw UnknownUserCommandException();
    }
}

