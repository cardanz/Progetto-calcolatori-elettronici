//
// Created by stefano on 01/09/18.
//

#ifndef PROGETTO_CALCOLATORI_LETTURA_TERMINALE_H
#define PROGETTO_CALCOLATORI_LETTURA_TERMINALE_H

#include <stddef.h>
#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

void stampa_help();

void lettura_terminale(int argc, char **argv, char **input_file, char **input_file_preemption,
                       char **input_file_non_preemption);

#endif //PROGETTO_CALCOLATORI_LETTURA_TERMINALE_H
