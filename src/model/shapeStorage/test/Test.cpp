#include <catch2/catch_test_macros.hpp>

#include "../ShapeStorage.h"

TEST_CASE("init empty storage")
{
    auto shapeStorage = model::ShapeStorage();

    auto shapes = shapeStorage.GetAll();
    REQUIRE(shapes.size() == 0);
}

TEST_CASE("Create, Read, Delete, Read")
{
    auto shapeStorage = model::ShapeStorage();

    std::string shapeId = "shapeId";
    std::string shapeColor = "#ffffff";
    auto shape = std::make_shared<model::Shape>(
        shapeId,
        shapeColor,
        nullptr
    );

    shapeStorage.Store(shape);
    auto shapes = shapeStorage.GetAll();
    REQUIRE(shapes.size() == 1);

    auto foundedShape = shapeStorage.GetById(shapeId);
    REQUIRE(foundedShape == shape);

    shapeStorage.DeleteById(shapeId);
    shapes = shapeStorage.GetAll();
    REQUIRE(shapes.size() == 0);
}

TEST_CASE("get unknown shape")
{
    auto shapeStorage = model::ShapeStorage();

    std::string shapeId = "shapeId";
    auto foundedShape = shapeStorage.GetById(shapeId);
    REQUIRE(!foundedShape.has_value());
}

TEST_CASE("delete unknown shape")
{
    auto shapeStorage = model::ShapeStorage();

    std::string shapeId = "shapeId";
    shapeStorage.DeleteById(shapeId);
}