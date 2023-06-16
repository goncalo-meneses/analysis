#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

void removeAndModify(const std::string& inputFileName, const std::string& outputFileName) {
    std::ifstream inputFile(inputFileName);
    std::ofstream outputFile(outputFileName);

    if (inputFile.is_open() && outputFile.is_open()) {
        std::string line;
        std::vector<std::string> lines;

        // Read all lines from the input file
        while (std::getline(inputFile, line)) {
            lines.push_back(line);
        }

        inputFile.close();

        // Remove the first five lines
        lines.erase(lines.begin(), lines.begin() + 5);

        // Remove the last four lines
        if (lines.size() >= 4) {
            lines.erase(lines.end() - 4, lines.end());
        }

        // Modify the separator from "," to tab for the first two columns
        for (std::string& l : lines) {
            std::istringstream iss(l);
            std::string column1, column2, column3;
            if (std::getline(iss, column1, ',') && std::getline(iss, column2, ',') && std::getline(iss, column3, ',')) {
                size_t substringLength = column1.length() + column2.length() + column3.length() + 3;
                l = column1 + "\t" + column2 + (substringLength < l.length() ? l.substr(substringLength) : "");
            }
        }

        // Write the modified lines to the output file
        for (const std::string& l : lines) {
            outputFile << l << std::endl;
        }

        outputFile.close();
        std::cout << "Modifications completed successfully." << std::endl;
    } else {
        std::cerr << "Error: Unable to open input or output file." << std::endl;
    }
}

int main() {
    std::string inputFileName = "/home/goncalo/LFEA/analysis/main/input.asc";
    std::string outputFileName = "output.txt";

    removeAndModify(inputFileName, outputFileName);

    return 0;
}
