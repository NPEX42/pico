#include "pico/utils.h"
#include <stdio.h>


// Opens & Reads a text file. Returns NULL if the file couldn't be opened
// and a char* containing a null-terminated string of the file contents.
// Callee is responsible for the returned buffer.
char* pico_read_text(const char* path) {
    U64 length = pico_file_size(path);
    FILE* file = fopen(path, "rb");
    if (!file) {
        return NULL;
    }
    char* buffer = malloc(length + 1);
    memset(buffer, 0, length + 1);
    fread(buffer, length, 1, file);
    fclose(file);
    return buffer;
}

// Get the size in bytes of a file.
// Returns 0 if not found.
U64 pico_file_size(const char* path) {
    FILE* file = fopen(path, "rb");
    if (!file) {
        return 0;
    }
    fseek(file, 0, SEEK_END);
    U64 size = ftell(file);
    fclose(file);

    return size;
}