//
// Created by stefano on 01/09/18.
//

#ifndef PROGETTO_CALCOLATORI_SCHEDULER_H
#define PROGETTO_CALCOLATORI_SCHEDULER_H

#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "../strutture/lista_istruzione.h"
#include "../strutture/lista_task.h"
#include "../utility/struttura_thread.h"
#include "../utility/scrittura_file.h"
#include "../utility/FCFS.h"
#include "../utility/round_robin.h"


void Scheduler(struttura_thread_t *parametro_scheduler);


#endif //PROGETTO_CALCOLATORI_SCHEDULER_H
