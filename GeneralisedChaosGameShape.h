#ifndef PH3170_FRACTAL_VISUALISATION_PROJECT_GENERALISEDCHAOSGAMESHAPE_H
#define PH3170_FRACTAL_VISUALISATION_PROJECT_GENERALISEDCHAOSGAMESHAPE_H

#include <array>
#include <vector>
#include <string>

class GeneralisedChaosGameShape {

public:
    GeneralisedChaosGameShape(std::string transformationsFile);
    ~GeneralisedChaosGameShape();
    std::vector<std::array<float, 2>> fractal(int n);

private:
    std::vector<std::array<float, 2>> _vertices;
    std::vector<float> _probabilities;
    std::vector<std::array<float, 6>> _contractionMappings;
    void addVertex(std::array<float, 2> vertex);
    std::array<float, 6> getRandomTransformation();
    std::array<float, 2> transformPoint(std::array<float, 2> startPoint, std::array<float, 6> transformation);

};


#endif //PH3170_FRACTAL_VISUALISATION_PROJECT_GENERALISEDCHAOSGAMESHAPE_H
