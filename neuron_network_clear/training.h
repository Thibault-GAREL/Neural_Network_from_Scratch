//
// Created by garel on 07/03/2024.
//

#ifndef NEURON_NETWORK_CLEAR_TRAINING_H
#define NEURON_NETWORK_CLEAR_TRAINING_H

#include "structure.h"
#include "1_fwd_propagation.h"
#include "2_back_propagation.h"
#include "affichage_tableau.h"

void training_neuron (Neuron_network *my_network, Donnees* donnees, int nb_lap_training, int entree_actuelle);

void training_all (Neuron_network *my_network, Donnees* donnees, int nb_lap_training, float DIVIDER);

float** comput (Neuron_network *my_network, Donnees* donnees, int entree_actuelle, float DIVIDER); //, float* tableau_couche_sortie_output

void print_couche (Neuron_network *my_network, float* tableau_target2D, float DIVIDER);

#endif //NEURON_NETWORK_CLEAR_TRAINING_H
