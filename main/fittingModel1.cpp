#include <iostream>
#include <fstream>
#include "TCanvas.h"
#include "TGraph.h"
#include "TF1.h"
#include "TAxis.h"

using namespace std;

void FitData(const char* filename, const char* modelName) {
  // Read data from file
  ifstream file(filename);
  if (!file) {
    cerr << "Error opening file: " << filename << endl;
    return;
  }

  double x, y;
  vector<double> xs, ys;
  while (file >> x >> y)
  {
    xs.push_back(x);
    ys.push_back(y);
  }
  file.close();

  // Create a TGraph from the data
  TGraph graph(xs.size(), &xs[0], &ys[0]);

  // Define a fitting function
  TF1 fitFunc("fitFunc", modelName);

  // Set initial parameter values for the fit (modify according to your model)
  // fitFunc.SetParameter(0, initialValue0);
  // fitFunc.SetParameter(1, initialValue1);
  // fitFunc.SetParameter(2, initialValue2);
  // ...

  // Fit the data to the function
  graph.Fit(&fitFunc, "Q");

  // Plot the data and fit
  TCanvas canvas("canvas", "Data and Fit", 800, 600);
  graph.Draw("AP");
  graph.GetXaxis()->SetTitle("X");
  graph.GetYaxis()->SetTitle("Y");

  // Print the fit parameters
  cout << "Fit Parameters:" << endl;
  for (int i = 0; i < fitFunc.GetNpar(); i++) {
    cout << "Parameter " << i << ": " << fitFunc.GetParameter(i) << endl;
  }

  canvas.Update();
  canvas.SaveAs("fit_result.png");
}

int main() {
  const char* filename = "/home/goncalo/LFEA/analysis/main/data.txt";  // Replace with your data file name
  const char* modelName = "gaus";    // Replace with your model name
  FitData(filename, modelName);
  return 0;
}
