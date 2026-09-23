#ifndef OOD_L1_SHAPES_SHAPESTORAGE_H
#define OOD_L1_SHAPES_SHAPESTORAGE_H
#include "IShapeStorage.h"

namespace model {
    class ShapeStorage : public IShapeStorage
    {
    public:
        std::optional<std::shared_ptr<INotificationShape>> GetById(const std::string &id) override
        {
            auto it = GetIteratorById(id);
            if (it != shapes.end()) {
                return *it;
            }
            return std::nullopt;
        }

        void Store(std::shared_ptr<INotificationShape> shape) override
        {
            shapes.push_back(shape);
        }

        std::vector<std::shared_ptr<INotificationShape>> GetAll() override
        {
            return shapes;
        }

        void DeleteById(const std::string &id) override
        {
            auto it = GetIteratorById(id);
            if (it != shapes.end()) {
                auto ind = std::distance(shapes.begin(), it);
                shapes.erase(shapes.begin() + ind);
            }
        }
    private:
        std::vector<std::shared_ptr<INotificationShape>> shapes;

        std::__wrap_iter<std::shared_ptr<INotificationShape> *> GetIteratorById(const std::string &id)
        {
            return std::find_if(shapes.begin(), shapes.end(), [id](const auto& shape) {
                return shape->GetId() == id;
            });
        }
    };

}

#endif //OOD_L1_SHAPES_SHAPESTORAGE_H
