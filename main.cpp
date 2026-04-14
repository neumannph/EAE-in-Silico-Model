#include <iostream>
#include "model.h"

using namespace std;

void ParametersInitializer() {

    params.microglia = 350.0; // cells/mm²          // average microglia density                     
    params.oligod = 400.0;    // cells/mm²          // average oligodendrocyte density                             
    params.lambda = 4.0e-1;   //1.4e-2,   // mm²/cells*dia      // production rate of microglia
    params.ni = 1.0e-1;       // cells/pg*ml       // microglia decay rate (estimated)
    params.p = 8.0e-2; // mm²/cells*dia      // production rate of oligodendrocyte
    params.gamma = 2.0e-2;    // cells/?*dia       // pro-inflamatory cytokine-induced oligodendrocyte damage (estimated)
    params.beta = 1.25e-1; //8.0e-2,     // pg/cells*dia,      // pro-inflamatory cytokine production rate per microglia               
    params.alpha = 6.5e-2;    // dia^-1             // pro-inflamatory cytokine decay rate                                  
    params.mi = 1.1e-1;       // dia^-1             // anti-inflamatory cytokine production rate (estimated)
    params.kappa = 5.0e-2;    // dia^-1             // anti-inflamatory cytokine decay rate (estimated)
}

int main() { 
    cout << "STARTING MAIN" << endl;
    
    // STARTS PARAMETERS
    ParametersInitializer();
    
    // M = MICROGLIA, O = OLIGODENDROCYTE, CP = PRO-INFALAMATORY CYTOKINE, CA = ANTI-INFALAMATORY CYTOKINE
    // INITIAL CONDITIONS
    //     x[4]       = (M[0], O[0], CP[0], CA[0])
    double x[NUM_VAR] = {100.0, 400.0, 0.0, 0.0};

    double t_final = 100; // TIME INTERVAL
    double dt = 0.01;    // STEP SIZE

    // STARTS THE SIMULATION
    run_simulation(x, dt, t_final);

    cout << "ENDING MAIN" << endl;

    return 0;
}