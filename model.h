#ifndef _MODEL_H_
#define _MODEL_H_
#define NUM_VAR 4

#include <fstream>

typedef struct parameters {
    double microglia;   // average microglia density (macrophages density*)                 
    double oligod;      // average oligodendrocyte density              
    double beta;        // cytokine production rate per microglia       
    double lambda;      // production rate of microglia (activated macrophages*)     
    double alpha;       // cytokine decay rate                       
    double gamma;       // cytokine-induced oligodendrocyte damage
    double ni;
    double mi;
    double kappa;
    
}parameters;

extern parameters params;

void euler(double *x, double dt);

void calculate_derivatives(double *current_x, double *dxdt);

void run_simulation (double *x, double dt, double t_final);

void writeFile(double *x, double t, std::ofstream &file);

void ParametersInitializer();

#endif 