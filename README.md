# Yet Another Ising Simulation
A simple 2D Ising model playground with customizable MCMC engines, now in C++. As a statistical mechanics aficionado, could I __ myself from implementing the so beloved Ising model?

## How to use YAIS

Clone this repository in your local machine and make sure you have [SFML](https://www.sfml-dev.org/) libraries installed in a standard path. The Ising engine can be executed in two different mode:
### Analysis mode
Create your `main.cpp` file and define the parameters:
- `N` -> Total number of spins (should be a perfect square)
- `H` -> Magnetic field
- `T` -> Temperature
- `MAX_TIME` -> Number of steps in the MCMC
- `BURNIN` -> Burn-in phase size in the MCMC
- `THINNING` -> Thinning variable, decides every when samples are drawn from the Montecarlo chain
As an example:
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
config.run(MAX_TIME, BURNIN, THINNING); // 5 is the blur size, default is 1 (no blur)
```
A MCMC will be executed in background and, if `config.keepTrack(true, true)` was declared, the program will build two distinct MCMC sampling from the magnetization and energy distribution (at a fixed value of `T,H`). The (hopefully independent) samples are stored in a specific struct called `result` (collected only after the BURNIN and every THINNING steps). To retrieve the chains, simply run:
```cpp
std::vector<double> energies = config.getResults().getEnergy();
std::vector<double> magnetizations = config.getResults().getMagnetizations();
```
And you're done. You can start analyzing those distributions right away or store them in memory and use your favourite statistical software.

### Graphical mode
In the graphical mode, no data is stored; the MCMC are run but samples are not collected and persisted in memory. It will however launch a graphical window showing the Ising lattice in real-time

As an example:
```cpp
#include "ising/configuration.hpp"
// Build the spin configuration
SpinConfiguration config(N, T, 0.55, H); //0.55 is the initial percentage of spins up

// Attach a MCMC engine (Metropolis-GibbsSampler-Wolff)
config.mountMCMCengine(MCMCType::MetropolisHastings);
// Set periodic boundary conditions
config.setPBC(true);
// Run with graphics
config.runGraphics(THINNING, 5); // 5 is the blur size, default is 1 (no blur)
```
This will launch two windows (a _main_ one and a _controller_ one):

INSERT HERE GIF

STILL WIP