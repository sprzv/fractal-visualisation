#include <algorithm>
#include "scalingFactor.h"

std::array<double, 4> scalingFactor(std::vector<std::array<float, 2>> coordSet, int maxWidth, int maxLength) {
    //find maximum length and width of shape for scaling
    std::vector<float> coordsX;
    std::vector<float> coordsY;

    for (unsigned int i = 0; i < coordSet.size(); i++) {
        coordsX.push_back(coordSet[i][0]);
        coordsY.push_back(coordSet[i][1]);
    }

    //find maximum and minimum x and y values in coordinates
    std::vector<float>::iterator xMaxIt;
    xMaxIt = std::max_element(coordsX.begin(), coordsX.end());
    std::vector<float>::iterator xMinIt;
    xMinIt = std::min_element(coordsX.begin(), coordsX.end());

    float maxX = *xMaxIt;
    float minX = *xMinIt;

    std::vector<float>::iterator yMaxIt;
    yMaxIt = std::max_element(coordsY.begin(), coordsY.end());
    std::vector<float>::iterator yMinIt;
    yMinIt = std::min_element(coordsY.begin(), coordsY.end());

    float maxY = *yMaxIt;
    float minY = *yMinIt;

    //scale shape to fit the image size
    double scalingFactorX = (maxWidth - 1) / (maxX - minX);
    double scalingFactorY = (maxLength - 1) / (maxY - minY);

    std::array<double, 4> scalingFactor = {scalingFactorX, scalingFactorY, minX, minY};

    return scalingFactor;
}

