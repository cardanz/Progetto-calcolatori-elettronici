//
// Created by stefano on 01/09/18.
//

#include "lettura_terminale.h"

void stampa_help() {
    printf("-op | --output-preemption: il file di output con i risultati dello scheduler con preemption\n"
           "-on | --output-no-preemption: il file di output con i risultati dello scheduler senza preemption\n"
           "-i  | --input: il file di input contenente la lista dei task, al termine della scansione del file, i task devono essere inviati ai due scheduler nelle stesso ordine in cui sono stati letti.\n"
           "-h  | --help: stampa l’helper di come utilizzare il programma\n");
}

void lettura_terminale(int argc, char **argv, char **input_file, char **input_file_preemption, char **input_file_non_preemption) {

    const char *const opzione_corta = "o:i:n:p:h";

    const struct option opzione_lunga[] = {
            {"output",               1, NULL, 'o'},
            {"input",                1, NULL, 'i'},
            {"output-no-preemption", 1, NULL, 'n'},
            {"output-preemption",    1, NULL, 'p'},
            {"help",                 0, NULL, 'h'},
            {NULL,                   0, NULL, 0}
    };

    int prossima_operazione;

    do {
        prossima_operazione = getopt_long(argc, argv, opzione_corta, opzione_lunga, NULL);
        switch (prossima_operazione) {
            case 'h':
                stampa_help();
                break;
            case 'o':
                if (strcmp(optarg, "n") == 0) {
                    *input_file_non_preemption = argv[optind];
                    printf("File di output dello scheduler non preemptive: %s\n", *input_file_non_preemption);

                } else if (strcmp(optarg, "p") == 0) {
                    *input_file_preemption = argv[optind];
                    printf("File di output dello scheduler preemptive: %s\n", *input_file_preemption);

                } else {
                    fprintf(stderr, "Lettera diversa da 'n' o 'p' , operazione non valida\n");
                    exit(EX_USAGE);
                }
                break;
            case 'n':
                *input_file_non_preemption = optarg;
                printf("File di output dello scheduler non preemptive: %s\n", *input_file_non_preemption);
                break;
            case 'p':
                *input_file_preemption = optarg;
                printf("File di output dello scheduler preemptive: %s\n", *input_file_preemption);
                break;
            case 'i':
                *input_file = optarg;
                printf("File di input: %s\n", *input_file);
                break;
            case '?' :
                printf("Operazione non valida\n");
                stampa_help();
                break;
            case -1:
                break;
            default:
                stampa_help();
        }
    } while (prossima_operazione != -1);
}