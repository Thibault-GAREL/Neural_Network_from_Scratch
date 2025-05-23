//
// Created by garel on 07/03/2024.
//

#include "training.h"

void training_neuron (Neuron_network *my_network, Donnees* donnees, int nb_lap_training, int entree_actuelle) {
    for (int i = 0; i < nb_lap_training; ++i){
//        my_network->learning_rate = donnees->erreur_moy;
//        if (donnees->erreur_moy > 0.5) {
//            my_network->learning_rate = donnees->erreur_moy;
//        }
//        if (donnees->erreur_moy < 0.1) {
//            my_network->learning_rate = donnees->erreur_moy;
//        }
        my_network->learning_rate = 0.5;
        if (my_network->nb_link > 1000){
            my_network->learning_rate = 0.001;
        }
        if (donnees->erreur_moy < 0.2){
            my_network->learning_rate = 0.1;
        }
        if (donnees->erreur_moy < 0.02){
            my_network->learning_rate = 0.01;
        }
//        printf("learning rate = %f\n", my_network->learning_rate);


        comput(my_network, donnees, entree_actuelle, 1);


        calcul_delta_erreur_last_layer(my_network->couche[my_network->nb_couche-1], donnees->tableau_target[entree_actuelle]);
        back_propagation(my_network->couche[my_network->nb_couche-1], my_network->couche[my_network->nb_couche-2]->input, my_network->learning_rate);


        for (int j = my_network->nb_couche - 2; j >= 0; --j) {
            calcul_delta_erreur_normal(my_network->couche[j], my_network->couche[j+1]); //Attention target output n'est pas le même, il va regarde + que 0 (0.1 100S000S)

            back_propagation(my_network->couche[j], my_network->couche[j]->input, my_network->learning_rate);
        }
    }
}

void training_all (Neuron_network *my_network, Donnees* donnees, int nb_lap_training, float DIVIDER) {
    for (int i = 0; i < donnees->nb_tab_entree; ++i) {

        training_neuron(my_network, donnees, nb_lap_training, i);
        donnees->erreur_moy = calculer_erreur_moyenne(my_network, donnees, DIVIDER);

    }
}

float** comput (Neuron_network *my_network, Donnees* donnees, int entree_actuelle, float DIVIDER) {//, float *tableau_couche_sortie_output
    float** tableau_comput = (float **)calloc(donnees->nb_tab_entree, sizeof(float*));
    for (int i = 0; i < donnees->nb_tab_entree; ++i) {
        tableau_comput[i] = malloc(my_network->couche[my_network->nb_couche-1]->nb_neurone * sizeof(float));
    }

    my_network->couche[0]->input = donnees->tableau_input[entree_actuelle];
    propagation_avant(my_network->couche[0], donnees->tableau_input[entree_actuelle]);

    for (int j = 0; j < my_network->nb_couche; ++j) { //Attention my_network->nb_couche-1, ici on cherche à écrire le dernier poids
        if(j != my_network->nb_couche-1) {
            my_network->couche[j+1]->input = my_network->couche[j]->output;
            propagation_avant(my_network->couche[j+1], my_network->couche[j]->output);

        }
    }
    for (int j = 0; j < my_network->couche[my_network->nb_couche-1]->nb_neurone; ++j) {
        tableau_comput[entree_actuelle][j] = my_network->couche[my_network->nb_couche-1]->output[j];
        donnees->tableau_comput[entree_actuelle][j] = my_network->couche[my_network->nb_couche-1]->output[j];
    }

    return tableau_comput;
}

void print_couche (Neuron_network *my_network, float* tableau_target2D, float DIVIDER) {
    printf("=================================================\n");
    printf("Entree finale\n");
    for (int j = 0; j < my_network->couche[0]->nb_entree; ++j) {
        printf("[%d] = %f (%f)\n", j, my_network->couche[0]->input[j]*DIVIDER, my_network->couche[0]->input[j]);
    }

    printf("\n\nHiden neuron\n");

    for (int k = 0; k < my_network->nb_couche; ++k) {
        printf("\nWeight couche [%d]\n", k);
        for (int i = 0; i < my_network->couche[k]->nb_neurone; ++i) {
            for (int j = 0; j < my_network->couche[k]->nb_entree; ++j) {
                printf("[%d][%d] = %f   |   ", i, j , my_network->couche[k]->weight[i][j]);
            }
//            printf("biais [%d] = %f\n", k, my_network->couche[k]->biais[i]);
            printf("delta couche[%d]->delta[%d] = %f\n", k, i, my_network->couche[k]->delta[i]);
        }
        printf("\n");
        for (int i = 0; i < my_network->couche[k]->nb_neurone; ++i) {
            printf("couche[%d]->output[%d] = %f\n", k, i, my_network->couche[k]->output[i]);
        }
    }
    printf("\nOutput\n");
    for (int j = 0; j < my_network->couche[my_network->nb_couche-1]->nb_neurone; ++j) {
        printf("[%d] = %f  (%f) et doit être égale à %f\n", j, my_network->couche[my_network->nb_couche-1]->output[j]*DIVIDER, my_network->couche[my_network->nb_couche-1]->output[j], tableau_target2D[j]*DIVIDER);
        printf("Erreur de %f", (tableau_target2D[j] - my_network->couche[my_network->nb_couche-1]->output[j])*(DIVIDER));
    }
    printf("\n\n");
}