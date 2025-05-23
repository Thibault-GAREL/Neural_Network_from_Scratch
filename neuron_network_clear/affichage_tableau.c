#include "affichage_tableau.h"
#include "training.h"

int affichage_tableau(Neuron_network *my_network, Donnees* donnees, int nb_lap_training, float DIVIDER) {
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_TIMER *timer = NULL;
    bool redraw = true;
    bool quit = false;
    int tour = 0;

    float multiplieur_graphique = 200;
    int multiplicateur = 10;
    int multiplicateur_dentrainement = 1;
    float erreur_arret = 0.0001;
    int espacement_maximal = 25;
    int modulo = 1;
    int espacement_changement = 1000;
    int arret = 50000;
    int limite_affichage = 10000;

    float timer_sec = 0.001;

    float* tab_erreur = NULL;

    // Initialisation d'Allegro
    if (!al_init()) {
        fprintf(stderr, "Failed to initialize Allegro.\n");
        return -1;
    }

    // Initialisation des addons nécessaires
    al_install_keyboard();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    // Chargement de la police
    font = al_load_ttf_font("arial.ttf", FONT_SIZE, 0);
    if (!font) {
        fprintf(stderr, "Failed to load font.\n");
        return -1;
    }

    // Création de la fenêtre
    display = al_create_display(WIDTH_TOTAL, HEIGHT_TOTAL);
    if (!display) {
        fprintf(stderr, "Failed to create display.\n");
        return -1;
    }

    // Positionnement de la fenêtre au centre de l'écran
    al_set_window_position(display, 50, 50);

    // Création du timer
    timer = al_create_timer(timer_sec);
    if (!timer) {
        fprintf(stderr, "Failed to create timer.\n");
        al_destroy_display(display);
        return -1;
    }

    // Création de la file d'événements
    queue = al_create_event_queue();
    if (!queue) {
        fprintf(stderr, "Failed to create event queue.\n");
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }

    // Enregistrement des événements
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));


    // Démarrage du timer
    al_start_timer(timer);

    // Boucle principale
    while (!quit) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(queue, &ev);

        // Gestion des événements
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            quit = true; // Quitter si la fenêtre est fermée
        }else if (ev.type == ALLEGRO_EVENT_TIMER) {
            redraw = true; // Redessiner à chaque événement de timer
        }else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                quit = true;
            } else if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {
                while (true) {
                    ALLEGRO_EVENT next_event;
                    al_wait_for_event(queue, &next_event);
                    if (next_event.type == ALLEGRO_EVENT_KEY_UP && next_event.keyboard.keycode == ALLEGRO_KEY_SPACE) {
                        break;
                    }
                }
            }
        }

//        for (int i = 0; i < donnees->nb_tab_entree; ++i) {
//            for (int j = 0; j < my_network->couche[0]->nb_entree; ++j) {
//                printf("donnees->tableau_input[%d][%d] = %f\n", i, j, donnees->tableau_input[i][j]);
//            }
//            for (int j = 0; j < my_network->couche[my_network->nb_couche-1]->nb_neurone; ++j) {
//                printf("donnees->tableau_target[%d][%d] = %f\n", i, j, donnees->tableau_target[i][j]);
//            }
//        }

        // Redessiner si nécessaire
        if (redraw && al_is_event_queue_empty(queue)) {
            redraw = false;
            // Dessiner le graphique
            al_clear_to_color(al_map_rgb(255, 255, 255)); // Efface l'écran en blanc

            for (int i = 0; i < multiplicateur_dentrainement; ++i) {
                if (donnees->erreur_moy > erreur_arret){
                    training_all(my_network, donnees, nb_lap_training, DIVIDER);
                    tour++;
                }
                else {
                    al_draw_text(font, al_map_rgb(255, 0, 0), AXIS_MARGIN, HEIGHT_NUAGE - AXIS_MARGIN/2, 0, "Arrêt de calcul - erreur trop faible !");
                }
            }

            // Allocation dynamique d'un nouvel espace mémoire pour le tableau
            float *nouveau_tab_erreur = (float *)realloc(tab_erreur, (tour + 1) * sizeof(float));
            if (nouveau_tab_erreur == NULL) {
                printf("Erreur d'allocation de mémoire.\n");
                if (tab_erreur != NULL) {
                    free(tab_erreur); // Libération de la mémoire allouée précédemment
                }
                return 1;
            }

            tab_erreur = nouveau_tab_erreur;
            tab_erreur[tour] = donnees->erreur_moy;

            // Dessiner les axes x et y
            al_draw_line(AXIS_MARGIN, HEIGHT_NUAGE - AXIS_MARGIN, WIDTH_NUAGE - AXIS_MARGIN - (WIDTH_NUAGE - 2 * AXIS_MARGIN) / donnees->nb_tab_entree, HEIGHT_NUAGE - AXIS_MARGIN, al_map_rgb(0, 0, 0), 2); // Axe des abscisses
            al_draw_line(AXIS_MARGIN, HEIGHT_NUAGE - AXIS_MARGIN, AXIS_MARGIN, AXIS_MARGIN, al_map_rgb(0, 0, 0), 2); // Axe des ordonnées

            // Dessiner des graduations sur l'axe des abscisses et les numéroter
            for (int i = 0; i < donnees->nb_tab_entree; i++) {
                int x = AXIS_MARGIN + i * (WIDTH_NUAGE - 2 * AXIS_MARGIN) / donnees->nb_tab_entree;
                al_draw_line(x, HEIGHT_NUAGE - AXIS_MARGIN - TICK_LENGTH, x, HEIGHT_NUAGE - AXIS_MARGIN + TICK_LENGTH, al_map_rgb(0, 0, 0), 2);
                char label[10];
                sprintf(label, "%d", i+1);
                al_draw_text(font, al_map_rgb(0, 0, 0), x, HEIGHT_NUAGE - AXIS_MARGIN + TICK_LENGTH + 2, ALLEGRO_ALIGN_CENTER, label);
            }

            // Dessiner des graduations sur l'axe des ordonnées et les numéroter
            for (int i = 0; i <= 10; i++) {
                int y = HEIGHT_NUAGE - AXIS_MARGIN - i * (HEIGHT_NUAGE - 2 * AXIS_MARGIN) / 10;
                al_draw_line(AXIS_MARGIN - TICK_LENGTH, y, AXIS_MARGIN + TICK_LENGTH, y, al_map_rgb(0, 0, 0), 2);
                char label[10];
                sprintf(label, "%.1f", ((float )i)/10);
                al_draw_text(font, al_map_rgb(0, 0, 0), AXIS_MARGIN - TICK_LENGTH - 20, y - FONT_SIZE / 2, ALLEGRO_ALIGN_RIGHT, label);
            }

            // Dessiner les données du tableau target en vert
            for (int i = 0; i < donnees->nb_tab_entree; i++) {
                for (int j = 0; j < my_network->couche[my_network->nb_couche-1]->nb_neurone; ++j) {
                    int x = AXIS_MARGIN + i * (WIDTH_NUAGE - 2 * AXIS_MARGIN) / donnees->nb_tab_entree;
//                printf("donnees->tableau_target[%d][0] %f\n", i, donnees->tableau_target[i][0]);
                    int y = HEIGHT_NUAGE - AXIS_MARGIN - donnees->tableau_target[i][j] * multiplieur_graphique * (HEIGHT_NUAGE - 2 * AXIS_MARGIN) / 200;
                    al_draw_filled_circle(x, y, 5, al_map_rgb(0, 255, 0)); // Dessine un point vert
                }
            }

            // Dessiner les données du tableau output en rouge
            for (int i = 0; i < donnees->nb_tab_entree; i++) {
                for (int j = 0; j < my_network->couche[my_network->nb_couche-1]->nb_neurone; ++j) {
                    int x = AXIS_MARGIN + i * (WIDTH_NUAGE - 2 * AXIS_MARGIN) / donnees->nb_tab_entree;
//                printf("donnees->tableau_comput[%d][%d] = %f\n", i, my_network->couche[my_network->nb_couche-1]->nb_neurone, donnees->tableau_comput[i][my_network->couche[my_network->nb_couche-1]->nb_neurone]);
                    int y = HEIGHT_NUAGE - AXIS_MARGIN - donnees->tableau_comput[i][j] * multiplieur_graphique * (HEIGHT_NUAGE - 2 * AXIS_MARGIN) / 200;
                    al_draw_filled_circle(x, y, 5, al_map_rgb(255, 0, 0)); // Dessine un point rouge
                }
            }

            //Legende vert
            al_draw_filled_circle( AXIS_MARGIN, HEIGHT_NUAGE, 8, al_map_rgb(0, 255, 0));
            al_draw_text(font, al_map_rgb(0, 0, 0), AXIS_MARGIN * 1.5, HEIGHT_NUAGE - AXIS_MARGIN * 0.1, ALLEGRO_ALIGN_LEFT, "Point que l'on cherche à apprendre");


            //Legende rouge
            al_draw_filled_circle( AXIS_MARGIN, HEIGHT_NUAGE + AXIS_MARGIN, 8, al_map_rgb(255, 0, 0));
            al_draw_text(font, al_map_rgb(0, 0, 0), AXIS_MARGIN * 1.5, HEIGHT_NUAGE + AXIS_MARGIN - AXIS_MARGIN * 0.1, ALLEGRO_ALIGN_LEFT, "Point qu'il prédit");


            char aff_tour[100];
            sprintf(aff_tour, "Nb iteration : %d * %d", tour, multiplicateur_dentrainement);
            al_draw_text(font, al_map_rgb(0, 0, 0), 150, 25, ALLEGRO_ALIGN_RIGHT, aff_tour);

            char aff_learning_rate[100];
            sprintf(aff_learning_rate, "LEARNING RATE : %f", my_network->learning_rate);
            al_draw_text(font, al_map_rgb(0, 0, 255), 400, 25, ALLEGRO_ALIGN_RIGHT, aff_learning_rate);

            char aff_erreur_moyenne[100];
            sprintf(aff_erreur_moyenne, "Mean Error : %f", donnees->erreur_moy); // 1-0.4 0.4-0.1 <0.1
            al_draw_text(font, al_map_rgb(donnees->erreur_moy >= 0.1 ? 255 : 0,
                                          donnees->erreur_moy >= 0.25 ? 0 : (donnees->erreur_moy >= 0.1 ? 165 : 255),
                                          donnees->erreur_moy <= 0.001 ? 100 : 0), 600, 25, ALLEGRO_ALIGN_RIGHT, aff_erreur_moyenne);

            //Legende Erreur
            al_draw_text(font, al_map_rgb(0, 0, 0), WIDTH_NUAGE + AXIS_MARGIN, 25, ALLEGRO_ALIGN_LEFT, "Graphe de l'erreur moyenne en fonction des iterations :");

            //Legende Bleu
            al_draw_filled_circle(WIDTH_NUAGE, HEIGHT_ERREUR + HEIGHT_RESEAU  - AXIS_MARGIN, 8, al_map_rgb(0, 0, 255));
            al_draw_text(font, al_map_rgb(0, 0, 0), WIDTH_NUAGE + AXIS_MARGIN * 0.5, HEIGHT_ERREUR + HEIGHT_RESEAU - AXIS_MARGIN * 1.1, ALLEGRO_ALIGN_LEFT, "Valeur faible pour le poids ou le biais");


            //Legende Rouge
            al_draw_filled_circle(WIDTH_NUAGE + AXIS_MARGIN * 4, HEIGHT_ERREUR + HEIGHT_RESEAU  - AXIS_MARGIN, 8, al_map_rgb(255, 0, 0));
            al_draw_text(font, al_map_rgb(0, 0, 0), WIDTH_NUAGE + AXIS_MARGIN * 4.5, HEIGHT_ERREUR + HEIGHT_RESEAU - AXIS_MARGIN * 1.1, ALLEGRO_ALIGN_LEFT, "Valeur élevée pour le poids ou le biais");


//            al_rest(1);
            // Dessiner les axes x et y
            al_draw_line(WIDTH_NUAGE, HEIGHT_ERREUR - AXIS_MARGIN, WIDTH_NUAGE + WIDTH_ERREUR - AXIS_MARGIN, HEIGHT_ERREUR - AXIS_MARGIN, al_map_rgb(0, 0, 0), 2); // Axe des abscisses
            al_draw_line(WIDTH_NUAGE, AXIS_MARGIN, WIDTH_NUAGE, HEIGHT_ERREUR - AXIS_MARGIN, al_map_rgb(0, 0, 0), 2); // Axe des ordonnées

            //            printf("donnees : %f\n", espacement);
            if (espacement_changement == tour){
                espacement_changement *= 10;
                espacement_maximal +=5;
            }
            if (((WIDTH_ERREUR - AXIS_MARGIN)* modulo / (tour)) < espacement_maximal) {
                modulo += 10;
            }


            // Dessiner des graduations sur l'axe des abscisses et les numéroter
            for (int i = 0; i <= tour; i++) {
                if (i % modulo == 0) {
                    int x = WIDTH_NUAGE + i * (WIDTH_ERREUR - AXIS_MARGIN) / (tour);
                    al_draw_line(x, HEIGHT_ERREUR - AXIS_MARGIN - TICK_LENGTH, x, HEIGHT_ERREUR - AXIS_MARGIN + TICK_LENGTH, al_map_rgb(0, 0, 0), 2);
                    char label[10];
                    sprintf(label, "%d", i);
                    al_draw_text(font, al_map_rgb(0, 0, 0), x, HEIGHT_ERREUR - AXIS_MARGIN + TICK_LENGTH + 2,
                                 ALLEGRO_ALIGN_CENTER, label);
                }
            }

            // Dessiner des graduations sur l'axe des ordonnées et les numéroter
            for (int i = 0; i <= 10; i++) {
                int y = HEIGHT_ERREUR - AXIS_MARGIN - i * (HEIGHT_ERREUR - 2 * AXIS_MARGIN) / 10;
                al_draw_line(WIDTH_NUAGE - TICK_LENGTH, y, WIDTH_NUAGE + TICK_LENGTH, y, al_map_rgb(0, 0, 0), 2);
                char label[10];
                sprintf(label, "%.1f", ((float )i)/10);
                al_draw_text(font, al_map_rgb(0, 0, 0), WIDTH_NUAGE - TICK_LENGTH - 20, y - FONT_SIZE / 2, ALLEGRO_ALIGN_RIGHT, label);
            }


            for (int i = 0; i <= tour; ++i) {
                if (i % multiplicateur_dentrainement == 0){
                    if (0 < tab_erreur[i] || tab_erreur[i] < 1){
                        float x = WIDTH_NUAGE + i * (WIDTH_ERREUR - AXIS_MARGIN) / (tour);
                        float y = HEIGHT_ERREUR - AXIS_MARGIN - (tab_erreur[i] * (HEIGHT_ERREUR - 2 * AXIS_MARGIN));
                        al_draw_circle(x, y, 0.5, al_map_rgb(0, 0, 100), 0);
                    }
                }
            }

            //printf("((WIDTH_RESEAU - AXIS_MARGIN) / (my_network->couche[j]->nb_entree + 1)) %d\n", ((WIDTH_RESEAU - AXIS_MARGIN) / (my_network->couche[0]->nb_entree + 1)));

            if (my_network->nb_link < limite_affichage) {
                for (int j = 0; j < my_network->nb_couche; ++j) {
                    for (int i = 0; i < my_network->couche[j]->nb_entree; ++i) {

                        int size = my_network->couche[j]->nb_entree;

                        float min, max;
                        find_min_max(my_network->couche[j]->biais, size, &min, &max);
                        if (min == max) {
                            min = 0.0;
                            max = 1.0;
                        }

                        float x1 = WIDTH_NUAGE + (j) * ((WIDTH_RESEAU) / (my_network->nb_couche + 1));
                        float y1 = HEIGHT_ERREUR + (i + 1) * ((HEIGHT_RESEAU - AXIS_MARGIN) / (my_network->couche[j]->nb_entree + 1));
                        for (int k = 0; k < my_network->couche[j]->nb_neurone; ++k) {
                            float x2 = WIDTH_NUAGE + (j + 1) * ((WIDTH_RESEAU) / (my_network->nb_couche + 1));
                            float y2 = HEIGHT_ERREUR + (k + 1) * ((HEIGHT_RESEAU - AXIS_MARGIN) / (my_network->couche[j]->nb_neurone + 1));
                            al_draw_line(x1, y1, x2, y2, al_map_rgb(255 * ((my_network->couche[j]->weight[k][j] - min) / (max - min)), 0, 255 * (1 - ((my_network->couche[j]->weight[k][j] - min) / (max - min)))), 2);
                        }
                    }
                }



                //affichage entrée
                for (int i = 0; i < my_network->couche[0]->nb_entree; ++i) {
                    float x = WIDTH_NUAGE + (0) * ((WIDTH_RESEAU) / (my_network->nb_couche + 1));
                    float y = HEIGHT_ERREUR + (i + 1) * ((HEIGHT_RESEAU - AXIS_MARGIN) / (my_network->couche[0]->nb_entree + 1));
                    al_draw_filled_circle(x, y, 10, al_map_rgb(255, 255, 255));
                    al_draw_circle(x, y, 10, al_map_rgb(0, 0, 0), 2);
                }

                //affichage des biais
//                printf("=========================\n");
                for(int j = 0; j < my_network->nb_couche; ++j) {
//                    printf("j : %d\n", j);
                    for (int i = 0; i < my_network->couche[j]->nb_neurone; ++i) {
//                        printf("i : %d\n", i);
                        int size = my_network->couche[j]->nb_entree;

                        float min, max;
                        find_min_max(my_network->couche[j]->biais, size, &min, &max);
                        if (min == max) {
                            min = 0.0;
                            max = 1.0;
                        }

                        float x = WIDTH_NUAGE + (j + 1) * ((WIDTH_RESEAU) / (my_network->nb_couche + 1));
                        float y = HEIGHT_ERREUR + (i + 1) * ((HEIGHT_RESEAU - AXIS_MARGIN) / (my_network->couche[j]->nb_neurone + 1));
                        al_draw_filled_circle(x, y, 10, al_map_rgb(255 * ((my_network->couche[j]->biais[i] - min) / (max - min)), 0, 255 * (1 - ((my_network->couche[j]->biais[i] - min) / (max - min)))));
                        al_draw_circle(x, y, 10, al_map_rgb(0, 0, 0), 2);
//                        printf("biais : %f\n", my_network->couche[j]->biais[i]);
                    }
                }

//                printf("=========================\n");

                int decalage_entree_x = 800;
                int decalage_entree_y = 200;

            }


            al_flip_display(); // Met à jour l'affichage
//            printf("tour %d\n", tour);
        }
    }
    // Libération de la mémoire et fermeture d'Allegro
    al_destroy_font(font);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);
    al_destroy_display(display);

    free(tab_erreur);

    return 0;
}


void find_min_max(float array[], int size, float *min, float *max) {
    if (size <= 0) {
        // Gérer le cas où le tableau est vide
        *min = 0;
        *max = 0;
        return;
    }

    *min = array[0];
    *max = array[0];

    for (int i = 1; i < size; i++) {
        if (array[i] < *min) {
            *min = array[i];
        }
        if (array[i] > *max) {
            *max = array[i];
        }
    }
}