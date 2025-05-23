//
// Created by garel on 01/04/2024.
//

#ifndef NEURON_NETWORK_CLEAR_AFFICHAGE_TABLEAU_H
#define NEURON_NETWORK_CLEAR_AFFICHAGE_TABLEAU_H

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdlib.h>
#include "structure.h"

#define WIDTH_TOTAL 1450
#define HEIGHT_TOTAL 750
#define WIDTH_NUAGE 800
#define HEIGHT_NUAGE 600
#define WIDTH_ERREUR 600
#define HEIGHT_ERREUR 300
#define WIDTH_RESEAU 600
#define HEIGHT_RESEAU 450
#define AXIS_MARGIN 75
#define TICK_LENGTH 5
#define FONT_SIZE 12


int affichage_tableau (Neuron_network *my_network, Donnees* donnees, int nb_lap_training, float DIVIDER); //int nb_donnee,  float* tableau_target, float* tableau_output

void find_min_max(float array[], int size, float *min, float *max);

#endif //NEURON_NETWORK_CLEAR_AFFICHAGE_TABLEAU_H
