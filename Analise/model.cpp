#include <iostream>
#include <iomanip>
#include <fstream>
#include "model.h"
using namespace std;

parameters params;

void solveModel(double *x, double dt, double t_final, const string &file_name) 
{

    double t = 0.0;
    
    while (t < t_final) 
    {
        eulerMethod(x, dt);
        x[5] = x[0] + x[1]; 
        t += dt;
    }
    
    cout << x[0] << endl;
    cout << x[1] << endl;
    cout << x[2] << endl;
    cout << x[3] << endl;
    cout << x[4] << endl;
    cout << x[5] << endl;
}

void eulerMethod(double *x, double dt) 
{
    double dxdt[NUM_VAR_M2];
    
    calculateDerivatives(x, dxdt);

    for(int i = 0; i < NUM_VAR_M2; i++) 
    {
        x[i] = x[i] + dt * dxdt[i];

        if (isnan(x[i]) || isinf(x[i])) 
            x[i] = 0.0;
        
        if (x[i] < 0.0) 
            x[i] = 0.0;
    }
}

void calculateDerivatives(double *current_x, double *dxdt) 
{
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
    dxdt[3] = MOG * (params.beta * MA - params.alpha * CA);
    
    //anti-inflamatory cytokines
    dxdt[4] = MOG * (params.mi * CP - params.kappa * CA);
}