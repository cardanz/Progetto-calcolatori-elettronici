//
// Created by stefano on 01/09/18.
//

#include "scrittura_file.h"

char *stato_processo(stato_processo_t stato) {
    switch (stato) {
        case NEW:
            return "new";
        case READY:
            return "ready";
        case BLOCKED:
            return "blocked";
        case RUNNING:
            return "running";
        case EXIT:
            return "exit";
        default:
            fprintf(stderr,"Stato del processo non riconosciuto\n");
            exit(1);
    }
}

void scrittura_file(struttura_thread_t *parametro_scheduler, unsigned int clock, TCB_t *corrente) {

    char *stato_stampa = stato_processo(corrente->stato);


    if (parametro_scheduler->tipo_scheduler == SCHEDULER_PREEMPTIVE) {
        fprintf(parametro_scheduler->scrittura_preemption, "core%d,%d,%d,%s\n", parametro_scheduler->numero_core,
                clock, corrente->id, stato_stampa);
    } else {
        fprintf(parametro_scheduler->scrittura_non_preemption, "core%d,%d,%d,%s\n",
                parametro_scheduler->numero_core, clock, corrente->id, stato_stampa);
    }
}