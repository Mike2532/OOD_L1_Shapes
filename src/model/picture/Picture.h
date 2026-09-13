#ifndef OOD_L1_SHAPES_PICTURE_H
#define OOD_L1_SHAPES_PICTURE_H

#include <string>
#include <vector>

class Picture
{
public:
    void AddShape(const std::string& id, const std::string& shapeType, const std::vector<std::string>& args);
    void MoveShape(const std::string& id, double dx, double dy);
    void DeleteShape(const std::string& id);
    void ChangeColor(const std::string& id, const std::string& color);
    void ChangeShape(const std::string& id, const std::string& shapeType, const std::vector<std::string>& args);
    void DrawShape(const std::string& id);
    void List();
    void MovePicture(double dx, double dy);
    void DrawPicture();
private:

};


#endif //OOD_L1_SHAPES_PICTURE_H
