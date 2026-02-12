#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include "model.h"
using namespace std;

parameters params;

void run_simulation (double *x, double dt, double t_final) {
    ofstream file("Dados.csv");
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
    double M = current_x[0]; // M = density of microglia
    double C = current_x[1]; // C = concentration of chemoattractants
    double O = current_x[2]; // O = density of oligodendrocytes

    dxdt[0] = params.lambda * M * (params.microglia - M);
    
    dxdt[1] = params.beta * M - params.alpha * C * ((params.oligod - O) / params.oligod);
    
    dxdt[2] = ((params.oligod - O)/params.oligod) - params.gamma * C; 
}

void writeFile(double *x, double t, ofstream &file) {
    // PRINT MODEL: TIME   MICROGLIA   CYTOKINES   OLIGODENDROCITES
    file << fixed << setprecision(3);
    file << t << "   ";        // Time
    file << x[0] << "   ";     // Microglia
    file << x[1] << "   ";     // Cytokines
    file << x[2] << "\n";      // Oligodendrocyte     

}

