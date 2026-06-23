#include <iostream>
#include <iomanip>
#include <fstream>
#include "model.h"
using namespace std;

parameters params;

void run_simulation (double *x, double dt, double t_final, const string &file_name) {
    ofstream file(file_name);

    if (!file.is_open()) {
        cerr << "ERRO AO ABRIR O ARQUIVO" << endl;
        return;
    }

    double t = 0.0;
    file << "tempo,microglia,celula-iba1+,oligodendrocytes,citocinaPro,citocinaAnti\n"; // HEADER OF THE CSV FILE
    writeFile(x, t, file); // PRINT THE INITIAL CONDITION IN dados.csv
    
    //PRINT EACH DATA IN dados.csv
    while (t < t_final) {
        euler(x, dt);
        //rk4(x, dt);
        t += dt;
        writeFile(x, t, file); 
    }
    file.close();
}

void euler(double *x, double dt) {
    double dxdt[NUM_VAR];

    calculate_derivatives(x, dxdt);

    for(int i = 0; i < NUM_VAR; i++) {
        x[i] = x[i] + dt * dxdt[i];
        if(x[i] <= 0)
            x[i] = 0.0;
    }
}

void rk4(double *x, double dt) {
    double k1[NUM_VAR], k2[NUM_VAR], k3[NUM_VAR], k4[NUM_VAR];
    double temp[NUM_VAR];
    
    //k1
    calculate_derivatives(x, k1);
    for(int i = 0; i < NUM_VAR; i++)
        temp[i] = x[i] + 0.5 * dt * k1[i];    

    //k2
    calculate_derivatives(temp, k2);
    for(int i = 0; i < NUM_VAR; i++)
        temp[i] = x[i] + 0.5 * dt * k2[i];
    
    //k3    
    calculate_derivatives(temp, k3);
    for(int i = 0; i < NUM_VAR; i++) 
        temp[i] = x[i] + dt * k3[i];

    //k4
    calculate_derivatives(temp, k4);

    //atualiza as variaveis
    for(int i = 0; i < NUM_VAR; i++) {
        x[i] += (dt/6.0) * (k1[i] + 2*k2[i] + 2*k3[i] + k4[i]);
        if(x[i] <= 0)
            x[i] = 0.0;
    }
}

void calculate_derivatives(double *current_x, double *dxdt) {
    double MB = current_x[0];  // MB = basal density of microglias (cells/mm²)
    double MA = current_x[1];  // MA = density of activated microglias (cells/mm²)
    double O  = current_x[2];  // O  = density of oligodendrocytes (cells/mm²)
    double CP = current_x[3];  // CP = concentration of pro-inflamatory cytokines (pg/ml)
    double CA = current_x[4];  // CA = concentration of anti-inflamatory cytokines (pg/ml)

    //basal microglia
    dxdt[0] = params.delta * (params.microglia - MB) - (1 - params.epsilon) * params.lambda * MB;
    
    //activated microglia
    dxdt[1] = (1 - params.epsilon) * params.lambda * MB - params.ni * CA;
    
    //oligodendrocyte
    dxdt[2] = params.p * O * (1 - O/params.oligod) - params.gamma * CP; 

    //pro-inflamatory cytokines
    dxdt[3] = params.beta * MA - params.alpha * CA;
    
    //anti-inflamatory cytokines
    dxdt[4] = params.mi * CP - params.kappa * CA;
}

void writeFile(double *x, double t, ofstream &file) {
    // PRINT MODEL: TIME   MICROGLIA   CELULAS IBA-1+   CYTOKINES   OLIGODENDROCITES
    file << fixed << setprecision(3);
    file << t << ",";       // Time
    file << x[0] << ",";    // Microglia
    file << x[1] << ",";    // Celulas Iba-1+
    file << x[2] << ",";    // Oligodendrocyte     
    file << x[3] << ",";    // Pro-Inflamatory Cytokines
    file << x[4] << "\n";     // Anti-Inflamatory Cytokines
}
