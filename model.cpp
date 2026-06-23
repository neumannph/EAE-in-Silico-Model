#include <iostream>
#include <iomanip>
#include <fstream>
#include "model.h"
using namespace std;

parameters params;

void model1(double *x, double dt, double t_final, const string &file_name) {
    ofstream file(file_name);

    if (!file.is_open()) {
        cerr << "ERRO AO ABRIR O ARQUIVO" << endl;
        exit(1);
    }

    double t = 0.0;
    file << "tempo,microglias,oligodendrocytes,citocinaPro,citocinaAnti\n"; // HEADER OF THE CSV FILE
    writeFileM1(x, t, file); // PRINT THE INITIAL CONDITION IN file_name (.csv)
    
    //PRINT EACH DATA IN file_name (.csv)
    while (t < t_final) {
        eulerModel1(x, dt);
        t += dt;
        writeFileM1(x, t, file); 
    }
    file.close();
}

void model2(double *x, double dt, double t_final, const string &file_name) {
    ofstream file(file_name);

    if (!file.is_open()) {
        cerr << "ERRO AO ABRIR O ARQUIVO" << endl;
        return;
    }

    double t = 0.0;
    file << "tempo,microglia,celula-iba1+,oligodendrocytes,citocinaPro,citocinaAnti\n"; // HEADER OF THE CSV FILE
    writeFileM2(x, t, file); // PRINT THE INITIAL CONDITION IN file_name (.csv)
    
    //PRINT EACH DATA IN file_name (.csv)
    while (t < t_final) {
        eulerModel2(x, dt);
        t += dt;
        writeFileM2(x, t, file); 
    }
    file.close();
}

void eulerModel1(double *x, double dt) {
    double dxdt[NUM_VAR_M1];

    calculateDerivativesModel1(x, dxdt);

    for(int i = 0; i < NUM_VAR_M1; i++) {
        x[i] = x[i] + dt * dxdt[i];
        if(x[i] <= 0)
            x[i] = 0.0;
    }
}

void eulerModel2(double *x, double dt) {
    double dxdt[NUM_VAR_M2];

    calculateDerivativesModel2(x, dxdt);

    for(int i = 0; i < NUM_VAR_M2; i++) {
        x[i] = x[i] + dt * dxdt[i];
        if(x[i] <= 0)
            x[i] = 0.0;
    }
}

void calculateDerivativesModel1(double *current_x, double *dxdt) {
    double MA = current_x[0];  // MA = density of activated microglias (cells/mm²)
    double O  = current_x[1];  // O  = density of oligodendrocytes (cells/mm²)
    double CP = current_x[2];  // CP = concentration of pro-inflamatory cytokines (pg/ml)
    double CA = current_x[3];  // CA = concentration of anti-inflamatory cytokines (pg/ml)

    //activated microglia
    dxdt[0] = params.lambda * MA * (1 - MA/params.microglia) - params.ni * CA;
    
    //oligodendrocyte
    dxdt[1] = params.p * O * (1 - O/params.oligod) - params.gamma * CP; 

    //pro-inflamatory cytokines
    dxdt[2] = params.beta * MA - params.alpha * CA;
    
    //anti-inflamatory cytokines
    dxdt[3] = params.mi * CP - params.kappa * CA;
}

void calculateDerivativesModel2(double *current_x, double *dxdt) {
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

void writeFileM1(double *x, double t, ofstream &file) {
    // PRINT MODEL: TIME   MICROGLIA   CELULAS IBA-1+   CYTOKINES   OLIGODENDROCITES
    file << fixed << setprecision(3);
    file << t << ",";       // Time
    file << x[0] << ",";    // Microglia
    file << x[1] << ",";    // Oligodendrocyte     
    file << x[2] << ",";    // Pro-Inflamatory Cytokines
    file << x[3] << "\n";     // Anti-Inflamatory Cytokines
}

void writeFileM2(double *x, double t, ofstream &file) {
    // PRINT MODEL: TIME   MICROGLIA   CELULAS IBA-1+   CYTOKINES   OLIGODENDROCITES
    file << fixed << setprecision(3);
    file << t << ",";       // Time
    file << x[0] << ",";    // Microglia
    file << x[1] << ",";    // Celulas Iba-1+
    file << x[2] << ",";    // Oligodendrocyte     
    file << x[3] << ",";    // Pro-Inflamatory Cytokines
    file << x[4] << "\n";     // Anti-Inflamatory Cytokines
}


/* 
void rk4(double *x, double dt) {
    double k1[NUM_VAR_M1], k2[NUM_VAR_M1], k3[NUM_VAR_M1], k4[NUM_VAR_M1];
    double temp[NUM_VAR_M1];
    
    //k1
    calculateDerivativesModel1(x, k1);
    for(int i = 0; i < NUM_VAR_M1; i++)
        temp[i] = x[i] + 0.5 * dt * k1[i];    

    //k2
    calculateDerivativesModel1(temp, k2);
    for(int i = 0; i < NUM_VAR_M1; i++)
        temp[i] = x[i] + 0.5 * dt * k2[i];
    
    //k3    
    calculateDerivativesModel1(temp, k3);
    for(int i = 0; i < NUM_VAR_M1; i++) 
        temp[i] = x[i] + dt * k3[i];

    //k4
    calculateDerivativesModel1(temp, k4);

    //atualiza as variaveis
    for(int i = 0; i < NUM_VAR_M1; i++) {
        x[i] += (dt/6.0) * (k1[i] + 2*k2[i] + 2*k3[i] + k4[i]);
        if(x[i] <= 0)
            x[i] = 0.0;
    }
}
 */