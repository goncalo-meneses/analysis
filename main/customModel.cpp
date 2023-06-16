#include <iostream>
#include <fstream>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TApplication.h>
#include <TAxis.h>

void FitData()
{
    // Create a TApplication for the ROOT graphics
    TApplication app("app", nullptr, nullptr);

    // Read data from file
    std::ifstream file("/home/goncalo/LFEA/analysis/main/energies.txt");
    if (!file.is_open())
    {
        std::cout << "Failed to open data file." << std::endl;
        return;
    }

    // Arrays to store data
    std::vector<double> xValues;
    std::vector<double> yValues;
    std::vector<double> yErrors;

    double x, y, yErr;
    while (file >> x >> y >> yErr)
    {
        xValues.push_back(x);
        yValues.push_back(y);
        yErrors.push_back(yErr);
    }
    file.close();

    // Create a TGraphErrors from the data
    int numPoints = xValues.size();
    TGraphErrors *graph = new TGraphErrors(numPoints, &xValues[0], &yValues[0], nullptr, &yErrors[0]);

    graph->SetTitle("Rate VS Distance");
    graph->GetXaxis()->SetTitle("Distance [cm]");
    graph->GetYaxis()->SetTitle("Rate [counts/s]");
    
    graph->GetXaxis()->CenterTitle(true);
    graph->GetYaxis()->CenterTitle(true);

    // Create a canvas to display the graph
    TCanvas *canvas = new TCanvas("canvas", "Data Fitting", 800, 600);
    graph->Draw("AP"); // "AP" option to display both markers and error bars

    // Define a custom TF1 function
    TF1 *fitFunc = new TF1("fitFunc", "[0] / pow(x,2) + [1]");

    // Set initial parameter values and names
    fitFunc->SetParameters(1.0, 0.0);
    fitFunc->SetParNames("a", "b");

    // Fit the graph to the custom function
    graph->Fit(fitFunc, "R"); // "R" option for fit range using the graph's x-axis range

    // Wait for the Fit Panel to be closed
    app.Run();
}

int main()
{
    FitData();
    return 0;
}