#ifndef _MODEL_H_
#define _MODEL_H_

#define NUM_VAR_M1 4
#define NUM_VAR_M2 6

#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>

struct parameters 
{
    double microglia;               
    double oligod;                  
    double delta;     
    double lambda;    
    double ni;        
    double p;         
    double gamma;     
    double beta;      
    double alpha;     
    double mi;        
    double kappa;     
    double citoP;
    double citoA;
    double MOG;       
    double epsilon;   
};

extern parameters params;

double signal(double epsilon);
void eulerMethod(double *x, double dt);
void rk4(double *x, double dt);
void calculateDerivatives(double *current_x, double *dxdt);
void solveModel(double *x, double dt, double t_final, const std::string &file_name);
void writeFile(double *x, double t, std::ofstream &file);
void ParametersInitializer21DaysModel(char* argv[]);
void runEpsilonSweep(double dt, double t_final);
void runSensitivityAnalysis(double dt, double t_final);

#endif