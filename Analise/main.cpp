#include "model.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void ParametersInitializer21DaysModel(char* argv[]) {
    params.microglia = 350.0   * atof(argv[1]);
    params.oligod    = 400.0   * atof(argv[2]);
    params.delta     = 1.8e-1  * atof(argv[3]);
    params.lambda    = 2.3e-1  * atof(argv[4]);
    params.ni        = 2.8e-2  * atof(argv[5]);
    params.p         = 6.5e-1  * atof(argv[6]);
    params.gamma    = 2.0e-1  * atof(argv[7]);
    params.beta     = 3.9e-1  * atof(argv[8]);
    params.alpha    = 6.2e-2  * atof(argv[9]);
    params.mi       = 7.9e-1  * atof(argv[10]);
    params.kappa    = 3.6e-1  * atof(argv[11]);
    params.citoP    = 198.0   * atof(argv[12]);
    params.citoA    = 392.0   * atof(argv[13]);

    params.MOG = 1.0;
    params.epsilon = 0.0;
}

int main(int argc, char* argv[]) 
{
    if (argc < 14) 
    {
        cerr << "Erro: passe os 13 parametros!" << endl;
        return 1;
    }

    ParametersInitializer21DaysModel(argv);

    double dt = 0.01;
    double t_final = 21.0;

    double x[NUM_VAR_M2] = {params.microglia, 0.0, 400.0, params.citoP, params.citoA, params.microglia};

    string fileName = "/dev/null"; 
    solveModel(x, dt, t_final, fileName);

    return 0;
}