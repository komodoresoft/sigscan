#ifndef SIGSCAN_FILE
#define SIGSCAN_FILE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

size_t get_file_size(char *filename, FILE *file);
char *read_file(char *filename, size_t *size);

#endif // SIGSCAN_FILE