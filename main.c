#include "file_specter.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "USAGE: FileSpecter PATH\n");
        exit(EXIT_FALIURE);
    } 
    run_filespecter(argv);
    exit(EXIT_SUCCESS);
}
