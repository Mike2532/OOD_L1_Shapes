#ifndef OOD_L1_SHAPES_IDRAWCANVAS_H
#define OOD_L1_SHAPES_IDRAWCANVAS_H

#include <string>

namespace gfx {
    class ICanvas {
    public:
        virtual ~ICanvas() = default;
        virtual void SetColor(const std::string& color) = 0;
        virtual void MoveTo(double x, double y) = 0;
        virtual void LineTo(double x, double y) = 0;
        virtual void DrawEllipse(double cx, double cy, float rx, double ry) = 0;
        virtual void DrawText(double left, double top, double fontSize, const std::string& text) = 0;
        virtual void Clear() = 0;
        virtual void Display() = 0;
        virtual void Close() = 0;
        virtual bool IsActive() = 0;
        virtual bool NeedToClose() = 0;
    };
}

#endif //OOD_L1_SHAPES_IDRAWCANVAS_H