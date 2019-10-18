//
// Created by stefano on 01/09/18.
//

#include "Scheduler.h"

void Scheduler(struttura_thread_t *parametro_scheduler) {

    unsigned int clock = 0;
    unsigned int bit_controllo = 0;
    TCB_t *tcb_corrente = parametro_scheduler->lista->inizio;

    lista_task_t *ready = crea_lista_task();
    lista_task_t *blocked = crea_lista_task();
    TCB_t *corrente_blocked = blocked->inizio;
    TCB_t *task_esecuzione = NULL;
    istruzione_t *istruzione_in_esecuzione = NULL;
    lista_task_t *coda = crea_lista_task();
    unsigned int quanto = 50;
    unsigned int progresso_istruzione = 0;

    while (1) {
        while (tcb_corrente != NULL && tcb_corrente->tempo_arrivo <= clock) {

            pthread_mutex_lock(parametro_scheduler->mutex);

            if (tcb_corrente->stato == NEW) {
                aggiungi_TCB_a_lista_ready(ready, tcb_corrente);
                tcb_corrente->stato = READY;
                scrittura_file(parametro_scheduler, clock, tcb_corrente);
            }

            tcb_corrente = tcb_corrente->prossima;
            pthread_mutex_unlock(parametro_scheduler->mutex);
        }

        while (corrente_blocked != NULL) {
            if (corrente_blocked->tempo_arrivo <= clock) {
                aggiungi_TCB_a_lista_ready(ready, corrente_blocked);
                corrente_blocked->stato = READY;
                scrittura_file(parametro_scheduler, clock, corrente_blocked);
                eliminazione_task(&(blocked), corrente_blocked->id);
            }
            /// come sopra possibile controllo guarda riga 42
            corrente_blocked = corrente_blocked->prossima;
        }

        /// scelta processo da eseguire
        // valuta se aggiungere condizione su bit di controllo
        if (ready->inizio == NULL && blocked->inizio == NULL && tcb_corrente == NULL && coda->inizio == NULL) {
            break; //condizione d'uscita dal file

        }

        if (bit_controllo == 0 &&
            (ready->inizio != NULL || parametro_scheduler->tipo_scheduler == SCHEDULER_PREEMPTIVE)) {
            // modifca condizione if per scheduler pre
            /// per quanto riguarda il round robin posso forzare a zero il
            /// bit di controllo dopo il dovuto quanto di tempo controllato con contatore
            // occore scegliere il prossimo task da eseguire tramite algoritmi
            if (parametro_scheduler->tipo_scheduler == SCHEDULER_PREEMPTIVE) {
                task_esecuzione = round_robin(ready, coda, task_esecuzione);
                progresso_istruzione = 0;
                if (task_esecuzione != NULL)
                    istruzione_in_esecuzione = task_esecuzione->pc;
            } else if (parametro_scheduler->tipo_scheduler == SCHEDULER_NOT_PREEMPTIVE) {

                task_esecuzione = FCFS(ready);
                istruzione_in_esecuzione = task_esecuzione->pc;
            }
        }
        /// condizione su coda
        if (task_esecuzione != NULL && task_esecuzione->pc == NULL && task_esecuzione->agg == LETTO) {

            task_esecuzione->stato = RUNNING;   /// altrimenti passavo direttamente da ready a bloked
            scrittura_file(parametro_scheduler, clock, task_esecuzione);
            task_esecuzione->stato = EXIT;
            scrittura_file(parametro_scheduler, clock, task_esecuzione);
            eliminazione_task(&(ready), task_esecuzione->id);
            if (parametro_scheduler->tipo_scheduler == SCHEDULER_PREEMPTIVE)
                eliminazione_task(&(coda), task_esecuzione->id);
            task_esecuzione = NULL;
            istruzione_in_esecuzione = NULL;
            bit_controllo = 0;
        }

        if (task_esecuzione != NULL) {
            if (task_esecuzione->pc == NULL && task_esecuzione->agg == NON_LETTO) {
                istruzione_in_esecuzione = task_esecuzione->lista_istruzione->inizio;
                task_esecuzione->pc = istruzione_in_esecuzione;
                task_esecuzione->agg = LETTO;
            }
            if (task_esecuzione->stato != RUNNING) {
                task_esecuzione->stato = RUNNING;
                scrittura_file(parametro_scheduler, clock, task_esecuzione);
                // scrivi su file il cambiamento ( passagggio ready ->running)
            }

            ///NON BLOCCANTE
            if (istruzione_in_esecuzione->blocco == 0) {
                if (parametro_scheduler->tipo_scheduler ==
                    SCHEDULER_PREEMPTIVE) // questa op non è nec. in caso di scheduler non_pre
                    progresso_istruzione++;
                istruzione_in_esecuzione->lunghezza--;
                bit_controllo = 1;
                if (istruzione_in_esecuzione->lunghezza == 0) {
                    if (istruzione_in_esecuzione->prossima != NULL) {
                        istruzione_in_esecuzione = istruzione_in_esecuzione->prossima;
                        task_esecuzione->pc = istruzione_in_esecuzione;
                        /// potrebbe servire agg. pc perchè in caso pre_Emption devono tenerne conto
                    } else {
                        task_esecuzione->stato = EXIT;
                        scrittura_file(parametro_scheduler, clock,
                                       task_esecuzione); //scrittura su file , aggiorno task passa da running a exit
                        eliminazione_task(&(ready), task_esecuzione->id);

                        bit_controllo = 0;
                        if (parametro_scheduler->tipo_scheduler == SCHEDULER_PREEMPTIVE) {
                            progresso_istruzione = 0;
                            eliminazione_task(&(coda), task_esecuzione->id);

                        }
                        task_esecuzione = NULL;
                        istruzione_in_esecuzione = NULL;
                        /// se ho completato il task oltre a rischedulare devo azzerare il il quanto

                    }
                    // lungheza dell ultima istruzione esaurita , quindi l'abbiamo eseguita tutta
                }
            }
               ///BLOCCAANTE
            else {
                // warning , valuta anche -1????
                srand((unsigned int) time(0));
                task_esecuzione->tempo_arrivo = clock + (rand() % ((istruzione_in_esecuzione->lunghezza) - 1) + 1);
                aggiungi_TCB_a_lista_blocked(blocked, task_esecuzione);
                task_esecuzione->stato = BLOCKED;
                scrittura_file(parametro_scheduler, clock, task_esecuzione);
                ///attenzione all'eliminazione task, sperando che eliminni solamente il puntatore della lista e non tutta la lista
                eliminazione_task(&(ready), task_esecuzione->id);
                bit_controllo = 0;
                if (parametro_scheduler->tipo_scheduler == SCHEDULER_PREEMPTIVE) {
                    progresso_istruzione = 0;
                    eliminazione_task(&(coda), task_esecuzione->id);
                }
                task_esecuzione = NULL;
                istruzione_in_esecuzione = NULL;

                /// se ho istruzione bloccante oltre a rischedulare devo azzerare il il quanto
            }
        }
        corrente_blocked = blocked->inizio;
        /// se lo schedelure e preempitive occorre mettere l'istruzione in coda che passa da runnin a ready perchè non
        /// è bloccante quindi loggo questo evento sul file , dopodichè azzero il contatore del quanto
        // era messo dopo 'laumneto del clock ma in realtà quella è l'ultima op.cosi è +corretto
        if (progresso_istruzione == quanto && parametro_scheduler->tipo_scheduler == SCHEDULER_PREEMPTIVE &&
            istruzione_in_esecuzione != NULL) {
            task_esecuzione->stato = READY;
            scrittura_file(parametro_scheduler, clock, task_esecuzione);
            bit_controllo = 0;
            progresso_istruzione = 0;
        }
        clock++;
    } // fine while "INFINITO"
    printf("Finita funzione Scheduler %d\n", parametro_scheduler->numero_core);
}
