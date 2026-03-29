#include <iostream>
#include "model.h"

using namespace std;

void ParametersInitializer() {

    params.microglia = 350.0, // cells/mm²          // average microglia density                     
    params.oligod = 400.0,    // cells/mm²          // average oligodendrocyte density                             
    params.lambda = 2.4e-4,//1.4e-2,   // mm²/cells*min   // production rate of microglia   
    params.beta = 8.0e-2,     // pg/cells*min,      // pro-inflamatory cytokine production rate per microglia               
    params.alpha = 2.3e-1,    // min^-1             // pro-inflamatory cytokine decay rate                                  
    params.gamma = 1.0e-1,    // cells/pg*min       // pro-inflamatory cytokine-induced oligodendrocyte damage (estimated)
    params.ni = 1.0e-1,       // cells/pg*mm²       // microglia decay rate (estimated)
    params.mi = 1.0e-2,       // min^-1             // anti-inflamatory cytokine production rate (estimated)
    params.kappa = 4.0e-3;    // min^-1             // anti-inflamatory cytokine decay rate (estimated)
}

int main() {
    cout << "STARTING MAIN" << endl;
    // M = MICROGLIA, O = OLIGODENDROCYTE, CP = PRO-INFALAMATORY CYTOKINE, CA = ANTI-INFALAMATORY CYTOKINE
    // INITIAL CONDITIONS
    //     x[4]       = (M[0], O[0], CP[0], CA[0])
    double x[NUM_VAR] = {100, 400.0, 0.0, 0.0};

    double t_final = 400; // TIME INTERVAL
    double dt = 0.01;    // STEP SIZE

    // STARTS PARAMETERS
    ParametersInitializer();

    // STARTS THE SIMULATION
    run_simulation(x, dt, t_final);

    cout << "ENDING MAIN" << endl;

    return 0;
}