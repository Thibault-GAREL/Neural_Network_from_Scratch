#include "structure.h"
#include "1_fwd_propagation.h"
#include "2_back_propagation.h"
#include "calcul.h"
#include "creator.h"
#include "training.h"
#include "affichage_tableau.h"

int main() {
    printf("Début programme\n");
    Neuron_network* my_network = NULL;
    Donnees* donnees = NULL;

    srand(time(NULL));

    FILE *fichier = fopen("..//donnees.txt", "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    int nb_couche = 3; // Attention à bien remplir
    int *tableau_composant = (int*) calloc(nb_couche + 1, sizeof (int));
    tableau_composant [0] = 1;
    tableau_composant[1] = 5;
    tableau_composant[2] = 10;
    tableau_composant[3] = 1;
//    tableau_composant[4] = 1;
//    tableau_composant[5] = 1;
//    tableau_composant[6] = 1;
//    tableau_composant[7] = 5;
//    tableau_composant[8] = 5;
//    tableau_composant[9] = 1;
//    tableau_composant[10] = 1;


    int nb_tab_entree = 0;
    char ligne[30];

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        nb_tab_entree++;
    }

    float DIVIDER = 1;// 3 * nb_tab_entree

    int nb_tour_entrenement = 1; //tour total
    int nb_lap_training = 1; //tour pour chaque donnée

    my_network = creation_neuron_network(nb_couche, tableau_composant);

    donnees = creation_donnee(nb_tab_entree, my_network);
    printf("Nb tab entrée : %d\n", donnees->nb_tab_entree);

    //printf("my_network->nb_couche-1 %d\n", my_network->couche[my_network->nb_couche-3]->nb_entree);



    lireFichierTexte(donnees->tableau_input, donnees->tableau_target, donnees->nb_tab_entree, my_network->couche[0]->nb_entree, my_network->couche[my_network->nb_couche-1]->nb_neurone);
    diviseur_d_entree(donnees->tableau_input, donnees->tableau_target, donnees->nb_tab_entree, my_network->couche[0]->nb_entree, my_network->couche[my_network->nb_couche-1]->nb_neurone, DIVIDER);

    calculer_link(my_network, donnees, DIVIDER);
    affichage_tableau(my_network, donnees, nb_lap_training, DIVIDER);


//    printf("Début comput\n");
//    for (int i = 0; i < nb_tab_entree; ++i) {
//        comput(my_network, tableau_input2D[i],tableau_target2D[i], nb_tab_entree, DIVIDER);
//        for (int j = 0; j < my_network->couche[my_network->nb_couche-1]->nb_neurone; ++j) {
//            tableau_couche_sortie_output [i][j] = my_network->couche[my_network->nb_couche-1]->output[j];
//            tableau_couche_sortie_output [i][j] *= DIVIDER;
//            //printf("tableau_couche_sortie_output [%d][%d] = %f\n", i, j, tableau_couche_sortie_output [i][j]);
//        }
//    }

//    for (int i = 0; i < nb_tour_entrenement; ++i) {
//        training_all(my_network, nb_lap_training, tableau_input2D, nb_tab_entree, tableau_target2D, DIVIDER,1);
//    }

//    for (int i = 0; i < nb_tab_entree; ++i) {
//        for (int j = 0; j < my_network->couche[my_network->nb_couche-1]->nb_neurone; ++j) {
//            printf("tableau_couche_sortie_output [%d][%d] = %f\n", i, j, tableau_output_re_global [i][j]);
//        }
//    }

//    calculer_erreur_moyenne(tableau_target2D, tableau_output_re_global, nb_tab_entree, tableau_composant[nb_couche], DIVIDER);

    //Demande de comput
    /*float entree1 [couche->nb_entree];
    for (int i = 0; i < couche->nb_entree; ++i) {
        printf("\n Entrer une valeur entrée :");
        scanf("%f", &entree1[i]);
    }
    for (int i = 0; i < couche->nb_entree; ++i) {
        printf("Entree 1 [%d] = %f\n", i, entree1[i]);
        comput(couche, couche_sortie, entree1, entree1, nb_tab_entree, DIVIDER);
    }*/


    liberation_memoire_network(my_network);
    liberation_donnee(donnees);
    return 0;
}
