//
// Created by stefano on 01/09/18.
//

#ifndef PROGETTO_CALCOLATORI_STRUTTURA_THREAD_H
#define PROGETTO_CALCOLATORI_STRUTTURA_THREAD_H

#include "../strutture/lista_task.h"
#include <pthread.h>

typedef enum tipo_scheduler {
    SCHEDULER_PREEMPTIVE,
    SCHEDULER_NOT_PREEMPTIVE

} tipo_scheduler_t;

typedef struct struttura_thread {
    int numero_core; //equivale all'identificatore del thread
    tipo_scheduler_t tipo_scheduler;
    lista_task_t *lista;
    FILE *scrittura_non_preemption;
    FILE *scrittura_preemption;
    pthread_mutex_t *mutex;
} struttura_thread_t;


#endif //PROGETTO_CALCOLATORI_STRUTTURA_THREAD_H
