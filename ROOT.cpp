#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

void graph(int N, double T, double H, int MAX_TIME, int THINNING) {
    // TGraph from a file
    TGraph *gr = new TGraph();
    std::ostringstream tStream, hStream;
    tStream << std::fixed << std::setprecision(2) << T;
    hStream << std::fixed << std::setprecision(2) << H;

    std::string magnetizationFileName = "data/magnetization/magnetization_N" + std::to_string(N) +
                                        "_T" + tStream.str() +
                                        "_H" + hStream.str() +
                                        "_t" + std::to_string(MAX_TIME) +
                                        "_th" + std::to_string(THINNING) + ".txt";

    std::ifstream file(magnetizationFileName);
    int i = 0;
    while(file.good()) {
        std::string line;
        std::getline(file, line);
        if (line.empty() || line[0] == '#') continue; // Skip empty lines and comments
        std::istringstream iss(line);
        double x;
        if (!(iss >> x)) continue; // Error reading line
        gr->SetPoint(gr->GetN(), i, x);
        i++;
    }

    gr->SetTitle("Graph from File;X-axis;Y-axis");
    gr->SetMarkerStyle(21);
    gr->SetMarkerColor(kBlue);
    gr->SetLineColor(kRed);
    gr->SetLineWidth(2);
    gr->SetFillColor(kYellow);
    gr->SetFillStyle(3001); 
    // set x limits
    gr->GetYaxis()->SetRangeUser(0, 1.1);

    gr->Draw("ALP");

}



// build a histogram
void histogram(int N, double T, double H, int MAX_TIME, int THINNING) {
    TH1F *h = new TH1F("h", "Histogram from File;X-axis;Y-axis", 500, -1, 1);
    std::ostringstream tStream, hStream;
    tStream << std::fixed << std::setprecision(2) << T;
    hStream << std::fixed << std::setprecision(2) << H;

    std::string magnetizationFileName = "data/magnetization/magnetization_N" + std::to_string(N) +
                                        "_T" + tStream.str() +
                                        "_H" + hStream.str() +
                                        "_t" + std::to_string(MAX_TIME) +
                                        "_th" + std::to_string(THINNING) + ".txt";

    std::ifstream file(magnetizationFileName);
    double value;
    while (file >> value) {
        h->Fill(value);
    }

    h->SetLineColor(kRed);
    h->SetFillColor(kBlue);
    h->SetFillStyle(3001);
    h->Draw();
}

void graphMT(int N, double T, double H, int MAX_TIME, int THINNING) {
    // Create a TMultiGraph
    std::string magnetizationFileName = "data/magnetization/magnetization_N" + std::to_string(N) +
                                        "_T" + std::to_string(T) +
                                        "_H" + std::to_string(H) +
                                        "_t" + std::to_string(MAX_TIME) +
                                        "_th" + std::to_string(THINNING) + ".txt";
    std::ifstream file(magnetizationFileName);

    double avg = 0.0, count = 0;
    while (file.good()) {
        std::string line;
        std::getline(file, line);
        std::istringstream iss(line);
        double x;
        if (!(iss >> x)) continue; // Error reading line
        avg += x;
        count++;
    }
    if (count > 0) {
        avg /= count;
        std::cout << "Average magnetization for T = " << T << ", H = " << H << ": " << avg << std::endl;
    }

}
