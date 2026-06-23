#include "model.h"

using namespace std;

// This function initializes the parameters for the 21 days model.
void ParametersInitializer21DaysModel1() {
    params.microglia = 350.0; // cells/mm²            // average microglia density                     
    params.oligod = 400.0;    // cells/mm²            // average oligodendrocyte density                             
    params.lambda = 6.0e-1;  // cells/mm²*dia        // activation rate of microglia by basal microglia
    params.ni = 3.0e-2;       // cells/mm²*dia        // microglia decay rate 
    params.p = 6.5e-1;        // dia^-1               // production rate of oligodendrocyte
    params.gamma = 3.7e-2;    // cells*ml/mm²*pg*dia  // pro-inflamatory cytokine-induced oligodendrocyte damage 
    params.beta = 8.9e-1;     // pg*mm²/ml*cells*dia  // pro-inflamatory cytokine production rate per microglia               
    params.alpha = 1.4e-1;    // dia^-1               // pro-inflamatory cytokine decay rate                                  
    params.mi = 4.0e-1;       // dia^-1               // anti-inflamatory cytokine production rate 
    params.kappa = 3.5e-1;    // dia^-1               // anti-inflamatory cytokine decay rate 

    params.epsilon = 0.0;     // treatment efficacy
}

// This function initializes the parameters for the 58 days model.
void ParametersInitializer21DaysModel2() {
    params.microglia = 350.0; // cells/mm²            // average microglia density                     
    params.oligod = 400.0;    // cells/mm²            // average oligodendrocyte density                             
    params.delta = 1.0e-1;    // dia^-1               // production rate of microglia
    params.lambda = 2.3e-1;  // cells/mm²*dia        // activation rate of microglia by basal microglia
    params.ni = 2.0e-2;       // cells/mm²*dia        // microglia decay rate 
    params.p = 6.5e-1;        // dia^-1               // production rate of oligodendrocyte
    params.gamma = 7.9e-2;    // cells*ml/mm²*pg*dia  // pro-inflamatory cytokine-induced oligodendrocyte damage 
    params.beta = 3.9e-1;     // pg*mm²/ml*cells*dia  // pro-inflamatory cytokine production rate per microglia               
    params.alpha = 6.2e-2;    // dia^-1               // pro-inflamatory cytokine decay rate                                  
    params.mi = 7.9e-1;       // dia^-1               // anti-inflamatory cytokine production rate 
    params.kappa = 3.6e-1;    // dia^-1               // anti-inflamatory cytokine decay rate 

    params.epsilon = 0.0;     // treatment efficacy
}

int main() { 
    // 21 DAYS MODEL
    ParametersInitializer21DaysModel1();
    
    // M = MICROGLIA, O = OLIGODENDROCYTE, CP = PRO-INFALAMATORY CYTOKINE, CA = ANTI-INFALAMATORY CYTOKINE
    // INITIAL CONDITIONS
    //     x[4]       = {MA[0], O[0], CP[0], CA[0]}
    double x[NUM_VAR_M1] = {100.0, 400.0, 198.0, 392.0};
    const string fileNameModel1 = "dadosModelo1.csv"; // OUTPUT FILE NAME

    double t_final = 21.0; // TIME INTERVAL (days)
    double dt = 0.01;    // STEP SIZE (days)
    

    // RUN SIMULATION FOR MODEL 1 (WITHOUT MICROGLIA BASAL DENSITY)
    model1(x, dt, t_final, fileNameModel1);

    // RUN SIMULATION FOR MODEL 2 (WITH MICROGLIA BASAL DENSITY)
    //     y[4]          = {MB[0], MA[0], O[0], CP[0], CA[0]}
    ParametersInitializer21DaysModel2();
    double y[NUM_VAR_M2] = {350.0, 0.0, 400.0, 198.0, 392.0};
    const string fileNameModel2 = "dadosModelo2.csv"; // OUTPUT FILE NAME
    model2(y, dt, t_final, fileNameModel2);

    return 0;
}