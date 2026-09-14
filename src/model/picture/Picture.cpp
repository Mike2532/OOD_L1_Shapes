#include "Picture.h"

#include "../../strategy/abstract/StrategyStorage.h"
#include "../Shape.h"
#include "../shapeStorage/IShapeStorage.h"

namespace model {
    void Picture::AddShape(
        const std::string& id,
        std::string color,
        const std::string& shapeType,
        const std::vector<std::string>& args
    ) {
        RequireShapeDoesNotExist(id);

        std::transform(color.begin(), color.end(), color.begin(), [](unsigned char c) {
            return std::tolower(c);
        });

        auto strategy = GetExistingStrategy(shapeType, args);
        const auto shape = std::make_shared<Shape>(id, color, std::move(strategy));
        m_shapeStorage->Store(shape);
    }

    void Picture::MoveShape(const std::string &id, double dx, double dy)
    {
        auto shape = GetExistingShape(id);
        shape->Move(dx, dy);
    }

    void Picture::DeleteShape(const std::string &id)
    {
        m_shapeStorage->DeleteById(id);
    }

    void Picture::ChangeColor(const std::string &id, const std::string &color)
    {
        auto shape = GetExistingShape(id);
        shape->SetColor(color);
    }

    void Picture::ChangeShape(
        const std::string &id,
        const std::string &shapeType,
        const std::vector<std::string> &args
    ) {
        auto strategy = GetExistingStrategy(shapeType, args);
        const auto shape = GetExistingShape(id);
        shape->SetStrategy(std::move(strategy));
    }

    void Picture::DrawShape(const std::string &id)
    {
        auto shape = GetExistingShape(id);
        ShowShapes({shape});
    }

    void Picture::List(std::ostream& output)
    {
        auto shapes = m_shapeStorage->GetAll();
        const auto shapesSize = shapes.size();

        std::string result;
        for (auto shapeInd = 0; shapeInd < shapesSize; shapeInd++)
        {
            auto shape = shapes[shapeInd];
            result += std::to_string(shapeInd + 1) + ' ';
            result += shape->GetStrategyName() + ' ';
            result += shape->GetId() + ' ';
            result += shape->GetColor() + ' ';
            result += shape->GetArgsAsString();
            result += '\n';
        }
        output << result;
    }

    void Picture::MovePicture(double dx, double dy)
    {
        auto shapes = m_shapeStorage->GetAll();
        for (const auto& shape : shapes) {
            shape->Move(dx, dy);
        }
    }

    void Picture::DrawPicture()
    {
        auto shapes = m_shapeStorage->GetAll();
        ShowShapes(shapes);
    }

    std::shared_ptr<Shape> Picture::GetExistingShape(const std::string &id)
    {
        auto shape = m_shapeStorage->GetById(id);
        if (shape.has_value()) {
            return shape.value();
        }
        throw std::runtime_error("can not get shape with id " + id);
    }

    std::unique_ptr<strategy::IShapeStrategy> Picture::GetExistingStrategy(
        const std::string &shapeType,
        const std::vector<std::string> &args
    ) {
        auto strategy = m_strategyStorage->Construct(shapeType, args);
        if (strategy.has_value()) {
            return std::move(strategy.value());
        }
        throw std::runtime_error("unknown strategy");
    }

    void Picture::RequireShapeDoesNotExist(const std::string &id)
    {
        auto shape = m_shapeStorage->GetById(id);
        if (shape.has_value()) {
            throw std::runtime_error("shape with id " + id + " already exists");
        }
    }

    void Picture::ShowShapes(const std::vector<std::shared_ptr<Shape>> &shapes) {
        while (m_canvas->IsActive()) {
            if (m_canvas->NeedToClose()) {
                m_canvas->Close();
            }

            m_canvas->Clear();

            for (const auto& shape : shapes) {
                shape->Draw(m_canvas);
            }

            m_canvas->Display();
        }
    }
}
