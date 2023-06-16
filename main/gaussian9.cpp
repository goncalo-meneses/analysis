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
    TCanvas *canvas = new TCanvas("canvas", "Gaussians with Data", 800, 600);

    canvas->SetLogy();

    // Draw the data points
    graph->SetMarkerStyle(20);
    graph->SetMarkerSize(0.7);
    graph->Draw("AP");

    // Create and draw the three Gaussian functions
    TF1 *gaussian1 = new TF1("gaussian1", "[0]*TMath::Gaus(x, [1], [2])", 0, 1023);
    TF1 *gaussian2 = new TF1("gaussian2", "[0]*TMath::Gaus(x, [1], [2])", 0, 1023);
    TF1 *gaussian3 = new TF1("gaussian3", "[0]*TMath::Gaus(x, [1], [2])", 0, 1023);
    TF1 *gaussian4 = new TF1("gaussian4", "[0]*TMath::Gaus(x, [1], [2])", 0, 1023);
    TF1 *gaussian5 = new TF1("gaussian5", "[0]*TMath::Gaus(x, [1], [2])", 0, 1023);
    TF1 *gaussian6 = new TF1("gaussian6", "[0]*TMath::Gaus(x, [1], [2])", 0, 1023);
    TF1 *gaussian7 = new TF1("gaussian7", "[0]*TMath::Gaus(x, [1], [2])", 0, 1023);
    TF1 *gaussian8 = new TF1("gaussian8", "[0]*TMath::Gaus(x, [1], [2])", 0, 1023);
    TF1 *gaussian9 = new TF1("gaussian9", "[0]*TMath::Gaus(x, [1], [2])", 0, 1023);

    gaussian1->SetParameters(4.26157e+02, 2.22007e+01, 1.31635e+01);
    gaussian2->SetParameters(1.04045e+03, 5.35090e+01, 1.83153e+01);
    gaussian3->SetParameters(6.29856e+02, 1.17050e+02, 1.98330e+01);
    gaussian4->SetParameters(6.15563e+02, 1.41329e+02, 2.71436e+01);
    gaussian5->SetParameters(2.32715e+02, 5.65679e+02, 3.49786e+01);
    gaussian6->SetParameters(1.40015e+02, 6.39883e+02, 5.08437e+01);
    gaussian7->SetParameters(4.83251e+02, 7.28768e+02, 1.58775e+01);
    gaussian8->SetParameters(3.72151e+02, 8.27220e+02, 1.63237e+01);
    gaussian9->SetParameters(2.40459e+01, 9.06270e+02, 1.71438e+01);

    gaussian1->SetLineColor(kRed);
    gaussian2->SetLineColor(kAzure-6);
    gaussian3->SetLineColor(kSpring-8);
    gaussian4->SetLineColor(kAzure+6);
    gaussian5->SetLineColor(kCyan+2);
    gaussian6->SetLineColor(kGreen-5);
    gaussian7->SetLineColor(kTeal-5);
    gaussian8->SetLineColor(kPink+3);
    gaussian9->SetLineColor(kOrange+1);

    gaussian1->Draw("same");
    gaussian2->Draw("same");
    gaussian3->Draw("same");
    gaussian4->Draw("same");
    gaussian5->Draw("same");
    gaussian6->Draw("same");
    gaussian7->Draw("same");
    gaussian8->Draw("same");
    gaussian9->Draw("same");

    // Create a legend and add entries for the data, individual Gaussians, and the sum
    TLegend *legend = new TLegend(0.7,0.7,0.9,0.9);
    legend->AddEntry(graph, "Dados", "lep");
    legend->AddEntry(gaussian1, "Pico 1", "l");
    legend->AddEntry(gaussian2, "Pico 2", "l");
    legend->AddEntry(gaussian3, "Pico 3", "l");
    legend->AddEntry(gaussian4, "Pico 4", "l");
    legend->AddEntry(gaussian5, "Pico 5", "l");
    legend->AddEntry(gaussian6, "Pico 6", "l");
    legend->AddEntry(gaussian7, "Pico 7", "l");
    legend->AddEntry(gaussian8, "Pico 8", "l");
    legend->AddEntry(gaussian9, "Pico 9", "l");
    legend->Draw();

    // Save the plot as a PDF file
    canvas->SaveAs("plot.pdf");
}


int main()
{
    PlotGaussiansWithData();
    return 0;
}
