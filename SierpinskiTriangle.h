#ifndef PH3170_FRACTAL_VISUALISATION_PROJECT_SIERPINSKITRIANGLE_H
#define PH3170_FRACTAL_VISUALISATION_PROJECT_SIERPINSKITRIANGLE_H

#include <array>
#include <vector>

class SierpinskiTriangle {

public:
    SierpinskiTriangle(std::array<int, 2> vertex1, std::array<int, 2> vertex2, std::array<int, 2> vertex3);
    ~SierpinskiTriangle();
    std::vector<std::array<int, 2> > fractal(int n);

private:
    std::vector<std::array<int, 2> > _vertices;
    void addVertex(std::array<int, 2> vertex);
    std::array<int,2> getRandomVertex();
    std::array<int, 2> pointAtHalfDistance(std::array<int, 2> point1, std::array<int, 2> point2);
};


#endif //PH3170_FRACTAL_VISUALISATION_PROJECT_SIERPINSKITRIANGLE_H
