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
    double M = current_x[0];  // M = density of microglias
    double O = current_x[1];  // O = density of oligodendrocytes
    double CP = current_x[2]; // C = concentration of pro-inflamatory cytokines
    double CA = current_x[3]; // C = concentration of anti-inflamatory cytokines

    //microglia
    dxdt[0] = params.lambda * M * (params.microglia - M) - params.ni * CA;
    
    //oligodendrocyte
    dxdt[1] = params.lambda * O * (params.oligod - O) - params.gamma * CP; 

    //pro-inflamatory cytokines
<<<<<<< HEAD
    dxdt[2] = params.beta * M - params.alpha * CP;
=======
    dxdt[2] = params.beta * M - params.alpha * CP;// * ((params.oligod - O) / params.oligod);
>>>>>>> 0fea1a082351b09dedac81d2c2fc24a3118f9f6f

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

