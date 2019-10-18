//
// Created by stefano on 01/09/18.
//

#ifndef PROGETTO_CALCOLATORI_SCRITTURA_FILE_H
#define PROGETTO_CALCOLATORI_SCRITTURA_FILE_H


#include "../strutture/lista_task.h"
#include "struttura_thread.h"

char* stato_processo(stato_processo_t stato);
void scrittura_file(struttura_thread_t *parametro_scheduler, unsigned int clock, TCB_t *corrente);

#endif //PROGETTO_CALCOLATORI_SCRITTURA_FILE_H
