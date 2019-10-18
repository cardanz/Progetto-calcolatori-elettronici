//
// Created by stefano on 01/09/18.
//

#ifndef PROGETTO_CALCOLATORI_LISTA_TASK_H
#define PROGETTO_CALCOLATORI_LISTA_TASK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include "lista_istruzione.h"

typedef enum aggiornamento {
    NON_LETTO,
    LETTO
} aggiornamento_t;

typedef enum stato_processo {
    NEW,
    READY,
    RUNNING,
    BLOCKED,
    EXIT
} stato_processo_t; // tipo

typedef struct TCB {
    stato_processo_t stato;
    int id;                        // va gestito da noi deve  essere univoco
    istruzione_t *pc;               // puntatore ad istruzione
    int tempo_arrivo;
    lista_istruzione_t *lista_istruzione; //puntatore alla lista delle istruzioni
    struct TCB *prossima;           // collegamento prossima task
    aggiornamento_t agg;
    //non in coda = 0;
    // in coda = 1;
    int in_coda;
} TCB_t;

typedef struct lista_task {
    TCB_t *inizio;
    TCB_t *fine;
} lista_task_t;


lista_task_t *crea_lista_task();

TCB_t *aggiungi_TCB_a_lista(lista_task_t *lista, int id, int arrivo);

TCB_t *aggiungi_TCB_a_coda(lista_task_t *lista, TCB_t *task_esecuzione);

TCB_t *aggiungi_TCB_a_lista_blocked(lista_task_t *lista, TCB_t *task_esecuzione);

TCB_t *aggiungi_TCB_a_lista_ready(lista_task_t *lista, TCB_t *task_esecuzione);


void aggiungi_istruzione_a_TCB(TCB_t *lista, int blocco, int lunghezza);

void eliminazione_task(lista_task_t **inizio, int id_canc);

#endif //PROGETTO_CALCOLATORI_LISTA_TASK_H
