#ifndef _MODEL_H_
#define _MODEL_H_
#define NUM_VAR 9

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

struct parameters {
    double microglia; // average microglia density               
    double oligod;    // average oligodendrocyte density              
    double delta;     // production rate of basal microglia
    double lambda;    // production rate of microglia    
    double ni;        // microglia decay rate                 
    double rho;       // production rate of oligodendrocyte
    double gamma;     // pro-inflamatory cytokine-induced oligodendrocyte damage
    double beta;      // cytokine production rate per microglia       
    double alpha;     // pro-inflamatory cytokine decay rate                       
    double mi;        // anti-inflamatory cytokine production rate
    double kappa;     // anti-inflamatory cytokine decay rate   
    double citoP;
    double citoA;

    double tHelper;       // basal density of Helper T cells
    double tCytotoxic;    // basal density of Cytotoxic T cells
    
    double alphaTH; // Helper T cells homeostasis rate
    double alphaTC; // Cytotoxic T cells homeostasis rate

    double betaTH;  // Helper T cells proliferation rate
    double betaTC;  // Cytotoxic T cells proliferation rate
    double betaTR;

    double kappaTH; // Helper T cells decay rate
    double kappaTC; // Cytotoxic T cells decay rate
    double kappaTR; // Regulatory T cells decay rate

    double rhoCA;   // Helper T cells anti-inflamatory cytokine production rate
    double rhoCP;   // Cytotoxic T cells pró-inflamatory cytokine production rate

    double gammaTC; // Cytotoxic T cells oligodendrocyte damage rate


    double MOG;       // microglia activation threshold
    double epsilon;   // treatment efficacy
};

extern parameters params;

void eulerMethod(double *x, double dt);

void rk4(double *x, double dt);

void calculateDerivatives(double *current_x, double *dxdt);

void solveModel(double *x, double dt, double t_final, const std::string &file_name);

void writeFile(double *x, double t, std::ofstream &file);

void ParametersInitializer21DaysModel();

void runEpsilonSweep(double dt, double t_final);

#endif 