# Curve Fitting with ROOT

This code performs curve fitting using the ROOT library. It reads data points from a file, fits them to a specified model, and generates a plot of the data and the fit.

## Prerequisites

Before using this code, make sure you have the following prerequisites installed:

- ROOT: The ROOT data analysis framework. You can download and install it from the official website: https://root.cern/install/

## Usage

Follow these steps to use the code:

1. Prepare your data file:
   - Create a text file named `data.txt`.
   - Each line of the file should contain space-separated x and y values representing your data points.

2. Open the code file `fittingModel1.cpp` in a text editor.

3. Specify the fitting model:
   - In the `main` function, modify the `modelName` variable to specify your desired fitting model. For example, use `"gaus"` for a Gaussian model.
   - If necessary, adjust the initial parameter values for the fit by using `fitFunc.SetParameter()` in the `FitData` function.

4. Save the modified code file.

5. Open a terminal or command prompt and navigate to the directory containing the code file.

6. Compile the code:
   - Run the following command to compile the code using the `root-config` utility:
     ```
     g++ -o fittingModel1 fittingModel1.cpp `root-config --cflags --libs`
     ```

7. Run the executable:
   - Execute the compiled program by running the following command:
     ```
     ./fittingModel1
     ```

8. View the results:
   - The fit parameters will be displayed in the terminal or command prompt.
   - A plot with the data and fit will be saved as `fit_result.png` in the same directory.

Note: Make sure the `data.txt` file is located in the same directory as the code file or provide the full path to the file in the `filename` variable.

## Example

To demonstrate the usage of this code, a sample `data.txt` file is included in the repository. You can use it as a reference or replace it with your own data file.

## Contributing

Contributions are welcome! If you have any suggestions, improvements, or bug fixes, feel free to open an issue or submit a pull request.

## License

This code is licensed under the [MIT License](LICENSE).
