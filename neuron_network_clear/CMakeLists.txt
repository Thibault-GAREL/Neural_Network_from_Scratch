cmake_minimum_required(VERSION 3.26)
project(neuron_network_clear C)

set(CMAKE_C_STANDARD 23)

add_executable(neuron_network_clear main.c
        creator.c
        creator.h
        structure.h
        1_fwd_propagation.c
        1_fwd_propagation.h
        2_back_propagation.c
        2_back_propagation.h
        calcul.c
        calcul.h
        training.c
        training.h
        affichage_tableau.c
        affichage_tableau.h)

target_link_libraries(neuron_network_clear -lmingw32 -lallegro-5.0.10-monolith-md-debug)
