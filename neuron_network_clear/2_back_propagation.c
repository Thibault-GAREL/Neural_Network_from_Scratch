//
// Created by garel on 07/03/2024.
//

#include "2_back_propagation.h"


void back_propagation(Couche * couche, float *valeur_entree, float LEARNING_RATE) {
    for (int i = 0; i < couche->nb_neurone; ++i) {
        for (int j = 0; j < couche->nb_entree; ++j) {

            couche->weight[i][j] = couche->weight[i][j] + LEARNING_RATE * couche->delta[i] * valeur_entree[j];

        }
        couche->biais[i] += LEARNING_RATE * couche->delta[i];
    }

}

void calcul_delta_erreur_last_layer (Couche* couche, float *target_output) {
    for (int i = 0; i < couche->nb_neurone; ++i) {

        couche->delta[i] = (target_output[i] - couche->output[i])* sigmoid_derivative(couche->output[i]);

    }
}

void calcul_delta_erreur_normal (Couche* couche, Couche *couche_sortie) {
    float erreur[couche_sortie->nb_entree];
    for (int i = 0; i < couche_sortie->nb_entree; ++i) {
        erreur[i] = 0;
        for (int j = 0; j < couche_sortie->nb_neurone; ++j) {
            erreur[i] = erreur[i] + couche_sortie->delta[j] * couche_sortie->weight[j][i];
        }

        couche->delta[i] = erreur[i] * sigmoid_derivative_partielle(couche->output[i]); //relu_derivative(couche->output[i])

    }
}