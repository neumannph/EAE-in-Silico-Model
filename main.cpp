#include "model.h"

using namespace std;

void ParametersInitializer() {
    params.microglia = 350.0; // cells/mm²            // average microglia density                     
    params.oligod = 400.0;    // cells/mm²            // average oligodendrocyte density                             
    params.ni = 2.0e-2;       // cells/mm²*dia        // microglia decay rate 
    params.p = 6.5e-1;        // dia^-1               // production rate of oligodendrocyte
    params.gamma = 7.5e-2;    // cells*ml/mm²*pg*dia  // pro-inflamatory cytokine-induced oligodendrocyte damage 
    params.beta = 5.5e-1;     // pg*mm²/ml*cells*dia  // pro-inflamatory cytokine production rate per microglia               
    params.alpha = 5.6e-2;    // dia^-1               // pro-inflamatory cytokine decay rate                                  
    params.mi = 7.9e-1;       // dia^-1               // anti-inflamatory cytokine production rate 
    params.kappa = 3.6e-1;    // dia^-1               // anti-inflamatory cytokine decay rate 

    params.microgliaBasal = 100.0; // cells/mm²           // initial condition of microglia density

    params.cv1 = 0.85e-1;
    params.basal = 1.0e-1;
}


int main() { 
    // STARTS PARAMETERS
    ParametersInitializer();
    
    // M = MICROGLIA, O = OLIGODENDROCYTE, CP = PRO-INFALAMATORY CYTOKINE, CA = ANTI-INFALAMATORY CYTOKINE
    // INITIAL CONDITIONS
    //     x[4]       = {MB[0], MA[0], O[0], CP[0], CA[0]}
    double x[NUM_VAR] = {350.0, 0.0, 400.0, 198.0, 392.0};

    double t_final = 25; // TIME INTERVAL (days)
    double dt = 0.01;    // STEP SIZE (days)

    // STARTS THE SIMULATION
    run_simulation(x, dt, t_final);

    return 0;
}