//
// Created by garel on 07/03/2024.
//

#ifndef NEURON_NETWORK_CLEAR_CALCUL_H
#define NEURON_NETWORK_CLEAR_CALCUL_H

#include "structure.h"

void lireFichierTexte(float **tableau_input2D, float **tableau_target2D, int nb_tab_entree, int nb_entree, int nb_sortie);

float calculer_erreur_moyenne(Neuron_network* my_network, Donnees* donnees, float DIVIDER);

void calculer_link (Neuron_network* my_network, Donnees* donnees, float DIVIDER);

void diviseur_d_entree (float **tableau_input2D, float **tableau_target2D, int nb_tab_entree, int nb_entree, int nb_sortie, float DIVIDER);

float sigmoid (float x);
float sigmoid_derivative (float x);
float sigmoid_derivative_partielle(float x);

float relu(float x);
float relu_derivative (float x);

#endif //NEURON_NETWORK_CLEAR_CALCUL_H
