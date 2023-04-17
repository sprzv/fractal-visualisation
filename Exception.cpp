#include <iostream>
#include "Exception.h"

//constructor and destructor for Exception class
Exception::Exception() {}

Exception::~Exception() {}

InvalidContractionMappingException::InvalidContractionMappingException(int n) : _n(n) {}
InvalidContractionMappingException::~InvalidContractionMappingException() {}
InvalidSumProbabilitiesException::InvalidSumProbabilitiesException() {}
InvalidSumProbabilitiesException::~InvalidSumProbabilitiesException() {}
InvalidNumberProbabilitiesException::InvalidNumberProbabilitiesException() {}
InvalidNumberProbabilitiesException::~InvalidNumberProbabilitiesException() {}
InvalidVerticesException::InvalidVerticesException() {}
InvalidVerticesException::~InvalidVerticesException() {}
InvalidNumberVerticesException::InvalidNumberVerticesException() {}
InvalidNumberVerticesException::~InvalidNumberVerticesException() {}
InvalidNumberSidesException::InvalidNumberSidesException() {}
InvalidNumberSidesException::~InvalidNumberSidesException() {}
InvalidFileException::InvalidFileException() {}
InvalidFileException::~InvalidFileException() {}

void InvalidContractionMappingException::handleException() {
    std::cout << "Invalid contraction mapping for N = " << _n << std::endl;
}

void InvalidSumProbabilitiesException::handleException() {
    std::cout << "Probabilities do not add up to 1" << std::endl;
}

void InvalidNumberProbabilitiesException::handleException() {
    std::cout << "Invalid number of probabilities to select each transformation" << std::endl;
}

void InvalidVerticesException::handleException() {
    std::cout << "Invalid vertex" << std::endl;
}

void InvalidNumberVerticesException::handleException() {
    std::cout << "Invalid number of vertices" << std::endl;
}

void InvalidNumberSidesException::handleException() {
    std::cout << "Invalid number of sides" << std::endl;
}

void InvalidFileException::handleException() {
    std::cout << "Unable to open file" << std::endl;
}


