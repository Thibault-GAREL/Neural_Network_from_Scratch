//
// Created by garel on 07/03/2024.
//

#include "1_fwd_propagation.h"

void propagation_avant(Couche *couche, float *valeur_entree) {
    for (int i = 0; i < couche->nb_neurone; ++i) {
        float somme = 0.0;
        for (int j = 0; j < couche->nb_entree; ++j) {
            somme += valeur_entree[j] * couche->weight[i][j];
//            printf("valeur_entree[%d] = %f  * ", j, valeur_entree[j]);
//            printf("couche->weight[%d][%d] = %f\n", i, j, couche->weight[i][j]);
            //printf("Valeur entree [%d] %f\n", i, valeur_entree[i]);
        }
        //printf("Somme %f\n", somme);

        somme += couche->biais[i];

        //printf("biais : %f\n", pCouche->biais[i]);
        couche->output[i] = sigmoid(somme);
        //printf("Couche output [%d] %f\n", i, couche->output[i]);
    }
}