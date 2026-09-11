#include "model.h"

using namespace std;

// This function initializes the parameters for the second 21 days model.
void ParametersInitializer21DaysModel() {
    params.microglia = 350.0; // cells/mm²            // average microglia density                     
    params.oligod = 400.0;    // cells/mm²            // average oligodendrocyte density                             
    params.delta = 1.0e-1;    // dia^-1               // production rate of microglia
    params.lambda = 2.3e-1;   // cells/mm²*dia        // activation rate of microglia by basal microglia
    params.ni = 2.0e-2;       // cells/mm²*dia        // microglia decay rate 
    params.p = 6.5e-1;        // dia^-1               // production rate of oligodendrocyte
    params.gamma = 2.0e-1;    // cells*ml/mm²*pg*dia  // pro-inflamatory cytokine-induced oligodendrocyte damage 
    params.beta = 3.9e-1;     // pg*mm²/ml*cells*dia  // pro-inflamatory cytokine production rate per microglia               
    params.alpha = 6.2e-2;    // dia^-1               // pro-inflamatory cytokine decay rate                                  
    params.mi = 7.9e-1;       // dia^-1               // anti-inflamatory cytokine production rate 
    params.kappa = 3.6e-1;    // dia^-1               // anti-inflamatory cytokine decay rate 
    params.citoP = 198.0;     // pg/ml                // basal pro-inflamatory cytokine concentration
    params.citoA = 392.0;     // pg/ml                // basal anti-inflamatory cytokine concentration
    
    params.tCD4 = 80.0;       // cells/mm²            // basal density of homeostasis CD4+ T cells
    params.tCD8 = 40.0;       // cells/mm²            // basal density of homeostasis CD8+ T cells
    
    params.alphaTCD4 = 1.0e-1;
    params.betaTCD8 = 1.0e-2;
    
    params.MOG = true;        // microglia activation threshold
    params.epsilon = 0.0;     // treatment efficacy
}

int main() { 
    // RUN SIMULATION FOR MODEL 2 (WITH MICROGLIA BASAL DENSITY)
    ParametersInitializer21DaysModel();

    double dt = 0.01;       // TIME STEP (DAYS)
    double t_final = 21.0;  // FINAL TIME (DAYS)

    // INITIAL CONDITIONS
    //     x[6]       = {MB[0], MA[0], O[0], CP[0], CA[0], MT[0], TH[0], TC[0]}
    double x[NUM_VAR] = {params.microglia, 0.0, 400.0, params.citoP, params.citoA, params.microglia, 0.0, 0.0};

    string fileName = "dadosModelo.csv"; // OUTPUT FILE NAME
    solveModel(x, dt, t_final, fileName);

    //runEpsilonSweep(dt, t_final);

    return 0;
}