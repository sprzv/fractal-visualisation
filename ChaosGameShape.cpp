#include <cmath>
#include <algorithm>
#include <random>
#include <iostream>
#include "ChaosGameShape.h"
#include "Exception.h"

ChaosGameShape::ChaosGameShape(unsigned int sides, std::vector<std::array<int, 2>> vertices) {

    //define vertices of original shape
    //checking for correct input
    if (sides > 0) {
        if (vertices.size() == sides) {
            for (unsigned int i = 0; i < vertices.size(); i++) {
                _vertices.push_back(vertices[i]);
            }
        }
        else {
            throw InvalidNumberVerticesException();
        }
    }
    else {
        throw InvalidNumberSidesException();
    }

}

ChaosGameShape::~ChaosGameShape() {}


//select random vertex coordinates each time
std::array<int,2> ChaosGameShape::getRandomVertex(std::vector<double> probabilities) {

    //generate a random probability from 0.01 to 1.00
    float randomProbability = (rand() % 100 + 1) / 100.0;

    float bottomOfRange = 0.01;

    //pile vertices according to their probabilities and choose the one whose probability range encloses the random probability generated
    for (unsigned int i = 0; i < probabilities.size(); i++) {
        if ((randomProbability >= bottomOfRange) && (randomProbability < (bottomOfRange + probabilities[i]))) {

            return _vertices[i];
        }
        bottomOfRange += probabilities[i];
    }
    throw -1;
}

//adds coordinates of a point to the set of points in the new shape
void ChaosGameShape::addVertex(std::array<int, 2> vertex) {
    _vertices.push_back(vertex);
}

//returns coords of point at a certain fraction of the distance from point1 to point2
std::array<int, 2> ChaosGameShape::pointAtFractionalDistance(std::array<int, 2> point1, std::array<int, 2> point2, double fraction) {
    int x1 = point1[0];
    int y1 = point1[1];
    int x2 = point2[0];
    int y2 = point2[1];
    std::array<int, 2> result;
    result[0] = (x1 + x2) * fraction;
    result[1] = (y1 + y2) * fraction;
    return result;
}

//returns all the coordinates of the different vertices found in the fractal after n iterations
//using different probabilities for selecting the vertices and a specified fractional distance at which to create new points between vertices
std::vector<std::array<int, 2> > ChaosGameShape::fractal(int n, std::vector<double> probabilityVertices, double distanceFraction) {

    //checking that probabilities for all vertices have been stated
    if (probabilityVertices.size() == _vertices.size()) {

        //checking that the sum of the probabilities = 1
        double sumProbabilities = 0;
        for (double var : probabilityVertices) {
            sumProbabilities += var;
        }

        if (sumProbabilities == 1.0) {

            //choose starting point for iteration
            std::array<int, 2> point1 = _vertices[0];

            for (int i = 0; i < n; i++) {
                std::array<int, 2> point2 = getRandomVertex(probabilityVertices);
                std::array<int, 2> newPoint = pointAtFractionalDistance(point1, point2, distanceFraction);

                //add new point coords as a new vertex and use it as starting point for the next iteration
                addVertex(newPoint);
                point1 = _vertices.back();
            }

            return _vertices;
        }

        else {
            throw InvalidSumProbabilitiesException();
        }
    }
    else {
        throw InvalidNumberVerticesException();
    }
}
