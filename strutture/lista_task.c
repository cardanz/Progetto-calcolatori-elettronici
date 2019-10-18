//
// Created by stefano on 01/09/18.
//

#include "lista_task.h"

lista_task_t *crea_lista_task() {
    lista_task_t *lista = malloc(sizeof(lista_task_t));
    lista->fine = NULL;
    lista->inizio = NULL;

    return lista;
}

TCB_t *aggiungi_TCB_a_lista(lista_task_t *lista, int id, int arrivo) {
    TCB_t *corrente = malloc(sizeof(TCB_t));
    lista_istruzione_t *istruzioni = malloc(sizeof(lista_istruzione_t));

    istruzioni->inizio = NULL;
    istruzioni->fine = NULL;

    corrente->agg = NON_LETTO;
    corrente->stato = NEW;
    corrente->id = id;
    corrente->pc = NULL;
    corrente->tempo_arrivo = arrivo;
    corrente->lista_istruzione = istruzioni;
    corrente->prossima = NULL;
    corrente->in_coda = 0;

    if (lista->inizio == NULL) {
        lista->inizio = corrente;
        lista->fine = corrente;
    } else {
        TCB_t *precedente = lista->fine;
        precedente->prossima = corrente;
        lista->fine = corrente;
    }

    return corrente;
}

TCB_t *aggiungi_TCB_a_coda(lista_task_t *lista, TCB_t *task_esecuzione) {

    TCB_t *corrente = malloc(sizeof(TCB_t));

    corrente->stato = READY;

    corrente->id = task_esecuzione->id;


    corrente->tempo_arrivo = task_esecuzione->tempo_arrivo;
    corrente->lista_istruzione = task_esecuzione->lista_istruzione;
    corrente->pc = task_esecuzione->pc;
    corrente->lista_istruzione = task_esecuzione->lista_istruzione;
    corrente->agg = task_esecuzione->agg;
    corrente->prossima = NULL;
    corrente->in_coda = 1;

    if (lista->inizio == NULL) {
        lista->inizio = corrente;
        lista->fine = corrente;
    } else {
        TCB_t *precedente = lista->fine;
        precedente->prossima = corrente;
        lista->fine = corrente;
    }

    return corrente;
}

/// problema mi blocco ed esco subito per il program  counter che non viene incrementato
/// penserei quasi a distinguere due funzioni con blocked e redi perchè qui ogni  tanto
/// vado avanti e ogni tanto no
TCB_t *aggiungi_TCB_a_lista_ready(lista_task_t *lista, TCB_t *task_esecuzione) {

    TCB_t *corrente = malloc(sizeof(TCB_t));

    if (task_esecuzione->stato == NEW) {
        corrente->stato = READY;
        corrente->pc = task_esecuzione->pc;

    }
    if (task_esecuzione->stato == BLOCKED) {
        corrente->stato = READY;
        corrente->pc = task_esecuzione->pc;
    }

    corrente->id = task_esecuzione->id;
    corrente->agg = task_esecuzione->agg;
    corrente->tempo_arrivo = task_esecuzione->tempo_arrivo;
    corrente->lista_istruzione = task_esecuzione->lista_istruzione;
    corrente->prossima = NULL;
    corrente->in_coda = 0;

    if (lista->inizio == NULL) {
        lista->inizio = corrente;
        lista->fine = corrente;
    } else {
        TCB_t *precedente = lista->fine;
        precedente->prossima = corrente;
        lista->fine = corrente;
    }

    return corrente;
}

TCB_t *aggiungi_TCB_a_lista_blocked(lista_task_t *lista, TCB_t *task_esecuzione) {

    TCB_t *corrente = malloc(sizeof(TCB_t));

    if (task_esecuzione->stato == RUNNING) {
        corrente->stato = BLOCKED;
        ///facendo cosi incrementiamo  il pc cioe passiamo alla prossima istruzione
        corrente->pc = task_esecuzione->pc->prossima;
    }

    corrente->id = task_esecuzione->id;
    corrente->agg = task_esecuzione->agg;
    corrente->tempo_arrivo = task_esecuzione->tempo_arrivo;
    corrente->lista_istruzione = task_esecuzione->lista_istruzione;
    corrente->prossima = NULL;
    corrente->in_coda = 0;

    if (lista->inizio == NULL) {
        lista->inizio = corrente;
        lista->fine = corrente;
    } else {
        TCB_t *precedente = lista->fine;
        precedente->prossima = corrente;
        lista->fine = corrente;
    }

    return corrente;
}


void aggiungi_istruzione_a_TCB(TCB_t *lista, int blocco, int lunghezza) {
    lista_istruzione_t *istruzioni = lista->lista_istruzione;

    istruzione_t *istruzione = malloc(sizeof(istruzione_t));
    istruzione->prossima = NULL;
    istruzione->blocco = blocco;
    istruzione->lunghezza = lunghezza;

    if (istruzioni->inizio == NULL) {
        istruzioni->inizio = istruzione;
        istruzioni->fine = istruzione;
    } else {
        istruzione_t *precedente = istruzioni->fine;
        precedente->prossima = istruzione;
        istruzioni->fine = istruzione;
    }
}

void eliminazione_task(lista_task_t **lista, int id_canc) {

    TCB_t *corrente = (*lista)->inizio;
    TCB_t *temporaneo = NULL;
    TCB_t *precedente = NULL;
    int bit_control = 0;
    //controllo se la lista è vuota ,nel caso lo fosse esco con messaggio di errore
    if ((*lista)->inizio == NULL) {
        fprintf(stderr, "Nessun elemento nella lista");
        exit(1);
    }

    while (corrente != NULL) {

        //eliminazione primo elemento
        if (id_canc == corrente->id && corrente == (*lista)->inizio) {
            (*lista)->inizio = ((*lista)->inizio)->prossima;
            corrente->prossima = NULL;
            // se rimangono zero elementi fine deve diventare null
            if ((*lista)->inizio == NULL)
                (*lista)->fine = NULL;
            free(corrente);
            bit_control = 1;
            break;
        } else {
            if (id_canc == corrente->id) {
                temporaneo = corrente;
                precedente->prossima = corrente->prossima;
                if (corrente->prossima == NULL)
                    (*lista)->fine = precedente;
                free(temporaneo);
                bit_control = 1;
            }
        }

        precedente = corrente;
        corrente = corrente->prossima;

    }

    if (bit_control == 0) {
        // Non utilizzo la perror perche essa risponde solamente agli errori di sistema, quindi in questo caso uso la fprintf su stderr
        fprintf(stderr, "Id_elemento non trovato");
        exit(EX_DATAERR);
    }

}
