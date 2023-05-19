#include <iostream>
#include "TGraph.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TF1.h"

// Define a custom function to fit
Double_t myFunction(Double_t* x, Double_t* par) {
  // par[0], par[1], par[2] are the parameters to be fitted
  Double_t a = par[0];
  Double_t b = par[1];
  // Double_t c = par[2];

  // Calculate the value of the function for a given x
  Double_t result = a * x[0] + b;
  return result;
}

void fitDataPoints() {
  // Create some example data points (x, y)
  Double_t x[] = {1, 2, 3, 4, 5};
  Double_t y[] = {2, 4, 6, 8, 10};
  Int_t numPoints = sizeof(x) / sizeof(x[0]);

  // Create a graph to hold the data points
  TGraph* graph = new TGraph(numPoints, x, y);

  // Create a user-defined model function
  TF1* model = new TF1("model", myFunction, 0, 6, 2);

  // Set initial parameter values for the model
  model->SetParameters(1, 1, 1);

  // Fit the data points with the model
  graph->Fit("model");

  // Create a canvas to display the data points and fit result
  TCanvas* canvas = new TCanvas("canvas", "Data Points with Fit", 800, 600);

  // Customize the canvas and plot appearance
  gStyle->SetOptFit(111);  // Show fit statistics on the plot

  // Draw the data points
  graph->SetMarkerStyle(20);
  graph->SetMarkerSize(1);
  graph->Draw("AP");

  // Update the canvas to display the fit result
  canvas->Update();

  // Save the canvas as an image file
  canvas->SaveAs("data_points_fit.png");

  // Clean up
  delete graph;
  delete model;
  delete canvas;
}

int main() {
  fitDataPoints();
  return 0;
}