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
    std::ifstream file("/home/goncalo/LFEA/analysis/main/bi3.txt");
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

    graph->SetTitle("Ajuste ao Espetro do ^{207}Bi");
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
    TF1 *gaussian1 = new TF1("gaussian1", "[0]*TMath::Gaus(x, [1], [2])", 0, 300);
    TF1 *gaussian2 = new TF1("gaussian2", "[0]*TMath::Gaus(x, [1], [2])", 0, 300);
    TF1 *gaussian3 = new TF1("gaussian3", "[0]*TMath::Gaus(x, [1], [2])", 0, 300);
    TF1 *gaussian4 = new TF1("gaussian4", "[0]*TMath::Gaus(x, [1], [2])", 0, 300);

    gaussian1->SetParameters(933.38, 102.77, 1.27);
    gaussian2->SetParameters(245.95, 118.81, 2.92);
    gaussian3->SetParameters(288.34, 208.50, 0.87);
    gaussian4->SetParameters(38.44, 224.23, 1.05);

    gaussian1->SetLineColor(kRed);
    gaussian2->SetLineColor(kAzure-6);
    gaussian3->SetLineColor(kSpring-8);
    gaussian4->SetLineColor(kOrange-2);

    gaussian1->Draw("same");
    gaussian2->Draw("same");
    gaussian3->Draw("same");
    gaussian4->Draw("same");

    // Create a legend and add entries for the data, individual Gaussians, and the sum
    TLegend *legend = new TLegend(0.7,0.7,0.9,0.9);
    legend->AddEntry(graph, "Dados", "lep");
    legend->AddEntry(gaussian1, "Pico 3", "l");
    legend->AddEntry(gaussian2, "Pico 4", "l");
    legend->AddEntry(gaussian3, "Pico 5", "l");
    legend->AddEntry(gaussian4, "Pico 6", "l");
    legend->Draw();

    // Save the plot as a PDF file
    canvas->SaveAs("plot.pdf");
}


int main()
{
    PlotGaussiansWithData();
    return 0;
}
