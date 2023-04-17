#include <algorithm>
#include <ctime>
#include <random>
#include <vector>
#include "EasyBMP.h"
#include "SierpinskiTriangle.h"
#include "ChaosGameShape.h"
#include "GeneralisedChaosGameShape.h"
#include "Exception.h"
#include "scalingFactor.h"

int main(){

    //Create a 2D array with MxN pixels on the heap
    int M = 1920; //our max x coordinate
    int N = 1200; //our max y coordinate
    double **data = new double *[M];

    for (int i = 0; i < M; ++i) {

        data[i] = new double[N];
    }


    bool continueProgram = true;
    int option1 = 0;
    int option2 = 0;

    //defining input variables before while loop with preferred defaults
    std::vector<std::array<int, 2>> vertices;
    std::array<int, 2> zeroes = {0, 0};
    int sides = 3;
    std::vector<double> probabilities;
    int nIterations = 100000;
    std::string transformationsFile;

    //continue iterating program unless user selects to exit
    while (continueProgram != false) {

        //Initialise pixel array to zero (i.e. empty image) - clear out image before drawing each time
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                 data[i][j] = 0;
            }
        }

        //sets random number generators to generate new values each time an option runs
        srand(time(NULL));

        std::cin.clear();

        //clears previous option value
        option1 = 0;
        option2 = 0;

        //user menu display
        std::cout << "***************************************" << std::endl;
        std::cout << "Fractal Visualisation Program" << std::endl;
        std::cout << "***************************************" << std::endl;
        std::cout << "Create fractal image from:" << std::endl;
        std::cout << "1 - Set of vertices for a triangle" << std::endl;
        std::cout << "2 - Set of vertices for a 2D polygon" << std::endl;
        std::cout << "3 - Set of contraction mappings" << std::endl;
        std::cout << std::endl;
        std::cout << "0 - Exit program" << std::endl;
        std::cout << "***************************************" << std::endl;
        std::cout << "Enter option:" << std::endl;
        std::cin >> option1;


        switch (option1) {
            case 1:
                //asking for input parameters
                std::cout << "***************************************" << std::endl;
                std::cout << "Sierpinski Triangle Visualisation" << std::endl;
                std::cout << "***************************************" << std::endl;

                for (int i = 0; i < 3; i++) {
                    vertices.push_back(zeroes);
                }

                for (int i = 0; i < 3; i++) {
                    std::cout << "Enter coordinates for vertex " << i + 1 << " separated by a space:" << std::endl;
                    std::cin >> vertices[i][0] >> vertices[i][1];
                    if (std::cin.fail()) {
                        do {
                            std::cout << "Invalid vertex" << std::endl;
                            std::cout << "Enter coordinates for vertex " << i + 1 << " separated by a space:" << std::endl;
                            std::cin >> vertices[i][0] >> vertices[i][1];
                        } while (std::cin.fail());
                    }
                }

                std::cout << "Enter number of iterations:" << std::endl;
                std::cin >> nIterations;

                try {
                    //generating coordinates for new shape and colouring in the pixels that match
                    SierpinskiTriangle triangle(vertices[0], vertices[1], vertices[2]);
                    std::vector<std::array<int, 2> > fractal = triangle.fractal(nIterations);
                    for (auto coord : fractal) {
                        data[coord[0]][coord[1]] = 1;
                    }
                }
                catch (Exception &exception){
                    std::cout << "Exception caught: " << std::endl;
                    exception.handleException();
                }

                break;

            case 2:
                //asking for input parameters
                std::cout << "***************************************" << std::endl;
                std::cout << "Chaos Game Visualisation" << std::endl;
                std::cout << "***************************************" << std::endl;

                std::cout << "Enter number of sides in shape:" << std::endl;
                std::cin >> sides;

                for (int i = 0; i < sides; i++) {
                    vertices.push_back(zeroes);
                }

                for (int i = 0; i < sides; i++) {
                    probabilities.push_back(0.0);
                }

                for (int i = 0; i < sides; i++) {
                    std::cout << "Enter coordinates for vertex " << i + 1 << " separated by a space:" << std::endl;
                    std::cin >> vertices[i][0] >> vertices[i][1];
                    if (std::cin.fail()) {
                        do {
                            //quick input checking
                            std::cin.clear();
                            std::cout << "Invalid vertex" << std::endl;
                            std::cout << "Enter coordinates for vertex " << i + 1 << " separated by a space:" << std::endl;
                            std::cin >> vertices[i][0] >> vertices[i][1];
                        } while (std::cin.fail());
                    }

                    std::cout << "Enter probability of selecting vertex as a decimal number:" << std::endl;
                    std::cin >> probabilities[i];
                }

                std::cout << "Enter distance fraction from one vertex to another at which a new point will be created:" << std::endl;
                double distanceFraction;
                std::cin >> distanceFraction;

                std::cout << "Enter number of iterations:" << std::endl;
                std::cin >> nIterations;

                try {
                    //generating coordinates for new shape and colouring in the pixels that match
                    ChaosGameShape shape(sides, vertices);
                    std::vector<std::array<int, 2> > fractal = shape.fractal(nIterations, probabilities, distanceFraction);
                    for (auto coord : fractal) {
                        data[coord[0]][coord[1]] = 1;
                    }
                }
                //catching exceptions in input
                catch (Exception &exception){
                    std::cout << "Exception caught: " << std::endl;
                    exception.handleException();
                }

                break;

            case 3:
                //submenu for generalised chaos game
                std::cout << "***************************************" << std::endl;
                std::cout << "Generalised Chaos Game Visualisation" << std::endl;
                std::cout << "***************************************" << std::endl;
                std::cout << "1 - Use contraction mappings for Barnsley's Fern" << std::endl;
                std::cout << "2 - Use own contraction mappings" << std::endl;
                std::cout << std::endl;
                std::cout << "0 - Go to main menu" << std::endl;
                std::cout << "***************************************" << std::endl;
                std::cout << "Enter option:" << std::endl;
                std::cin >> option2;

                switch (option2) {
                    case 1:
                        try {
                            //find coordinates of new shape
                            GeneralisedChaosGameShape barnsleyFern("transformationsfile.txt");
                            std::vector<std::array<float, 2>> fractal = barnsleyFern.fractal(1000000);

                            //scale shape to fit the image size
                            double scalingFactorX = scalingFactor(fractal, M, N)[0];
                            double scalingFactorY = scalingFactor(fractal, M, N)[1];
                            double minX = scalingFactor(fractal, M, N)[2];
                            double minY = scalingFactor(fractal, M, N)[3];

                            for (auto coord : fractal) {
                                int coordX = (int) ((coord[0] - minX) * scalingFactorX);
                                int coordY = (int) ((coord[1] - minY) * scalingFactorY);
                                data[coordX][coordY] = 1;

                            }
                        }

                        catch (Exception &exception) {
                        std::cout << "Exception caught: " << std::endl;
                        exception.handleException();
                        }

                        break;

                    case 2:
                        std::cout << "Enter name of file with contraction mappings and corresponding probabilities:" << std::endl;
                        std::cin >> transformationsFile;

                        try {
                            GeneralisedChaosGameShape barnsleyFern(transformationsFile);
                            std::vector<std::array<float, 2>> fractal = barnsleyFern.fractal(1000000);

                            //scale shape to fit the image size
                            double scalingFactorX = scalingFactor(fractal, M, N)[0];
                            double scalingFactorY = scalingFactor(fractal, M, N)[1];
                            double minX = scalingFactor(fractal, M, N)[2];
                            double minY = scalingFactor(fractal, M, N)[3];

                            for (auto coord : fractal) {
                                int coordX = (int) ((coord[0] - minX) * scalingFactorX);
                                int coordY = (int) ((coord[1] - minY) * scalingFactorY);
                                data[coordX][coordY] = 1;

                            }
                        }

                        //catch invalid input
                        catch (Exception &exception) {
                            std::cout << "Exception caught: " << std::endl;
                            exception.handleException();
                        }
                        break;

                    //go to main menu
                    case 0:
                        break;

                    //incorrect option restarts the program
                    default:
                        std::cout << "Invalid option. Choose again." << std::endl;
                        break;
                }


                break;

            //exit program
            case 0:
                continueProgram = false;
                break;

            //incorrect option restarts the program
            default:
                std::cout << "Invalid option. Choose again." << std::endl;
                break;
        }

        //Loops over all elements to work out which pixel has largest number (and therefore
        //darkest colour. The entire image is then re-normalised based on the difference between
        //the lightest and darkest pixels to ensure the best contrast
        double min = 9e9;
        double max = -9e9;
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (data[i][j] < min) {
                    min = data[i][j];
                }
                if (data[i][j] > max) {
                    max = data[i][j];
                }
            }
        }

        //only output image if options selected are valid
        if ((continueProgram != false) && (option1 < 4) && (option1 > 0) && (option2 >= 0) && (option2 < 3)) {

            //Create output bmp container
            BMP Output;
            Output.SetSize(M, N);
            Output.SetBitDepth(32);

            //go to main menu without displaying image
            if ((option1 == 3) && (option2 == 0)) {
                continue;
            }

            else if ((option1 == 3) && (option2 == 1)){
                std::cout << "Detected Cell Minimum: " << min << std::endl;
                std::cout << "Detected Cell Maximum: " << max << std::endl;
                //Create output bmp container
                BMP Output;
                Output.SetSize(M, N);
                Output.SetBitDepth(32);

                // plot the pixels green for Barnsley's fern
                for (int i = 0; i < M; i++) {
                    for (int j = 0; j < N; j++) {
                        double scaled_value = 1 - (data[i][j] - min) / (max - min + 1e-16);
                        ebmpBYTE pixel_value = (ebmpBYTE) (scaled_value * 255.0);
                        Output(i, j)->Red = pixel_value;   //
                        Output(i, j)->Blue = pixel_value;  //
                    }
                }

                //Save output (change filename as necessary for your code!)
                Output.WriteToFile("image.bmp");
            }

            else {
                std::cout << "Detected Cell Minimum: " << min << std::endl;
                std::cout << "Detected Cell Maximum: " << max << std::endl;

                //Create output bmp container
                BMP Output;
                Output.SetSize(M, N);
                Output.SetBitDepth(32);

                // plot the pixels in black
                for (int i = 0; i < M; i++) {
                    for (int j = 0; j < N; j++) {
                        double scaled_value = 1 - (data[i][j] - min) / (max - min + 1e-16);
                        ebmpBYTE pixel_value = (ebmpBYTE) (scaled_value * 255.0);
                        Output(i, j)->Red = pixel_value;
                        Output(i, j)->Green = pixel_value;
                        Output(i, j)->Blue = pixel_value;
                    }
                }

                //Save output
                Output.WriteToFile("image.bmp");
            }
        }
    }
    //Cleanup!

    //Remove data array from heap
    for (int i = 0; i < M; ++i) {

        delete[] data[i];
    }

    //Remove array container
    delete[] data;
}