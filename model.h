#ifndef _MODEL_H_
#define _MODEL_H_
#define NUM_VAR_M1 4
#define NUM_VAR_M2 6

#include <iostream>
#include <string>
#include <fstream>

struct parameters {
    double microglia; // average microglia density               
    double oligod;    // average oligodendrocyte density              
    double delta;     // production rate of basal microglia
    double lambda;    // production rate of microglia    
    double ni;        // microglia decay rate                 
    double p;         // production rate of oligodendrocyte
    double gamma;     // pro-inflamatory cytokine-induced oligodendrocyte damage
    double beta;      // cytokine production rate per microglia       
    double alpha;     // pro-inflamatory cytokine decay rate                       
    double mi;        // anti-inflamatory cytokine production rate
    double kappa;     // anti-inflamatory cytokine decay rate   
    double citoP;
    double citoA;


    double epsilon;     // treatment efficacy
};

extern parameters params;

void eulerModel1(double *x, double dt);

void eulerModel2(double *x, double dt);

void rk4(double *x, double dt);

void calculateDerivativesModel1(double *current_x, double *dxdt);

void calculateDerivativesModel2(double *current_x, double *dxdt);

void solveModel1(double *x, double dt, double t_final, const std::string &file_name);

void solveModel2(double *x, double dt, double t_final, const std::string &file_name);

void writeFileM1(double *x, double t, std::ofstream &file);

void writeFileM2(double *x, double t, std::ofstream &file);

void ParametersInitializer21DaysModel1();

void ParametersInitializer21DaysModel2();

void runEpsilonSweep(double dt, double t_final);

#endif 