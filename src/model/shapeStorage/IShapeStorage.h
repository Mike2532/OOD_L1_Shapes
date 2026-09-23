#ifndef OOD_L1_SHAPES_ISHAPESTORAGE_H
#define OOD_L1_SHAPES_ISHAPESTORAGE_H

#include <optional>
#include <vector>
#include "../Shape.h"

namespace model {
    class IShapeStorage
    {
    public:
        virtual ~IShapeStorage() = default;

        virtual std::optional<std::shared_ptr<INotificationShape>> GetById(const std::string& id) = 0;
        virtual std::vector<std::shared_ptr<INotificationShape>> GetAll() = 0;
        virtual void Store(std::shared_ptr<INotificationShape> shape) = 0;
        virtual void DeleteById(const std::string& id) = 0;
    };
}

#endif //OOD_L1_SHAPES_ISHAPESTORAGE_H
