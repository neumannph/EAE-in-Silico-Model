#include "model.h"

using namespace std;

// This function initializes the parameters for the second 21 days model.
void ParametersInitializer21DaysModel() {
    params.microglia = 350.0;  // cells/mm²            // average microglia density                     
    params.oligod = 400.0;     // cells/mm²            // average oligodendrocyte density                             
    params.delta = 1.0e-1;     // dia^-1               // production rate of microglia
    params.lambda = 2.3e-1;    // cells/mm²*dia        // activation rate of microglia by basal microglia
    params.ni = 1.5e-2;        // cells/mm²*dia        // microglia decay rate 
    params.rho = 6.5e-1;       // dia^-1               // production rate of oligodendrocyte
    params.gamma = 2.0e-5;     // cells*ml/mm²*pg*dia  // pro-inflamatory cytokine-induced oligodendrocyte damage 
    params.beta = 3.9e-1;      // pg*mm²/ml*cells*dia  // pro-inflamatory cytokine production rate per microglia               
    params.alpha = 6.0e-1;     // dia^-1               // pro-inflamatory cytokine decay rate                                  
    params.mi = 7.9e-1;        // dia^-1               // anti-inflamatory cytokine production rate 
    params.kappa = 4.5e-2;     // dia^-1               // anti-inflamatory cytokine decay rate 
    params.citoP = 198.0;      // pg/ml                // basal pro-inflamatory cytokine concentration
    params.citoA = 392.0;      // pg/ml                // basal anti-inflamatory cytokine concentration
    
    params.tHelper = 80.0;        // cells/mm²            // basal density of homeostasis Helper T cells
    params.tCytotoxic = 160.0;    // cells/mm²            // basal density of homeostasis Cytotoxic T cells
    
    params.alphaTH = 4.5e-1; // Helper T cells homeostasis rate
    params.alphaTC = 2.8e-1; // Cytotoxic T cells homeostasis rate

    params.betaTH = 4.5e-1;  // Helper T cells proliferation rate
    params.betaTC = 1.7e-1;  // Cytotoxic T cells proliferation rate
    params.betaTR = 5.0e-2;  // Regulatory T cells proliferation rate

    params.kappaTH = 1.0e-1; // Helper T cells decay rate
    params.kappaTC = 1.0e-1; // Cytotoxic T cells decay rate
    params.kappaTR = 1.0e-2; // Regulatory T cells decay rate

    params.rhoCA = 2.4e-1;    // Helper T cells anti-inflamatory cytokine production rate
    params.rhoCP = 2.0e-1;    // Cytotoxic T cells pró-inflamatory cytokine production rate    

    params.gammaTC = 1.0e-5; // Cytotoxic T cells oligodendrocyte damage rate

    params.MOG = true;         // microglia activation threshold
    params.epsilon = 0.0;      // treatment efficacy
}

int main() { 
    ParametersInitializer21DaysModel();

    double dt = 0.01;       // TIME STEP (DAYS)
    double t_final = 150.0;  // FINAL TIME (DAYS)

    // INITIAL CONDITIONS
    //     x[6]       = {MB[0], MA[0], O[0], CP[0], CA[0], TH[0], TC[0], TR[0], MT[0]}
    double x[NUM_VAR] = {params.microglia, 0.0, 400.0, params.citoP, params.citoA, 0.0, 0.0, 0.0, params.microglia};

    string fileName = "dadosModelo.csv"; // OUTPUT FILE NAME

    // RUN SIMULATION FOR MODEL
    solveModel(x, dt, t_final, fileName);

    //runEpsilonSweep(dt, t_final);

    return 0;
}