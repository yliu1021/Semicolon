#ifndef TOKENIZE_H
#define TOKENIZE_H

#include <stdlib.h>

/*
Returns an array of tokens as a integer array
Note that this array must be freed by the caller of this function
*/
extern int *tokenize(const char* prog_inst, size_t size, size_t *tk_size);

#endif
