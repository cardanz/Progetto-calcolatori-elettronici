//
// Created by stefano on 01/09/18.
//

#include "FCFS.h"

TCB_t *FCFS(lista_task_t *ready) {
    TCB_t *corrente = ready->inizio;
    TCB_t *scelto = ready->inizio;
    while (corrente != NULL) {
        if (corrente->tempo_arrivo < scelto->tempo_arrivo) {
            scelto = corrente;
        }
        corrente = corrente->prossima;
    }
    return scelto;
}
