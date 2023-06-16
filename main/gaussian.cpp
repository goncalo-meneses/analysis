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
    std::ifstream file("/home/goncalo/LFEA/analysis/main/air.txt");
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

    graph->SetTitle("Ajuste ao Espetro do ^{241}Am");
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
    TF1 *gaussian1 = new TF1("gaussian1", "[0]*TMath::Gaus(x, [1], [2])", 500, 650);
    TF1 *gaussian2 = new TF1("gaussian2", "[0]*TMath::Gaus(x, [1], [2])", 500, 650);
    TF1 *gaussian3 = new TF1("gaussian3", "[0]*TMath::Gaus(x, [1], [2])", 500, 650);

    /*
    //Amp Janela 5-7, primeiro ficheiro gonc_5_7.asc
    Se utilizar estas gaussianas, mudar os dados do data.txt
    gaussian1->SetParameters(1.41771e+02, 4.29178e+02, 1.36281e+01);
    gaussian2->SetParameters(1.04254e+03, 4.57667e+02, 7.76765e+00);
    gaussian3->SetParameters(5.79581e+03, 4.79441e+02, 5.13494e+00);
    */

    /*
    //Amp Janela 5-7, segundo ficheiro gonc_5_7_.asc
    gaussian1->SetParameters(1.46865e+02, 4.27294e+02, 1.10506e+01);
    gaussian2->SetParameters(1.04464e+03, 4.56804e+02, 6.52156e+00);
    gaussian3->SetParameters(6.02019e+03, 4.79626e+02, 5.03484e+00);
    */

    /**/
    //Amp linear com ar
    gaussian1->SetParameters(6.41878e+01, 5.85332e+02, 2.98325e+01);
    gaussian2->SetParameters(1.33457e+03, 5.92834e+02, 1.18222e+01);
    gaussian3->SetParameters(2.79386e+03, 6.02739e+02, 6.32587e+00);
    

    /*
    //Amp Linear sem ar
    gaussian1->SetParameters(5.43254e+02, 6.97870e+02, 3.33783e+00);
    gaussian2->SetParameters(3.93950e+03, 7.05066e+02, 2.11394e+00);
    gaussian3->SetParameters(2.03306e+04, 7.09964e+02, 1.52146e+00);
    */

    gaussian1->SetLineColor(kRed);
    gaussian2->SetLineColor(kAzure-6);
    gaussian3->SetLineColor(kSpring-8);

    gaussian1->Draw("same");
    gaussian2->Draw("same");
    gaussian3->Draw("same");

    // Create and draw the sum of the Gaussians
    TF1 *gaussianSum = new TF1("gaussianSum", "[0]*TMath::Gaus(x, [1], [2]) + [3]*TMath::Gaus(x, [4], [5]) + [6]*TMath::Gaus(x, [7], [8])", 500, 650);

    // Amp Janela, primeiro ficheiro gonc_5_7.asc
    //gaussianSum->SetParameters(1.41771e+02, 4.29178e+02, 1.36281e+01, 1.04254e+03, 4.57667e+02, 7.76765e+00, 5.79581e+03, 4.79441e+02, 5.13494e+00);
    
    // Amp linear com ar
    gaussianSum->SetParameters(6.41878e+01, 5.85332e+02, 2.98325e+01, 1.33457e+03, 5.92834e+02, 1.18222e+01, 2.79386e+03, 6.02739e+02, 6.32587e+00);
    
    // Amp Linear sem ar
    //gaussianSum->SetParameters(5.43254e+02, 6.97870e+02, 3.33783e+00, 3.93950e+03, 7.05066e+02, 2.11394e+00, 2.03306e+04, 7.09964e+02, 1.52146e+00);
    
    gaussianSum->SetLineColor(kPink-4);

    gaussianSum->Draw("same");

    // Create a legend and add entries for the data, individual Gaussians, and the sum
    TLegend *legend = new TLegend(0.1,0.7,0.40,0.9);
    legend->AddEntry(graph, "Dados", "lep");
    legend->AddEntry(gaussian1, "Pico 1", "l");
    legend->AddEntry(gaussian2, "Pico 2", "l");
    legend->AddEntry(gaussian3, "Pico 3", "l");
    legend->AddEntry(gaussianSum, "Soma dos Picos", "l");
    legend->Draw();

    // Save the plot as a PDF file
    canvas->SaveAs("plot.pdf");
}


int main()
{
    PlotGaussiansWithData();
    return 0;
}
