//
// Created by garel on 07/03/2024.
//

#ifndef NEURON_NETWORK_CLEAR_2_BACK_PROPAGATION_H
#define NEURON_NETWORK_CLEAR_2_BACK_PROPAGATION_H

#include "structure.h"
#include "calcul.h"

void back_propagation(Couche * couche, float *valeur_entree, float LEARNING_RATE);

void calcul_delta_erreur_last_layer (Couche* couche_sortie, float *target_output);

void calcul_delta_erreur_normal (Couche* couche, Couche *couche_sortie);

#endif //NEURON_NETWORK_CLEAR_2_BACK_PROPAGATION_H
