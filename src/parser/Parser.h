#ifndef OOD_L1_SHAPES_PARSER_H
#define OOD_L1_SHAPES_PARSER_H
#include <memory>
#include <sstream>

#include "../model/picture/Picture.h"

class Parser
{
public:
    Parser(std::unique_ptr<model::Picture> picture)
        : m_picture(std::move(picture))
    {
    }

    void ListenAndServe()
    {
        std::string userInput;
        while (std::getline(std::cin, userInput)) {
            if (userInput.empty()) {
                continue;
            }

            std::stringstream stream(userInput);

            std::string userCommand;
            stream >> userCommand;

            auto command = ParseCommand(userCommand);
            if (!command.has_value()) {
                std::cout << "unknown command" << std::endl;
                continue;
            }


        }
    }
private:
    std::unique_ptr<model::Picture> m_picture;

    enum class Command {
        AddShape,
        MoveShape,
        MovePicture,
        DeleteShape,
        List,
        ChangeColor,
        ChangeShape,
        DrawShape,
        DrawPicture
    };

    std::optional<Command> ParseCommand(std::string userInput)
    {
        std::transform(userInput.begin(), userInput.end(), userInput.begin(), [](unsigned char c) {
            return std::tolower(c);
        });

        if (userInput == "adddshape") {
            return Command::AddShape;
        }
        if (userInput == "moveshape") {
            return Command::MoveShape;
        }
        if (userInput == "movepicture") {
            return Command::MovePicture;
        }
        if (userInput == "deleteshape") {
            return Command::DeleteShape;
        }
        if (userInput == "list") {
            return Command::List;
        }
        if (userInput == "changecolor") {
            return Command::ChangeColor;
        }
        if (userInput == "changeshape") {
            return Command::ChangeShape;
        }
        if (userInput == "drawshape") {
            return Command::DrawShape;
        }
        if (userInput == "drawpicture") {
            return Command::DrawPicture;
        }
        return std::nullopt;
    }
};


#endif //OOD_L1_SHAPES_PARSER_H