#include <iostream>
#include <TF1.h>

int main()
{
    
    // Gaussian 1 parameters
    double constant1 = 1.41771e+02;
    double mean1 = 4.29178e+02;
    double sigma1 = 1.36281e+01;

    // Gaussian 2 parameters
    double constant2 = 1.04254e+03;
    double mean2 = 4.57667e+02;
    double sigma2 = 7.76765e+00;

    // Gaussian 3 parameters
    double constant3 = 5.79581e+03;
    double mean3 = 4.79441e+02;
    double sigma3 = 5.13494e+00;
    

    /*
    // Gaussian 1 parameters
    double constant1 = 1.46865e+02;
    double mean1 = 4.27294e+02;
    double sigma1 = 1.10506e+01;

    // Gaussian 2 parameters
    double constant2 = 1.04464e+03;
    double mean2 = 4.56804e+02;
    double sigma2 = 6.52156e+00;

    // Gaussian 3 parameters
    double constant3 = 6.02019e+03;
    double mean3 = 4.79626e+02;
    double sigma3 = 5.03484e+00;
    */

    // Create TF1 objects for each Gaussian
    TF1 *gaussian1 = new TF1("gaussian1", "[0]*exp(-0.5*((x-[1])/[2])^2)", 0, 1023);
    gaussian1->SetParameters(constant1, mean1, sigma1);

    TF1 *gaussian2 = new TF1("gaussian2", "[0]*exp(-0.5*((x-[1])/[2])^2)", 0, 1023);
    gaussian2->SetParameters(constant2, mean2, sigma2);

    TF1 *gaussian3 = new TF1("gaussian3", "[0]*exp(-0.5*((x-[1])/[2])^2)", 0, 1023);
    gaussian3->SetParameters(constant3, mean3, sigma3);

    // Perform integration for each Gaussian
    double integral1 = gaussian1->Integral(0, 441);
    double integral2 = gaussian2->Integral(441, 467.8);
    double integral3 = gaussian3->Integral(467.8, 1023);
    
    double sumIntegral = integral1 + integral2 + integral3;

    // Print the integration results
    std::cout << "Integral of Gaussian 1: " << integral1 << std::endl;
    std::cout << "Integral of Gaussian 2: " << integral2 << std::endl;
    std::cout << "Integral of Gaussian 3: " << integral3 << std::endl;
    std::cout << "Total Integral: " << sumIntegral << std::endl;
    std::cout << "Probability of Gaussian 1: " << integral1/sumIntegral*100 << std::endl;
    std::cout << "Probability of Gaussian 2: " << integral2/sumIntegral*100 << std::endl;
    std::cout << "Probability of Gaussian 3: " << integral3/sumIntegral*100 << std::endl;

    // Clean up
    delete gaussian1;
    delete gaussian2;
    delete gaussian3;

    return 0;
}
