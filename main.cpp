#include "model.h"

using namespace std;

void ParametersInitializer() {
    params.microglia = 350.0; // cells/mm²            // average microglia density                     
    params.oligod = 400.0;    // cells/mm²            // average oligodendrocyte density                             
    params.lambda = 4.3e-1;   // dia^-1               // production rate of microglia
    params.ni = 2.3e-2;       // cells/mm²*dia        // microglia decay rate (estimated)
    params.p = 6.5e-1;        // dia^-1               // production rate of oligodendrocyte
    params.gamma = 4.0e-2;    // cells*ml/mm²*pg*dia  // pro-inflamatory cytokine-induced oligodendrocyte damage (estimated)
    params.beta = 6.8e-1;     // pg*mm²/ml*cells*dia  // pro-inflamatory cytokine production rate per microglia               
    params.alpha = 9.45e-2;   // dia^-1               // pro-inflamatory cytokine decay rate                                  
    params.mi = 3.2e-1;       // dia^-1               // anti-inflamatory cytokine production rate (estimated)
    params.kappa = 2.5e-1;    // dia^-1               // anti-inflamatory cytokine decay rate (estimated)
}

int main() { 
    // STARTS PARAMETERS
    ParametersInitializer();
    
    // M = MICROGLIA, O = OLIGODENDROCYTE, CP = PRO-INFALAMATORY CYTOKINE, CA = ANTI-INFALAMATORY CYTOKINE
    // INITIAL CONDITIONS
    //     x[4]       = (M[0], O[0], CP[0], CA[0])
    double x[NUM_VAR] = {200.0, 400.0, 198.0, 392.0};

    double t_final = 60; // TIME INTERVAL
    double dt = 0.01;    // STEP SIZE

    // STARTS THE SIMULATION
    run_simulation(x, dt, t_final);

    return 0;
}