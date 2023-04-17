#include <cmath>
#include <algorithm>
#include <random>
#include <iostream>
#include "SierpinskiTriangle.h"

SierpinskiTriangle::SierpinskiTriangle(std::array<int, 2> vertex1, std::array<int, 2> vertex2, std::array<int, 2> vertex3) {

    //define vertices of original shape
    _vertices.push_back(vertex1);
    _vertices.push_back(vertex2);
    _vertices.push_back(vertex3);
}

SierpinskiTriangle::~SierpinskiTriangle() {};

//generate random vertex from triangle with equal probabilities
std::array<int,2> SierpinskiTriangle::getRandomVertex() {
    int index = std::rand() % 3;
    return _vertices[index];
}

//add a vertex to the list of points in the shape
void SierpinskiTriangle::addVertex(std::array<int, 2> vertex) {
    _vertices.push_back(vertex);
}

//returns coords of point at half the distance from point1 to point2
std::array<int, 2> SierpinskiTriangle::pointAtHalfDistance(std::array<int, 2> point1, std::array<int, 2> point2) {
    int x1 = point1[0];
    int y1 = point1[1];
    int x2 = point2[0];
    int y2 = point2[1];
    std::array<int, 2> result;
    result[0] = (x1 + x2) / 2;
    result[1] = (y1 + y2) / 2;
    return result;
}

//returns all the coordinates of the different points found in the triangle fractal after n iterations
std::vector<std::array<int, 2> > SierpinskiTriangle::fractal(int n) {
    //choose starting point for iteration
    std::array<int, 2> point1 = _vertices[0];

    for (int i = 0; i < n; i++) {
        std::array<int, 2> point2 = getRandomVertex(); //does this give a new vertex on each iteration of for loop??
        std::array<int, 2> newPoint = pointAtHalfDistance(point1, getRandomVertex());

        //add new point coords as a new vertex and use it as starting point for the next iteration
        addVertex(newPoint);
        point1 = _vertices.back();
    }

    return _vertices;
}