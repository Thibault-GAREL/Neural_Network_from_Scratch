//
// Created by garel on 07/03/2024.
//

#ifndef NEURON_NETWORK_CLEAR_STRUCTURE_H
#define NEURON_NETWORK_CLEAR_STRUCTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


//#define LEARNING_RATE 0.3//0.7
//#define LAMBDA 0.001
typedef struct {
    int nb_entree;
    int nb_neurone;
    float** weight; // weight[nb_neurone][nb_entree]
    float* biais;
    float* output;
    float* input;
    float* delta;
} Couche;

typedef struct {
    Couche** couche;
    int nb_couche;
    int* tableau_composant;
    float learning_rate;
    int nb_link;
}Neuron_network;

typedef struct {
    int nb_tab_entree; //(nb de données)
    float erreur_moy;
    float** tableau_input; //[nb_tab_entree][nb entree du réseau]
    float** tableau_target; //[nb_tab_entree][nb sortie du réseau]
    float** tableau_comput; //[nb_tab_entree][nb sortie du réseau]
}Donnees;

#endif //NEURON_NETWORK_CLEAR_STRUCTURE_H
