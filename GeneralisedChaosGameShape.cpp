#include <cmath>
#include <algorithm>
#include <list>
#include <random>
#include <iostream>
#include <fstream>
#include <sstream>
#include "GeneralisedChaosGameShape.h"
#include "Exception.h"

GeneralisedChaosGameShape::GeneralisedChaosGameShape(std::string transformationsFile) {

    //set pre-defined starting point at top left corner
    std::array<float, 2> startPoint= {0.0, 0.0};
    _vertices.push_back(startPoint);

    //add transformations and probabilities in file to temporary arrays to check validity
    std::array<float, 6> transformation = {};
    float probability = 0.0;

    std::string line;
    std::ifstream myFile(transformationsFile);
    if (myFile.is_open()) {
        while (std::getline(myFile, line)) {

            std::stringstream linestream(line);
            float numberData;
            int n = 1; //index for transformation in file
            for(int i = 0; linestream >> numberData; i++) {

                //filling in values of the temporary array for transformation found with corresponding probability
                if ((i < 6) && (i >= 0)) {
                    transformation[i] = numberData;
                    if (i == 5) {
                        //checking validity of transformation as contraction mapping once all transformation values for corresponding transformation have been read
                        float a11 = transformation[0];
                        float a12 = transformation[1];
                        float a21 = transformation[2];
                        float a22 = transformation[3];
                        double detA = (a11 * a22) - (a12 * a21);

                        if (((pow(a11, 2) + pow(a21, 2)) < 1)
                            && ((pow(a12, 2) + pow(a22, 2)) < 1)
                            && ((pow(a11, 2) + pow(a12, 2) + pow(a21, 2) + pow(a22, 2) - pow(detA, 2)) < 1)) {

                            _contractionMappings.push_back(transformation);
                        }
                        else {
                            throw InvalidContractionMappingException(n);
                        }

                    }
                }
                else if (i == 6) {
                    probability = numberData;
                    _probabilities.push_back(probability);
                    //reset count for element indexing and start reading new transformation in file
                    i = 0;
                    n++;
                }
                else {
                    throw -1;
                }
            }
        }
        myFile.close();
    }
    else {
        throw InvalidFileException();
    }

}

GeneralisedChaosGameShape::~GeneralisedChaosGameShape() {}


//select random transformations
std::array<float, 6> GeneralisedChaosGameShape::getRandomTransformation() {

    //generate a random probability from 0.01 to 1.00
    float randomProbability = (rand() % 100 + 1) / 100.0;

    float bottomOfRange = 0.01;

    //pile transformations according to their probabilities and choose the one whose probability range encloses the random probability generated
    for (unsigned int i = 0; i < _probabilities.size(); i++) {
        if ((randomProbability >= bottomOfRange) && (randomProbability < (bottomOfRange + _probabilities[i]))) {

            return _contractionMappings[i];
        }
        bottomOfRange += _probabilities[i];
    }
    throw -1;
}

//adds coordinates of a point to the set of points in the new shape
void GeneralisedChaosGameShape::addVertex(std::array<float, 2> vertex) {
    _vertices.push_back(vertex);
}

//returns coords of starting point after undergoing the transformation
std::array<float, 2> GeneralisedChaosGameShape::transformPoint(std::array<float, 2> startPoint, std::array<float, 6> transformation) {
    float a11 = transformation[0];
    float a12 = transformation[1];
    float a21 = transformation[2];
    float a22 = transformation[3];
    float b1 = transformation[4];
    float b2 = transformation[5];

    float x = startPoint[0];
    float y = startPoint[1];

    std::array<float, 2> result;
    result[0] = (a11 * x) + (a12 * y) + b1;
    result[1] = (a21 * x) + (a22 * y) + b2;

    return result;
}

//returns all the coordinates of the different points found in the fractal after n iterations
std::vector<std::array<float, 2> > GeneralisedChaosGameShape::fractal(int n) {

    //checking that probabilities for all transformations have been stated
    if (_probabilities.size() == _contractionMappings.size()) {

        //checking that the sum of the probabilities = 100
        float sumProbabilities = 0.0;
        for (float var : _probabilities) {
            sumProbabilities += var;
        }

        if (sumProbabilities == 1.0) {
            //choose starting point for iteration
            std::array<float, 2> point1 = _vertices[0];

            for (int i = 0; i < n; i++) {
                std::array<float, 6> transformation = getRandomTransformation();

                std::array<float, 2> newPoint = transformPoint(point1, transformation);

                //add new point coords as a new vertex and use it as starting point for the next iteration
                addVertex(newPoint);
                point1 = newPoint;
            }

            return _vertices;
        }

        else {
            throw InvalidSumProbabilitiesException();
        }
    }
    else {

        throw InvalidNumberProbabilitiesException();
    }
}


