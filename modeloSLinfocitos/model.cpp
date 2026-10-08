#include <iostream>
#include <iomanip>
#include <fstream>
#include "model.h"
using namespace std;

parameters params;

void solveModel(double *x, double dt, double t_final, const string &file_name) 
{
    ofstream file(file_name);

    if (!file.is_open()) 
        cerr << "ERRO AO ABRIR O ARQUIVO" << endl;

    double t = 0.0;
    file << "tempo,microglia,celula-iba1+,oligodendrocytes,citocinaPro,citocinaAnti,totalMicroglia\n"; // HEADER OF THE CSV FILE
    writeFile(x, t, file); // PRINT THE INITIAL CONDITION IN file_name (.csv)

    // 1. Guardar o estado inicial (t = 0)
    double x_inicial[6];
    double x_Max[6], t_Max[6]; // valor e dia de pico
    double x_Min[6], t_Min[6]; // valor e dia minimo
    double auc[6] = {0.0};
    double x_anterior[6];

    for (int i = 0; i < 6; i++) 
    {
        x_inicial[i] = x[i];
        x_Max[i] = x[i];
        t_Max[i] = 0.0;
        x_Min[i] = x[i];
        t_Min[i] = 0.0;
    }

    //PRINT EACH DATA IN file_name (.csv)
    while (t < t_final) 
    {
        for (int i = 0; i < NUM_VAR_M2; i++)
            x_anterior[i] = x[i];
        
        eulerMethod(x, dt);

        x[5] = x[0] + x[1]; // Update total microglia
        t += dt;
        writeFile(x, t, file);
        
        for (int i = 0; i < NUM_VAR_M2; i++)
        {
            if (x_Max[i] < x[i]) // pegando valor e dia de pico
            {
                x_Max[i] = x[i];
                t_Max[i] = t;
            }
            if (x_Min[i] > x[i]) // pegando valor e dia de menor valor
            {
                x_Min[i] = x[i];
                t_Min[i] = t;
            }
            auc[i] += ((x_anterior[i] + x[i]) / 2.0) * dt; // acumulação
        }
    }

    /* Valores de pico */
    cout << "Valor maximo microglia: " << x_Max[0] << endl;
    cout << "Valor maximo microglia ativa: " << x_Max[1] << endl;
    cout << "Valor maximo oligodendrocito: " << x_Max[2] << endl;
    cout << "Valor maximo citocina pro: " << x_Max[3] << endl;
    cout << "Valor maximo citocina anti: " << x_Max[4] << endl;
    cout << "Valor maximo microglia total: " << x_Max[5] << endl;

    cout << endl;
    
    /* Dias de pico */
    cout << "dia de pico microglia: " << t_Max[0] << endl;
    cout << "dia de pico microglia ativa: " << t_Max[1] << endl;
    cout << "dia de pico oligodendrocito: " << t_Max[2] << endl;
    cout << "dia de pico citocina pro: " << t_Max[3] << endl;
    cout << "dia de pico citocina anti: " << t_Max[4] << endl;
    cout << "dia de pico microglia total: " << t_Max[5] << endl;

    cout << endl;

    /* Menor Valor */
    cout << "Valor minimo microglia: " << x_Min[0] << endl;
    cout << "Valor minimo microglia ativa: " << x_Min[1] << endl;
    cout << "Valor minimo oligodendrocito: " << x_Min[2] << endl;
    cout << "Valor minimo citocina pro: " << x_Min[3] << endl;
    cout << "Valor minimo citocina anti: " << x_Min[4] << endl;
    cout << "Valor minimo microglia total: " << x_Min[5] << endl;

    cout << endl;

    /* Dias de menor valor */
    cout << "Dia de menor valor microglia: " << t_Min[0] << endl;
    cout << "Dia de menor valor microglia ativa: " << t_Min[1] << endl;
    cout << "Dia de menor valor oligodendrocito: " << t_Min[2] << endl;
    cout << "Dia de menor valor citocina pro: " << t_Min[3] << endl;
    cout << "Dia de menor valor citocina anti: " << t_Min[4] << endl;
    cout << "Dia de menor valor microglia total: " << t_Min[5] << endl;

    cout << endl;

    /* Area (AUC) */
    cout << "Area da microglia: " << auc[0] << endl;
    cout << "Area da microglia ativa: " << auc[1] << endl;
    cout << "Area do oligodendrocito: " << auc[2] << endl;
    cout << "Area da citocina pro: " << auc[3] << endl;
    cout << "Area da citocina anti: " << auc[4] << endl;
    cout << "Area da microglia total: " << auc[5] << endl;

    cout << endl;

    /* TAXAS MÉDIAS DE VARIAÇÃO */
    cout << "=== TAXAS MEDIAS DE CRESCIMENTO / CONSUMO ===" << endl;
    
    // Para variáveis que sobem até ao pico
    double taxaSubidaMA = (t_Max[1] > 0) ? (x_Max[1] - x_inicial[1]) / t_Max[1] : 0.0;
    double taxaSubidaCP = (t_Max[3] > 0) ? (x_Max[3] - x_inicial[3]) / t_Max[3] : 0.0;
    double taxaSubidaCA = (t_Max[4] > 0) ? (x_Max[4] - x_inicial[4]) / t_Max[4] : 0.0;
    double taxaSubidaTotal = (t_Max[5] > 0) ? (x_Max[5] - x_inicial[5]) / t_Max[5] : 0.0;

    // Para variáveis que caem até ao mínimo
    double taxaDanoMB = (t_Min[0] > 0) ? (x_inicial[0] - x_Min[0]) / t_Min[0] : 0.0;
    double taxaDanoOligod = (t_Min[2] > 0) ? (x_inicial[2] - x_Min[2]) / t_Min[2] : 0.0;

    cout << "Taxa media consumo Microglia Basal: " << taxaDanoMB << " cel/mm2*dia" << endl;
    cout << "Taxa media expansao Microglia Ativa: " << taxaSubidaMA << " cel/mm2*dia" << endl;
    cout << "Taxa media destruicao Oligodendrocitos: " << taxaDanoOligod << " cel/mm2*dia" << endl;
    cout << "Taxa media acumulo Citocina Pro: " << taxaSubidaCP << " pg/ml*dia" << endl;
    cout << "Taxa media resposta Citocina Anti: " << taxaSubidaCA << " pg/ml*dia" << endl;
    cout << "Taxa media expansao Microglia Total: " << taxaSubidaTotal << " cel/mm2*dia" << endl;

    cout << endl;

    /* PERDA PERCENTUAL FINAL */
    double perdaPercentualOligod = ((x_inicial[2] - x[2]) / x_inicial[2]) * 100.0;
    cout << "Perda percentual final de Oligodendrocitos (dia 21): " << perdaPercentualOligod << " %" << endl;

    file.close();
}

void eulerMethod(double *x, double dt) 
{
    double dxdt[NUM_VAR_M2];
    
    calculateDerivatives(x, dxdt);

    for(int i = 0; i < NUM_VAR_M2; i++) 
        x[i] = x[i] + dt * dxdt[i];
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

void writeFile(double *x, double t, ofstream &file) 
{
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

void runEpsilonSweep(double dt, double t_final) 
{
    cout << "Running epsilon sweep..." << endl;
    for(params.epsilon+0.1; params.epsilon < 1; params.epsilon+=0.1) 
    {
        cout << "Running simulation with epsilon = " << params.epsilon << endl;

        double y[NUM_VAR_M2] = {params.microglia, 0.0, 400.0, params.citoP, params.citoA, params.microglia};
        string epsilonStr = to_string(params.epsilon);

        epsilonStr.erase(epsilonStr.find_last_not_of('0') + 1, std::string::npos); // Remove extra zeros
        
        if (epsilonStr.back() == '.') 
            epsilonStr += '0';
        
        string fileNameModel2 = "dadosModelo2_epsilon_" + epsilonStr + ".csv";
        solveModel(y, dt, t_final, fileNameModel2);
    }
}
