#include <iostream>
#include <TF1.h>
#include <TMath.h>

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
    double sigma3 = 3.69565e-02;

    // Create TF1 objects for each Gaussian
    TF1 *gaussian1 = new TF1("gaussian1", "[0]*exp(-0.5*((x-[1])/[2])^2)", 400, 550);
    gaussian1->SetParameters(constant1, mean1, sigma1);

    TF1 *gaussian2 = new TF1("gaussian2", "[0]*exp(-0.5*((x-[1])/[2])^2)", 400, 550);
    gaussian2->SetParameters(constant2, mean2, sigma2);

    TF1 *gaussian3 = new TF1("gaussian3", "[0]*exp(-0.5*((x-[1])/[2])^2)", 400, 550);
    gaussian3->SetParameters(constant3, mean3, sigma3);

    // Define integration range
    double xmin = 400;
    double xmax = 550;

    // Calculate integral and uncertainty for Gaussian 1
    double integral1 = gaussian1->Integral(xmin, xmax);
    double integralError1 = TMath::Sqrt(integral1);

    // Calculate integral and uncertainty for Gaussian 2
    double integral2 = gaussian2->Integral(xmin, xmax);
    double integralError2 = TMath::Sqrt(integral2);

    // Calculate integral and uncertainty for Gaussian 3
    double integral3 = gaussian3->Integral(xmin, xmax);
    double integralError3 = TMath::Sqrt(integral3);

    // Print the integration results
    std::cout << "Integral of Gaussian 1: " << integral1 << " +/- " << integralError1 << std::endl;
    std::cout << "Integral of Gaussian 2: " << integral2 << " +/- " << integralError2 << std::endl;
    std::cout << "Integral of Gaussian 3: " << integral3 << " +/- " << integralError3 << std::endl;

    // Clean up
    delete gaussian1;
    delete gaussian2;
    delete gaussian3;

    return 0;
}
