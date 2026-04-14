#include <iostream>
#include <iomanip>
#include <fstream>
#include "model.h"
using namespace std;

parameters params;

void run_simulation (double *x, double dt, double t_final) {
    ofstream file("Dados.csv");

    if (!file.is_open()) {
        cout << "===== ERRO AO ABRIR O ARQUIVO ====" << endl;
        return;
    }

    double t = 0.0;
    writeFile(x, t, file); // PRINT THE INITIAL CONDITION IN Dados.csv
    
    //PRINT EACH DATA IN Dados.csv
    while (t < t_final) {
        euler(x, dt);
        t += dt;
        writeFile(x, t, file); 
    }
    file.close();
}

// y(k+1) = yk + dt * dxdt;
void euler(double *x, double dt) {
    double dxdt[NUM_VAR];

    calculate_derivatives(x, dxdt);

    for(int i = 0; i < NUM_VAR; i++) {
        x[i] = x[i] + dt * dxdt[i];
    }
}

void calculate_derivatives(double *current_x, double *dxdt) {
    double M = current_x[0];  // M = density of microglias (cells/mm²)
    double O = current_x[1];  // O = density of oligodendrocytes (cells/mm²)
    double CP = current_x[2]; // C = concentration of pro-inflamatory cytokines (pg/ml)
    double CA = current_x[3]; // C = concentration of anti-inflamatory cytokines (pg/ml)

    //microglia
    dxdt[0] = params.lambda * M * ((params.microglia - M)/params.microglia) - params.ni * CA;
    //dxdt[0] = params.lambda * M * ((params.microglia - M)/params.microglia) - params.ni * CA; //(EQUACAO ANIGA)
    
    //oligodendrocyte
    dxdt[1] = params.p * O * (1 - O/params.oligod) - params.gamma * CP; 
    //dxdt[1] = params.lambda * O * ((params.oligod - O)/params.oligod) - params.gamma * CP; //(EQUACAO ANIGA) 

    //pro-inflamatory cytokines
    dxdt[2] = params.beta * M - params.alpha * CA;
    
    //anti-inflamatory cytokines
    dxdt[3] = params.mi * CP - params.kappa * CA;
}

void writeFile(double *x, double t, ofstream &file) {
    // PRINT MODEL: TIME   MICROGLIA   CYTOKINES   OLIGODENDROCITES
    file << fixed << setprecision(3);
    file << t << "   ";       // Time
    file << x[0] << "   ";    // Microglia
    file << x[1] << "   ";    // Oligodendrocyte     
    file << x[2] << "   ";    // Pro-Inflamatory Cytokines
    file << x[3] << "\n";     // Anti-Inflamatory Cytokines
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
    for(int i = 0; i < NUM_VAR; i++)
        x[i] += (dt/6.0) * (k1[i] + 2*k2[i] + 2*k3[i] + k4[i]);
}

