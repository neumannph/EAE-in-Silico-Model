#include "model.h"

using namespace std;

// This function initializes the parameters for the 21 days model.
void ParametersInitializer21DaysModel() {
    params.microglia = 350.0; // cells/mm²            // average microglia density                     
    params.oligod = 400.0;    // cells/mm²            // average oligodendrocyte density                             
    params.delta = 1.0e-1;    // dia^-1               // production rate of microglia
    params.lambda = 2.3e-1;  // cells/mm²*dia         // activation rate of microglia by basal microglia
    params.ni = 2.0e-2;       // cells/mm²*dia        // microglia decay rate 
    params.p = 6.5e-1;        // dia^-1               // production rate of oligodendrocyte
    params.gamma = 7.9e-2;    // cells*ml/mm²*pg*dia  // pro-inflamatory cytokine-induced oligodendrocyte damage 
    params.beta = 3.9e-1;     // pg*mm²/ml*cells*dia  // pro-inflamatory cytokine production rate per microglia               
    params.alpha = 6.2e-2;    // dia^-1               // pro-inflamatory cytokine decay rate                                  
    params.mi = 7.9e-1;       // dia^-1               // anti-inflamatory cytokine production rate 
    params.kappa = 3.6e-1;    // dia^-1               // anti-inflamatory cytokine decay rate 

    params.epsilon = 0.0;     // treatment efficacy
}

// This function initializes the parameters for the 58 days model.
void ParametersInitializer58DaysModel() {
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
    ParametersInitializer21DaysModel();
    
    // M = MICROGLIA, O = OLIGODENDROCYTE, CP = PRO-INFALAMATORY CYTOKINE, CA = ANTI-INFALAMATORY CYTOKINE
    // INITIAL CONDITIONS
    //     x[4]       = {MB[0], MA[0], O[0], CP[0], CA[0]}
    double x[NUM_VAR] = {350.0, 0.0, 400.0, 198.0, 392.0};

    double t_final = 21.0; // TIME INTERVAL (days)
    double dt = 0.01;    // STEP SIZE (days)
    
    const string file_name_21_days = "dados21Dias.csv"; // OUTPUT FILE NAME

    // 21 DAYS SIMULATION
    //run_simulation(x, dt, t_final, file_name_21_days);



    const string file_name_58_days = "dados58Dias.csv";
    
    //     x[4]       = {MB[0], MA[0], O[0], CP[0], CA[0]}
    double y[NUM_VAR] = {350.0, 0.0, 400.0, 198.0, 392.0};
    
    t_final = 58.0; // TIME INTERVAL (days)
    
    
    ParametersInitializer58DaysModel();
    run_simulation(y, dt, t_final, file_name_58_days);

    return 0;
}