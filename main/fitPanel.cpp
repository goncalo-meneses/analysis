#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
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
    std::ifstream file("/home/goncalo/LFEA/analysis/main/csG.txt");
    if (!file.is_open())
    {
        std::cout << "Failed to open data file." << std::endl;
        return;
    }

    // Arrays to store data
    std::vector<double> xValues;
    std::vector<double> yValues;
    std::vector<double> yErrors;

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        double x, y, err;
        if (iss >> x >> y >> err)
        {
            xValues.push_back(x);
            yValues.push_back(y);
            yErrors.push_back(err);
        }
    }

    file.close();

    // Create a TGraphErrors from the data
    int numPoints = xValues.size();
    TGraphErrors *graph = new TGraphErrors(numPoints, &xValues[0], &yValues[0], 0, &yErrors[0]);

    graph->SetTitle("Calibration in Energy");
    graph->GetXaxis()->SetTitle("Energy [keV]");
    graph->GetYaxis()->SetTitle("Channel");

    graph->GetXaxis()->CenterTitle(true);
    graph->GetYaxis()->CenterTitle(true);

    // Create a canvas to display the graph
    TCanvas *canvas = new TCanvas("canvas", "Data Fitting", 800, 600);
    graph->Draw("AP"); // "AP" option to display both markers and error bars

    // Launch the ROOT Fit Panel
    canvas->Update(); // Update the canvas to display the graph
    canvas->cd();
    graph->FitPanel();

    // Wait for the Fit Panel to be closed
    app.Run();
}

int main()
{
    FitData();
    return 0;
}
