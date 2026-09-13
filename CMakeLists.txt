cmake_minimum_required(VERSION 4.2)
project(OOD_L1_Shapes)

set(CMAKE_CXX_STANDARD 20)

add_executable(OOD_L1_Shapes main.cpp
        src/strategy/abstract/IShapeStrategy.h
        src/strategy/abstract/StrategyConstructFn.h
        src/strategy/abstract/StrategyStorage.h
        src/strategy/abstract/AutoRegisterStrategy.h
        src/strategy/abstract/AutoRegisterStrategy.h
        src/strategy/impl/Circle.cpp
        src/strategy/impl/Circle.h
        src/strategy/impl/Rectangle.cpp
        src/strategy/impl/Rectangle.h
        src/strategy/impl/Line.cpp
        src/strategy/impl/Line.h
        src/strategy/impl/Text.cpp
        src/strategy/impl/Text.h
        src/model/Shape.h
        src/model/picture/Picture.cpp
        src/model/picture/Picture.h
        src/model/shapeStorage/IShapeStorage.h
)
