//
// Created by stefano on 01/09/18.
//

#ifndef PROGETTO_CALCOLATORI_ROUND_ROBIN_H
#define PROGETTO_CALCOLATORI_ROUND_ROBIN_H

#include "../strutture/lista_task.h"

TCB_t *round_robin(lista_task_t *ready, lista_task_t *coda, TCB_t *task_esecuzione);

void swap(TCB_t *a, TCB_t *b);

void bubbleSort(lista_task_t *coda);

#endif //PROGETTO_CALCOLATORI_ROUND_ROBIN_H
