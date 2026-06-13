#ifndef _MODEL_H_
#define _MODEL_H_
#define NUM_VAR 5

#include <iostream>
#include <string>
#include <fstream>

struct parameters {
    double microglia; // average microglia density               
    double oligod;    // average oligodendrocyte density              
    double basal;     // production rate of basal microglia
    double lambda;    // production rate of microglia    
    double ni;        // microglia decay rate                 
    double p;         // production rate of oligodendrocyte
    double gamma;     // pro-inflamatory cytokine-induced oligodendrocyte damage
    double beta;      // cytokine production rate per microglia       
    double alpha;     // pro-inflamatory cytokine decay rate                       
    double mi;        // anti-inflamatory cytokine production rate
    double kappa;     // anti-inflamatory cytokine decay rate   


    double epsilon;     // treatment efficacy
};

extern parameters params;

void euler(double *x, double dt);

void rk4(double *x, double dt);

void calculate_derivatives(double *current_x, double *dxdt);

void run_simulation (double *x, double dt, double t_final, const std::string &file_name);

void writeFile(double *x, double t, std::ofstream &file);

void ParametersInitializer21DaysModel();

void ParametersInitializer58DaysModel();

#endif 