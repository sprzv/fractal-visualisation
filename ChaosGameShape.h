
#ifndef PH3170_FRACTAL_VISUALISATION_PROJECT_CHAOSGAMESHAPE_H
#define PH3170_FRACTAL_VISUALISATION_PROJECT_CHAOSGAMESHAPE_H

#include <array>
#include <vector>

class ChaosGameShape {

public:
    ChaosGameShape(unsigned int sides, std::vector<std::array<int, 2> > vertices);
    ~ChaosGameShape();
    std::vector<std::array<int, 2> > fractal(int n, std::vector<double> probabilityVertices, double distanceFraction);

private:
    std::vector<std::array<int, 2> > _vertices;
    void addVertex(std::array<int, 2> vertex);
    std::array<int,2> getRandomVertex(std::vector<double> probabilities);
    std::array<int, 2> pointAtFractionalDistance(std::array<int, 2> point1, std::array<int, 2> point2, double fraction);

};

#endif //PH3170_FRACTAL_VISUALISATION_PROJECT_CHAOSGAMESHAPE_H
