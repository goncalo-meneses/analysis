#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "TCanvas.h"
#include "TGraph.h"
#include "TFile.h"
#include "TMultiGraph.h"
#include "TAxis.h"
#include "TLegend.h"

void ReadDataFile(const std::string& filename, std::vector<double>& x, std::vector<double>& y) {
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        double xValue, yValue;

        if (!(iss >> xValue >> yValue)) {
            std::cout << "Error reading file: " << filename << std::endl;
            break;
        }

        x.push_back(xValue);
        y.push_back(yValue);
    }
}

void PlotDataPoints(const std::vector<std::string>& filenames, const std::vector<std::string>& legendNames) {
    TCanvas* canvas = new TCanvas("canvas", "Data Points", 800, 600);
    TMultiGraph* mg = new TMultiGraph();
    TLegend* legend = new TLegend(0.7, 0.7, 0.9, 0.9); // Adjust the position of the legend if needed

    int numColors = 5; // Number of line colors to use

    for (int i = 0; i < filenames.size(); ++i) {
        std::vector<double> xValues, yValues;
        ReadDataFile(filenames[i], xValues, yValues);

        TGraph* graph = new TGraph(xValues.size(), &xValues[0], &yValues[0]);
        graph->SetLineColor(i % numColors + kAzure); // Set line color
        graph->SetMarkerColor(i % numColors + kAzure); // Set marker color
        graph->SetMarkerStyle(20 + i);
        graph->SetTitle(filenames[i].c_str());
        graph->GetXaxis()->SetTitle("X");
        graph->GetYaxis()->SetTitle("Y");
        graph->SetMarkerSize(0.3);

        mg->Add(graph);
        legend->AddEntry(graph, legendNames[i].c_str(), "lp"); // Add the legend name to the legend
    }

    mg->Draw("APL");
    mg->SetTitle("Espetro do Cesio para diferentes espessuras massicas do Chumbo");
    mg->GetXaxis()->SetTitle("Channel");
    mg->GetYaxis()->SetTitle("Counts");
    mg->GetXaxis()->CenterTitle(true);
    mg->GetYaxis()->CenterTitle(true);
    legend->Draw();

    canvas->Update();
    canvas->SaveAs("data_points.pdf");

    delete legend;
    delete mg;
    delete canvas;
}

int main() {
    std::vector<std::string> filenames = {
        "/home/goncalo/LFEA/analysis/main/data/gamma/overkill/file1.txt",
        "/home/goncalo/LFEA/analysis/main/data/gamma/overkill/file2.txt",
        "/home/goncalo/LFEA/analysis/main/data/gamma/overkill/file3.txt",
        "/home/goncalo/LFEA/analysis/main/data/gamma/overkill/file4.txt",
        "/home/goncalo/LFEA/analysis/main/data/gamma/overkill/file5.txt",
        "/home/goncalo/LFEA/analysis/main/data/gamma/overkill/file6.txt",
    };

    std::vector<std::string> legendNames = {
        "x = 0",
        "x = 0.9477",
        "x = 1.8091",
        "x = 2.0147",
        "x = 4.465",
        "x = 7.042",
    };

    PlotDataPoints(filenames, legendNames);

    return 0;
}
