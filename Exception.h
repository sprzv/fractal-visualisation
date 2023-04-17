
#ifndef PH3170_FRACTAL_VISUALISATION_PROJECT_EXCEPTION_H
#define PH3170_FRACTAL_VISUALISATION_PROJECT_EXCEPTION_H


class Exception {

public:
    Exception();
    ~Exception();
    virtual void handleException() = 0;
};


class InvalidContractionMappingException: public Exception{

public:
    InvalidContractionMappingException(int n);
    ~InvalidContractionMappingException();
    void handleException();

private:
    int _n;
};

class InvalidSumProbabilitiesException: public Exception {

public:
    InvalidSumProbabilitiesException();
    ~InvalidSumProbabilitiesException();
    void handleException();

};

class InvalidNumberProbabilitiesException: public Exception{

public:
    InvalidNumberProbabilitiesException();
    ~InvalidNumberProbabilitiesException();
    void handleException();
};

class InvalidVerticesException: public Exception{

public:
    InvalidVerticesException();
    ~InvalidVerticesException();
    void handleException();
};

class InvalidNumberVerticesException: public Exception{

public:
    InvalidNumberVerticesException();
    ~InvalidNumberVerticesException();
    void handleException();
};

class InvalidNumberSidesException: public Exception{

public:
    InvalidNumberSidesException();
    ~InvalidNumberSidesException();
    void handleException();
};

class InvalidFileException: public Exception{

public:
    InvalidFileException();
    ~InvalidFileException();
    void handleException();
};

#endif //PH3170_FRACTAL_VISUALISATION_PROJECT_EXCEPTION_H
