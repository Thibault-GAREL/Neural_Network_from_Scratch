//
// Created by garel on 07/03/2024.
//

#include "calcul.h"

void lireFichierTexte(float **tableau_input2D, float **tableau_target2D, int nb_tab_entree, int nb_entree, int nb_sortie) {
    FILE *fichier = fopen("..//donnees.txt", "r");

    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }


    // Lecture des données dans le tableau
    for (int i = 0; i < nb_tab_entree; ++i) {
        for (int j = 0; j < nb_entree; ++j) {
            fscanf(fichier, "%f", &tableau_input2D[i][j]);
            //printf("tableau_input2D[%d][%d] = %f\n", i, j, tableau_input2D[i][j]);
        }
        for (int j = 0; j < nb_sortie; ++j) {
            fscanf(fichier, "%f", &tableau_target2D[i][j]);
            //printf("tableau_target2D[%d][%d] = %f\n", i, j, tableau_target2D[i][j]);
        }
    }

    fclose(fichier);
}

float calculer_erreur_moyenne(Neuron_network* my_network, Donnees* donnees, float DIVIDER) {
    float erreur_moyenne = 0;

    for (int i = 0; i < donnees->nb_tab_entree; ++i) {
        for (int j = 0; j < my_network->couche[my_network->nb_couche-1]->nb_neurone; ++j) {
//            printf("tableau_target2D[%d][%d] = %f", i, j, donnees->tableau_target[i][j]);
//            printf("tableau_couche_sortie_output[%d][%d] = %f", i, j, tableau_couche_sortie_output[i][j]);
            erreur_moyenne += fabs(donnees->tableau_target[i][j] * DIVIDER - donnees->tableau_comput[i][j]);
        }
    }

    erreur_moyenne /= donnees->nb_tab_entree;
//    printf("Erreur moyenne absolue = %f\n", erreur_moyenne);
    return erreur_moyenne;
}

void calculer_link (Neuron_network* my_network, Donnees* donnees, float DIVIDER){
    int som = 0;
    for (int j = 0; j < my_network->nb_couche; ++j) {
                som += my_network->couche[j]->nb_entree * my_network->couche[j]->nb_neurone;
    }
    printf("som = %d\n", som);
    my_network->nb_link = som;
}

void diviseur_d_entree (float **tableau_input2D, float **tableau_target2D, int nb_tab_entree, int nb_entree, int nb_sortie, float DIVIDER) {
    for (int i = 0; i < nb_tab_entree; ++i) {
        for (int j = 0; j < nb_entree; ++j) {
            //printf("Entrée divisée : %f\n", (tableau_input2D[i][j]));
            (tableau_input2D[i][j]) = (tableau_input2D[i][j] / DIVIDER);
        }
        for (int j = 0; j < nb_sortie; ++j) {
            //printf("Sortie divisée : %f\n", (tableau_target2D[i][j]));
            (tableau_target2D[i][j]) = (tableau_target2D[i][j] / DIVIDER);
        }
    }
}

float sigmoid(float x) {
    return 1.0 / (1.0 + exp(-x));
}

float sigmoid_derivative(float x) {
    float sig_x = sigmoid(x);
    return sig_x * (1.0 - sig_x);
}

float sigmoid_derivative_partielle(float x) {
    return x * (1.0 - x);//
}


float relu(float x) {
    return (x >= 0) ? x+0.001: 0;
}

float relu_derivative(float x) {
    return (x >= 0) ? 1 : 0;
}