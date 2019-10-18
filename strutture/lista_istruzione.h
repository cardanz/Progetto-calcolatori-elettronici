//
// Created by stefano on 01/09/18.
//

#ifndef PROGETTO_CALCOLATORI_LISTA_ISTRUZIONE_H
#define PROGETTO_CALCOLATORI_LISTA_ISTRUZIONE_H

typedef struct istruzione {

    int lunghezza;
    int blocco;
    struct istruzione *prossima;

} istruzione_t; //tipo istruzione_t


typedef struct lista_istruzione {
    istruzione_t *inizio;
    istruzione_t *fine;
} lista_istruzione_t;

#endif //PROGETTO_CALCOLATORI_LISTA_ISTRUZIONE_H
