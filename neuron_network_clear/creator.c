//
// Created by garel on 07/03/2024.
//

#include "creator.h"

Neuron_network *creation_neuron_network(int nb_couche, int* tableau_composant) {
    Neuron_network* my_neural_network = (Neuron_network*) malloc (sizeof (Neuron_network));

    my_neural_network->nb_couche = nb_couche;
    my_neural_network->tableau_composant = tableau_composant;
    my_neural_network->learning_rate = 0.001;

    my_neural_network->couche = (Couche**) calloc(nb_couche, sizeof (Couche*));
    for (int i = 0; i < my_neural_network->nb_couche; ++i) {
        my_neural_network->couche[i] = creation_couche(tableau_composant[i], tableau_composant[i+1]);
        if (my_neural_network->couche[i] == NULL) {
            printf("Erreur init : ");
        }
    }

    return my_neural_network;
}

Couche *creation_couche(int nb_entree, int nb_neurone) {
    Couche *couche = (Couche *) malloc(sizeof(Couche));

    couche->nb_entree = nb_entree;
    couche->nb_neurone = nb_neurone;

    couche->weight = (float **) calloc(couche->nb_neurone, sizeof(float *));
    for (int i = 0; i < couche->nb_neurone; ++i) {
        couche->weight[i] = (float *) calloc(couche->nb_entree, sizeof(float));
    }
    couche->input = (float *) calloc(couche->nb_entree, sizeof (float));
    couche->biais = (float *) calloc(couche->nb_neurone, sizeof(float));
    couche->output = (float *) calloc(couche->nb_neurone, sizeof(float));
    couche->delta = (float *) calloc(couche->nb_neurone, sizeof(float));

    for (int i = 0; i < couche->nb_neurone; ++i) {
        for (int j = 0; j < couche->nb_entree; ++j) {
            couche->weight[i][j] = ((float) rand() / RAND_MAX) * 2 - 1; //((float) rand() / RAND_MAX) * 2 - 1
            //printf("i : %d, j : %d, poids : %f\n", i, j, couche->weight[i][j]);
        }
    }
    for (int i = 0; i < nb_neurone; ++i) {
        couche->biais[i] = ((float) rand() / RAND_MAX) * 2 - 1; //
        couche->output[i] = ((float) rand() / RAND_MAX) * 2 - 1; //((float) rand() / RAND_MAX) * 2 - 1
        couche->delta[i] = 0;
    }
    for (int i = 0; i < nb_entree; ++i) {
        couche->input [i] = 0.5;
    }

    return couche;
}

Donnees* creation_donnee (int nb_tab_entree, Neuron_network* my_network) {
    Donnees* donnees = (Donnees*) malloc (sizeof (Donnees));

    donnees->nb_tab_entree = nb_tab_entree;
    printf("Nb tab entrée à l'interieur : %d\n", donnees->nb_tab_entree);
    donnees->erreur_moy = 1;
//    printf("my_network %d\n", my_network->nb_couche);

    donnees->tableau_input = (float **)calloc(nb_tab_entree, sizeof(float *));       //[nb_tab_entree][nb_entree]
    for (int i = 0; i < nb_tab_entree; ++i) {
        donnees->tableau_input[i] = (float *)calloc(my_network->couche[0]->nb_entree, sizeof(float));
    }

    donnees->tableau_target = (float **)calloc(nb_tab_entree, sizeof(float *));       //[nb_tab_entree][nb_sortie]
    for (int i = 0; i < nb_tab_entree; ++i) {
//        printf("%d\n", my_network->couche[my_network->nb_couche-1]->nb_neurone);
        donnees->tableau_target[i] = (float *)calloc(my_network->couche[my_network->nb_couche-1]->nb_neurone, sizeof(float));
    }

    donnees->tableau_comput = (float **)calloc(nb_tab_entree, sizeof(float *));       //[nb_tab_entree][nb_sortie]
    for (int i = 0; i < nb_tab_entree; ++i) {
        donnees->tableau_comput[i] = (float *)calloc(my_network->couche[my_network->nb_couche-1]->nb_neurone, sizeof(float));
    }

    return donnees;
}

void liberation_memoire_network (Neuron_network *my_network) {
    for (int i = 0; i < my_network->nb_couche; ++i) {
        liberation_memoire_couche(my_network->couche[i]);
    }
    free(my_network->tableau_composant);
}

void liberation_memoire_couche(Couche *couche) {
    free(couche->output);
    free(couche->biais);
    free(couche->delta);
    //free(couche->input);

    liberation_tableau_entree(couche->weight, couche->nb_neurone);

    free(couche);
}



void liberation_tableau_entree(float **tableau, int lignes) {
    for (int i = 0; i < lignes; ++i) {
        free(tableau[i]);
    }
    free(tableau);
}

void liberation_donnee (Donnees* donnees) {
    liberation_tableau_entree(donnees->tableau_input, donnees->nb_tab_entree);
    liberation_tableau_entree(donnees->tableau_target, donnees->nb_tab_entree);
    liberation_tableau_entree(donnees->tableau_comput, donnees->nb_tab_entree);


    free(donnees);
}