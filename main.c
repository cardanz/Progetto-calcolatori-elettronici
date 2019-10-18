
#include <stdio.h>
#include <pthread.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sysexits.h>
#include "scheduler/Scheduler.h"
#include "strutture/lista_task.h"
#include "strutture/lista_istruzione.h"
#include "utility/lettura_terminale.h"
#include "utility/struttura_thread.h"


int main(int argc, char **argv) {

    //Nomi dei file che dovro leggere / scrivere
    char *input_file = NULL;
    char *input_file_preemption = NULL;
    char *input_file_non_preemption = NULL;

    //inizio a leggere da terminale
    lettura_terminale(argc, argv, &input_file, &input_file_preemption, &input_file_non_preemption);

    FILE *scrittura_preemption = fopen(input_file_preemption, "w");

    if (scrittura_preemption == NULL) {
        perror(input_file_preemption);
        exit(EX_IOERR);
    }

    FILE *scrittura_non_preemption = fopen(input_file_non_preemption, "w");

    if (scrittura_non_preemption == NULL) {
        perror(input_file_non_preemption);
        exit(EX_IOERR);
    }

    FILE *lettura = fopen(input_file, "r");

    if (lettura == NULL) {
        perror(input_file);
        exit(EX_NOINPUT);
    }

    lista_task_t *lista = crea_lista_task();

    TCB_t *task_corrente = NULL;

    char tipo;
    int parametro_1, parametro_2;

    while (fscanf(lettura, "%c,%d,%d\n", &tipo, &parametro_1, &parametro_2) != EOF) {

        if (tipo == 't') {
            int id = parametro_1;
            int arrivo = parametro_2;
            task_corrente = aggiungi_TCB_a_lista(lista, id, arrivo);
        } else {
            int blocco = parametro_1;
            int lunghezza = parametro_2;
            aggiungi_istruzione_a_TCB(task_corrente, blocco, lunghezza);
        }

    }

    fclose(lettura);

    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    struttura_thread_t parametro_scheduler_0;
    struttura_thread_t parametro_scheduler_1;

    parametro_scheduler_0.numero_core = 0;
    parametro_scheduler_0.lista = lista;
    parametro_scheduler_0.mutex = &mutex;
    parametro_scheduler_0.scrittura_non_preemption = scrittura_non_preemption;
    parametro_scheduler_0.scrittura_preemption = scrittura_preemption;

    parametro_scheduler_1.numero_core = 1;
    parametro_scheduler_1.lista = lista;
    parametro_scheduler_1.mutex = &mutex;
    parametro_scheduler_1.scrittura_non_preemption = scrittura_non_preemption;
    parametro_scheduler_1.scrittura_preemption = scrittura_preemption;

    int child_status = 0;
    int ris_fork = fork();

    if (ris_fork < 0) {
        perror("Errore nella creazione della fork ");
        exit(EX_OSERR);
    }

    if (ris_fork == 0) {
        parametro_scheduler_1.tipo_scheduler = SCHEDULER_NOT_PREEMPTIVE;
        parametro_scheduler_0.tipo_scheduler = SCHEDULER_NOT_PREEMPTIVE;

    } else {
        parametro_scheduler_1.tipo_scheduler = SCHEDULER_PREEMPTIVE;
        parametro_scheduler_0.tipo_scheduler = SCHEDULER_PREEMPTIVE;

    }

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, (void *(*)(void *)) &Scheduler, &parametro_scheduler_0);

    Scheduler(&parametro_scheduler_1);

    pthread_join(thread_id, (void *) &parametro_scheduler_0);


    if(ris_fork != 0){
        wait(&child_status);
    }
    while (lista->fine != NULL) {
        eliminazione_task((&lista), lista->inizio->id);
    }

    fclose(scrittura_non_preemption);
    fclose(scrittura_preemption);

    return 0;
}
