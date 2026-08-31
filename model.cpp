#include <iostream>
#include <iomanip>
#include <fstream>
#include "model.h"
using namespace std;

parameters params;

void solveModel(double *x, double dt, double t_final, const string &file_name) {
    ofstream file(file_name);

    if (!file.is_open()) {
        cerr << "ERRO AO ABRIR O ARQUIVO" << endl;
        return;
    }

    double t = 0.0;
    file << "tempo,microglia,celula-iba1+,oligodendrocytes,citocinaPro,citocinaAnti,totalMicroglia\n"; // HEADER OF THE CSV FILE
    writeFile(x, t, file); // PRINT THE INITIAL CONDITION IN file_name (.csv)

    //PRINT EACH DATA IN file_name (.csv)
    while (t < t_final) {
        eulerMethod(x, dt);
        x[5] = x[0] + x[1]; // Update total microglia
        t += dt;
        writeFile(x, t, file); 
    }

    cout << "SIGNAL: " << signal(params.epsilon) << endl;
    cout << "epsilon: " << params.epsilon << endl;

    file.close();
}

void eulerMethod(double *x, double dt) {
    double dxdt[NUM_VAR_M2];
    
    calculateDerivatives(x, dxdt);

    for(int i = 0; i < NUM_VAR_M2; i++) {
        x[i] = x[i] + dt * dxdt[i];
    }
}

void calculateDerivatives(double *current_x, double *dxdt) {
    double MB = current_x[0];  // MB = basal density of microglias (cells/mm²)
    double MA = current_x[1];  // MA = density of activated microglias (cells/mm²)
    double O  = current_x[2];  // O  = density of oligodendrocytes (cells/mm²)
    double CP = current_x[3];  // CP = concentration of pro-inflamatory cytokines (pg/ml)
    double CA = current_x[4];  // CA = concentration of anti-inflamatory cytokines (pg/ml)

    bool MOG = params.MOG; // MOG = microglia activation threshold (true or false)

    //basal microglia
    dxdt[0] = params.delta * (params.microglia - MB) - MOG * (1 - params.epsilon) * params.lambda * MB;
    
    //activated microglia
    dxdt[1] = MOG * ((1 - params.epsilon) * params.lambda * MB - (params.ni * CA));
    
    //oligodendrocyte
    dxdt[2] = params.p * O * (1 - O/params.oligod) - params.gamma * MA; 

    //pro-inflamatory cytokines
    // dxdt[3] = params.beta * MA - params.alpha * CA;
    dxdt[3] = MOG * (params.beta * MA - params.alpha * CA);
    
    //anti-inflamatory cytokines
    dxdt[4] = MOG * (params.mi * CP - params.kappa * CA);
    // dxdt[4] = params.mi * CP * (1 - CP/params.citoP) - params.kappa * CA;
}

double signal(double epsilon) {
    return 1 - pow(0.0, 1.0 - epsilon);
}

void writeFile(double *x, double t, ofstream &file) {
    // PRINT MODEL: TIME   MICROGLIA   CELULAS IBA-1+   CYTOKINES   OLIGODENDROCITES
    file << fixed << setprecision(3);
    file << t << ",";       // Time
    file << x[0] << ",";    // Microglia
    file << x[1] << ",";    // Celulas Iba-1+
    file << x[2] << ",";    // Oligodendrocyte     
    file << x[3] << ",";    // Pro-Inflamatory Cytokines
    file << x[4] << ",";    // Anti-Inflamatory Cytokines
    file << x[5] << "\n";   // Total Microglia
    
}

/* void rk4(double *x, double dt) {
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

void runEpsilonSweep(double dt, double t_final) {
    cout << "Running epsilon sweep..." << endl;
    for(params.epsilon+0.1; params.epsilon < 1; params.epsilon+=0.1) {
        cout << "Running simulation with epsilon = " << params.epsilon << endl;
        double y[NUM_VAR_M2] = {params.microglia, 0.0, 400.0, params.citoP, params.citoA, params.microglia};
        string epsilonStr = to_string(params.epsilon);
        epsilonStr.erase(epsilonStr.find_last_not_of('0') + 1, std::string::npos); // Remove extra zeros
        if (epsilonStr.back() == '.') {
            epsilonStr += '0';
        }
        string fileNameModel2 = "dadosModelo2_epsilon_" + epsilonStr + ".csv";
        solveModel(y, dt, t_final, fileNameModel2);
    }
}