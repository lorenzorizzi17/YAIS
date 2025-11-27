# Yet Another Ising Simulation
A simple 2D Ising model playground with customizable MCMC engines, now in C++. As a stat mech fan, did I really have a chance of not implementing the much beloved Ising model?

## Requirements
- SFML Library

## How to use YAIS

Clone this repository in your local machine and make sure you have [SFML](https://www.sfml-dev.org/) libraries installed in a standard path. The Ising engine can be executed in two different mode:
- Terminal mode (fast, computations are performed under the hood)
- GUI mode (slow, but a nice visualization of the Markov process)
  
To compile, just use the `CMakeLists.txt` provided. In particular (make sure you are in the general directory), run with your shell:
```bash
$ mkdir build; cd build
$ cmake ..
$ make
```
Two executables will be ready to run in `build/`, namely `build/ising.out` and `build/isingGraphics.out`

### Terminal mode
Just run:
```bash
./ising.out <N> <T> <H> <MAX_TIME> <BURNIN> <THINNING>
```
where
- `N` -> Total number of spins (should be a perfect square)
- `H` -> Magnetic field
- `T` -> Temperature
- `MAX_TIME` -> Number of steps in the MCMC
- `BURNIN` -> Burn-in phase size in the MCMC
- `THINNING` -> Thinning variable, decides every when samples are drawn from the Montecarlo chain

This will automatically launch a Markov chain with the desired setting. If you want more customization than the pure in-shell parameters passing, just edit `code/main.cpp`. An example of a minimal compiling code:
```cpp
#include "ising/configuration.hpp"
// Build the spin configuration
SpinConfiguration config(N, T, 0.55, H); //0.55 is the initial percentage of spins up
// Attach a MCMC engine (Metropolis-GibbsSampler-Wolff)
config.mountMCMCengine(MCMCType::MetropolisHastings);
// Set periodic boundary conditions
config.setPBC(true);
// Signal to the MCMC engine that you want to save samples from both the magnetization and the energy chains
config.keepTrack(true, true)
// Run without graphics
config.run(MAX_TIME, BURNIN, THINNING); 
```
A MCMC will be executed in background and, if `config.keepTrack(true, true)` was declared, the program will build two distinct MCMC sampling from the magnetization and energy distribution (at a fixed value of `T,H`). The (hopefully independent) samples are stored in a specific struct called `result` (collected only after the BURNIN and every THINNING steps). To retrieve the chains, simply run:
```cpp
std::vector<double> energies = config.getResults().getEnergy();
std::vector<double> magnetizations = config.getResults().getMagnetizations();
```
And you're done. You can start analyzing those distributions right away or store them in memory and use your favourite statistical software.

### Graphical mode
In the graphical mode, no data is stored; the MCMC are run but samples are not collected and persisted in memory. It will however launch a graphical window showing the Ising lattice in real-time. Just run:
```bash
./isingGraphics.out <N> <T> <H> <MAX_TIME> (optional: <BLUR>)
```
This will launch two windows (a _main_ one and a _controller_ one):

[Screencast from 2025-09-24 11-56-32.webm](https://github.com/user-attachments/assets/ea13a55a-4b63-4b19-ae9c-da7dbeeb7ac9)


STILL WIP
