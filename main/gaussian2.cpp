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
    std::ifstream file("/home/goncalo/LFEA/analysis/main/co.txt");
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

    graph->SetTitle("Ajuste ao Espetro do ^{60}Co");
    graph->GetXaxis()->SetTitle("Canal");
    graph->GetYaxis()->SetTitle("Contagens");

    graph->GetXaxis()->CenterTitle(true);
    graph->GetYaxis()->CenterTitle(true);

    // Create a canvas to display the plot
    TCanvas *canvas = new TCanvas("canvas", "Gaussians with Data", 950, 600);

    // Draw the data points
    graph->SetMarkerStyle(20);
    graph->SetMarkerSize(0.7);
    graph->Draw("AP");

    // Create and draw the three Gaussian functions
    TF1 *gaussian1 = new TF1("gaussian1", "[0]*TMath::Gaus(x, [1], [2])", 700, 1000);
    TF1 *gaussian2 = new TF1("gaussian2", "[0]*TMath::Gaus(x, [1], [2])", 600, 900);
    TF1 *gaussian3 = new TF1("gaussian3", "[0]*TMath::Gaus(x, [1], [2])", 0, 300);
    TF1 *gaussian4 = new TF1("gaussian4", "[0]*TMath::Gaus(x, [1], [2])", 0, 300);
    
    // Césio 237
    gaussian1->SetParameters(3.73699e+02, 8.27303e+02, 1.62066e+01);
    gaussian2->SetParameters(4.81812e+02, 7.28563e+02, 1.59784e+01);
    gaussian3->SetParameters(6.15022e+02, 1.42145e+02, 2.65231e+01);
    gaussian4->SetParameters(6.29325e+02, 1.18064e+02, 1.81869e+01);

    gaussian1->SetLineColor(kRed);
    gaussian2->SetLineColor(kAzure-6);
    gaussian3->SetLineColor(kSpring-8);
    gaussian4->SetLineColor(kOrange-2);

    gaussian1->Draw("same");
    gaussian2->Draw("same");
    gaussian3->Draw("same");
    gaussian4->Draw("same");

    /* Sum gaussians?
    // Create and draw the sum of the Gaussians
    TF1 *gaussianSum = new TF1("gaussianSum", "[0]*TMath::Gaus(x, [1], [2]) + [3]*TMath::Gaus(x, [4], [5])", 0, 500);

    gaussianSum->SetParameters(1.42697e+04, 1.92995e+01, 2.09538e+00, 6.38699e+03, 4.16048e+02, 1.10978e+01);

    gaussianSum->SetLineColor(kSpring-8);

    gaussianSum->Draw("same");
    */

    // Create a legend and add entries for the data, individual Gaussians, and the sum
    TLegend *legend = new TLegend(0.7,0.7,0.9,0.9);
    legend->AddEntry(graph, "Dados", "lep");
    legend->AddEntry(gaussian4, "Pico de retrodifusao 1", "l");
    legend->AddEntry(gaussian3, "Pico de retrodifusao 2", "l");
    legend->AddEntry(gaussian2, "Pico de absorcao total 1", "l");
    legend->AddEntry(gaussian1, "Pico de absorcao total 2", "l");
    

    //legend->AddEntry(gaussianSum, "Soma dos picos", "l");

    legend->Draw();

    // Save the plot as a PDF file
    canvas->SaveAs("plot.pdf");
}


int main()
{
    PlotGaussiansWithData();
    return 0;
}
