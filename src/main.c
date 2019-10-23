#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

#include "includes/tokenizer.h"
#include "includes/interpreter.h"

#define MEMORY_ERROR 1
#define IO_ERROR 2
#define CMD_LINE_ERROR 3

#define INVALID_OP_CODE_ERR 4

char prog_mem[256];
char *prog_inst;

int main(int argc, char *argv[]) {
  size_t read_size = 1024;
  size_t prog_size = 0;
  prog_inst = (char*)malloc(read_size * sizeof(char));
  if (prog_inst == NULL) {
    fprintf(stderr, "Unable to allocate memory for program instructions\n");
    exit(MEMORY_ERROR);
  }

  // read everything into prog_inst
  int fd;
  if (argc == 1) {
    fd = STDIN_FILENO;
  } else if (argc == 2) {
    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
      fprintf(stderr, "Cannot open file %s: %s\n", argv[1], strerror(errno));
      exit(IO_ERROR);
    }
  } else {
    fprintf(stderr, "Invalid command line arguments\n");
    exit(CMD_LINE_ERROR);
  }

  for (;;) {
    ssize_t bytes_read = read(fd, prog_inst+prog_size, read_size);
    if (bytes_read < 0) {
      perror("Unable to read instructions");
      exit(IO_ERROR);
    }
    prog_size += bytes_read;
    if ((size_t)bytes_read < read_size) break;
    prog_inst = (char*)realloc(prog_inst, (prog_size + read_size) * sizeof(char));
    if (prog_inst == NULL) {
      fprintf(stderr, "Unable to allocate memory for program instructions\n");
      exit(MEMORY_ERROR);
    }
  }

  if (fd != STDIN_FILENO) {
    if (close(fd) < 0) {
      fprintf(stderr, "Cannot close file %s: %s\n", argv[1], strerror(errno));
      exit(IO_ERROR);
    }
  }

  size_t token_size;
  int *tokens = tokenize(prog_inst, prog_size, &token_size);
  if (tokens == NULL) {
    fprintf(stderr, "Out of memory to create tokens\n");
    exit(MEMORY_ERROR);
  }

  int r = start_interpreting(tokens, token_size);

  if (r == -1) {
    fprintf(stderr, "Invalid op code encountered\n");
    exit(INVALID_OP_CODE_ERR);
  }

  free(tokens);
  free(prog_inst);
  return 0;
}
