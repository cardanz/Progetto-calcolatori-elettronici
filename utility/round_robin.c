//
// Created by stefano on 01/09/18.
//

#include "round_robin.h"

TCB_t *round_robin(lista_task_t *ready, lista_task_t *coda, TCB_t *task_esecuzione) {
    TCB_t *corrente = ready->inizio;
    TCB_t *esecuzione_bis = malloc(sizeof(TCB_t));
    if (task_esecuzione != NULL) {
        esecuzione_bis->lista_istruzione = task_esecuzione->lista_istruzione;
        esecuzione_bis->pc = task_esecuzione->pc;
        esecuzione_bis->prossima = task_esecuzione->prossima;
        esecuzione_bis->id = task_esecuzione->id;
        esecuzione_bis->stato = task_esecuzione->stato;
        esecuzione_bis->agg = task_esecuzione->agg;
        esecuzione_bis->tempo_arrivo = task_esecuzione->tempo_arrivo;
    }

    while (corrente != NULL) {
        if (corrente->in_coda == 0) {
            aggiungi_TCB_a_coda(coda, corrente);
            corrente->in_coda = 1;
        }

        corrente = corrente->prossima;
    }

    if (task_esecuzione != NULL) {
        eliminazione_task(&(coda), task_esecuzione->id);
    }

    // elimando modifica task esecuzione dopodiche anzichè agg elemento 1 in coda aggiungo 0

    if (task_esecuzione != NULL) {
        aggiungi_TCB_a_coda(coda, esecuzione_bis);
    }
    free(esecuzione_bis);
    return coda->inizio;

}