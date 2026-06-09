#include "model.h"

using namespace std;

void ParametersInitializer() {
    params.microglia = 350.0; // cells/mm²            // average microglia density                     
    params.oligod = 400.0;    // cells/mm²            // average oligodendrocyte density                             
    params.lambda = 5.0e-1;   // dia^-1               // production rate of microglia
    params.ni = 6.0e-2;       // cells/mm²*dia        // microglia decay rate (estimated)
    params.p = 6.5e-1;        // dia^-1               // production rate of oligodendrocyte
    params.gamma = 6.0e-2;    // cells*ml/mm²*pg*dia  // pro-inflamatory cytokine-induced oligodendrocyte damage (estimated)
    params.beta = 4.0e-1;     // pg*mm²/ml*cells*dia  // pro-inflamatory cytokine production rate per microglia               
    params.alpha = 7.4e-2;    // dia^-1               // pro-inflamatory cytokine decay rate                                  
    params.mi = 6.5e-1;       // dia^-1               // anti-inflamatory cytokine production rate (estimated)
    params.kappa = 4.5e-1;    // dia^-1               // anti-inflamatory cytokine decay rate (estimated)

    params.microgliaBasal = 100.0; // cells/mm²           // initial condition of microglia density

    params.cv1 = 2.7e-1;
    params.cv1 = 2.7e-1;
    params.cv2 = 0;
    params.basal = 2.0e-1;
}


int main() { 
    // STARTS PARAMETERS
    ParametersInitializer();
    
    // M = MICROGLIA, O = OLIGODENDROCYTE, CP = PRO-INFALAMATORY CYTOKINE, CA = ANTI-INFALAMATORY CYTOKINE
    // INITIAL CONDITIONS
    //     x[4]       = {MB[0], MA[0], O[0], CP[0], CA[0]}
    double x[NUM_VAR] = {350.0, 0.0, 400.0, 198.0, 392.0};

    double t_final = 58; // TIME INTERVAL (days)
    double dt = 0.01;    // STEP SIZE (days)

    // STARTS THE SIMULATION
    run_simulation(x, dt, t_final);

    return 0;
}