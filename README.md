# Yet Another Ising Simulation
A simple 2D Ising model playground with customizable MCMC engines, now in C++

## Use example

```cpp
int N = 200 * 200; 
double H = 0;
int MAX_TIME = 1000;
int THINNING = 10;
int BURNIN = 100;
double T = 2;

// Build the spins
SpinConfiguration config(N, T, 0.55, H);

// Attach a MCMC engine
config.mountMCMCengine(MCMCType::MetropolisHastings);

// Set periodic boundary conditions
config.setPBC(true);

// Run without graphics
config.run(MAX_TIME, BURNIN, THINNING);

// Collect the samples drawn from the magnetization equilibrium distribution ( > BURNIN)
std::vector<double> magnetizations = config.getResults().getMagnetizations();
```

STILL WIP