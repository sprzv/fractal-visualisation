cmake_minimum_required(VERSION 3.10)
project(PH3170_Fractal_Visualisation_Project)

set(CMAKE_CXX_STANDARD 17)

set(EASY_BMP EasyBMP.h EasyBMP_BMP.h EasyBMP.cpp EasyBMP_DataStructures.h EasyBMP_VariousBMPutilities.h)
set(SOURCE_FILES main.cpp SierpinskiTriangle.cpp SierpinskiTriangle.h ChaosGameShape.cpp ChaosGameShape.h GeneralisedChaosGameShape.cpp GeneralisedChaosGameShape.h Exception.cpp Exception.h scalingFactor.h scalingFactor.cpp)

set(CMAKE_CXX_FLAGS "-pedantic -Wall")

add_executable(PH3170_Fractal_Visualisation_Project ${SOURCE_FILES} ${EASY_BMP})