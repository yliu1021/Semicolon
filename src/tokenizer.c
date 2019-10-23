#include "includes/tokenizer.h"

int *tokenize(const char* prog_inst, size_t size, size_t *tk_size) {
  int *tokens;
  size_t token_capacity = 10;
  size_t token_size = 0;
  tokens = (int*)malloc(token_capacity * sizeof(int));
  if (tokens == NULL) return NULL;

  int token = 0;
  for (size_t i = 0; i < size; ++i) {
    if (prog_inst[i] == ';') token++; // we saw another ;
    else if (token != 0) {
      // we saw something that's not a ; and we have a token to push
      tokens[token_size++] = token;
      if (token_size == token_capacity) {
        token_capacity *= 2;
        tokens = (int*)realloc(tokens, token_capacity * sizeof(int));
        if (tokens == NULL) return NULL;
      }
      token = 0;
    }
  }
  *tk_size = token_size;
  return tokens;
}