#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <omp.h>

#include "ising/configuration.hpp"

int main() {
    // Create a SpinConfiguration object
    int N = 200*200; 
    double H = 0;
    int MAX_TIME = 1000;
    int THINNING = 10;
    int BURNIN = 100;
    double T = 2; // 1.1 + i * 0.2;
    // Build the lattice
    SpinConfiguration config(N, T, 0.55, H);
    // Attach a MCMC engine
    config.mountMCMCengine(MCMCType::MetropolisHastings);
    config.setPBC(true); // Set periodic boundary conditions
    config.keepTrack(false, false); // Magnetization only
    // Now run the MCMC chain
    config.runGraphics(MAX_TIME, BURNIN, THINNING, 1);

    // Get the results
    std::vector<double> energies = config.getResults().getEnergy();
    std::vector<double> magnetizations = config.getResults().getMagnetizations();
}


