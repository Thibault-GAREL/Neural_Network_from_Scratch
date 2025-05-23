//
// Created by garel on 07/03/2024.
//

#ifndef NEURON_NETWORK_CLEAR_CREATOR_H
#define NEURON_NETWORK_CLEAR_CREATOR_H

#include "structure.h"

Neuron_network* creation_neuron_network(int nb_couche, int* tableau_composant);
Couche* creation_couche (int nb_entree, int nb_neurone);
Donnees* creation_donnee (int nb_tab_entree, Neuron_network* my_network);

void liberation_memoire_network (Neuron_network *my_network);
void liberation_memoire_couche (Couche* couche);
void liberation_tableau_entree(float **tableau, int lignes);
void liberation_donnee (Donnees* donnees);

#endif //NEURON_NETWORK_CLEAR_CREATOR_H
