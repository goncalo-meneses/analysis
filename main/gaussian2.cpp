#include <iostream>
#include <fstream>
#include <vector>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TF1.h>
#include <TAxis.h>

void PlotGaussiansWithData()
{
    // Read data from file
    std::ifstream file("/home/goncalo/LFEA/analysis/main/cs.txt");
    if (!file.is_open())
    {
        std::cout << "Failed to open data file." << std::endl;
        return;
    }

    // Arrays to store data
    std::vector<double> xValues;
    std::vector<double> yValues;
    std::vector<double> yErrors;

    double x, y, error;
    while (file >> x >> y >> error)
    {
        xValues.push_back(x);
        yValues.push_back(y);
        yErrors.push_back(error);
    }

    file.close();

    // Create a TGraphErrors from the data
    int numPoints = xValues.size();
    TGraphErrors *graph = new TGraphErrors(numPoints, &xValues[0], &yValues[0], 0, &yErrors[0]);

    graph->SetTitle("Ajuste ao Espetro do ^{137}Cs");
    graph->GetXaxis()->SetTitle("Canal");
    graph->GetYaxis()->SetTitle("Contagens");

    graph->GetXaxis()->CenterTitle(true);
    graph->GetYaxis()->CenterTitle(true);

    // Create a canvas to display the plot
    TCanvas *canvas = new TCanvas("canvas", "Gaussians with Data", 800, 600);

    // Draw the data points
    graph->SetMarkerStyle(20);
    graph->SetMarkerSize(0.7);
    graph->Draw("AP");

    // Create and draw the three Gaussian functions
    TF1 *gaussian1 = new TF1("gaussian1", "[0]*TMath::Gaus(x, [1], [2])", 0, 170);
    TF1 *gaussian2 = new TF1("gaussian2", "[0]*TMath::Gaus(x, [1], [2])", 0, 170);

    // Césio 237
    gaussian1->SetParameters(1.63229e+03, 1.15777e+02, 3.44590e+00);
    gaussian2->SetParameters(2.38294e+02, 1.25212e+02, 1.88109e+00);

    gaussian1->SetLineColor(kRed);
    gaussian2->SetLineColor(kAzure-6);

    gaussian1->Draw("same");
    gaussian2->Draw("same");

    // Create and draw the sum of the Gaussians
    TF1 *gaussianSum = new TF1("gaussianSum", "[0]*TMath::Gaus(x, [1], [2]) + [3]*TMath::Gaus(x, [4], [5])", 0, 170);

    gaussianSum->SetParameters(1.63229e+03, 1.15777e+02, 3.44590e+00, 2.38294e+02, 1.25212e+02, 1.88109e+00);

    gaussianSum->SetLineColor(kSpring-8);

    gaussianSum->Draw("same");

    // Create a legend and add entries for the data, individual Gaussians, and the sum
    TLegend *legend = new TLegend(0.7,0.7,0.9,0.9);
    legend->AddEntry(graph, "Dados", "lep");
    legend->AddEntry(gaussian1, "Pico de conversao", "l");
    legend->AddEntry(gaussian2, "Pico", "l");
    legend->AddEntry(gaussianSum, "Soma dos picos", "l");
    legend->Draw();

    // Save the plot as a PDF file
    canvas->SaveAs("plot.pdf");
}


int main()
{
    PlotGaussiansWithData();
    return 0;
}
