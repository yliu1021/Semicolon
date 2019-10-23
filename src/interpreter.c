#include <stdio.h>
#include <stdlib.h>

#include "includes/interpreter.h"

// Op codes
#define MOVE_LEFT         1
#define MOVE_RIGHT        2
#define READ              3   // read from memory to stack
#define WRITE             4   // write from stack to memory
#define LOAD_ONE          5   // load 1 to stack
#define DOUBLE_STACK_TOP  6   // double top element of stack
#define JMP               7   // load function from stack, jump to location
#define CMP               8   // pop cmp value, pop 3 more, push compared value back
#define READ_STDIN_NUM    9   // read from stdin to stack
#define WRITE_STDOUT_NUM  10  // write from stack to stdout
#define ADD               11  // second pop + first pop, push result
#define SUB               12
#define MUL               13
#define DIV               14  // push remainder, then quotient
#define READ_STDIN        15
#define WRITE_STDOUT      16

// Built in functions
#define NOOP              0

#define VERBOSE 0

#define DEBUG_PRINT(op) do {\
  if (VERBOSE) { \
    printf(op); \
    for (size_t __i = 0; __i < stack_pointer; ++__i) { \
      printf(" %d", prog_stack[__i]); \
    } \
    printf("\n"); \
  } \
} while(0)

static unsigned char prog_mem[512];
static unsigned char prog_stack[512];
static size_t memory_pointer = 0;
static size_t stack_pointer = 1;

static void push(unsigned char val) {
  prog_stack[stack_pointer++] = val;
}

static unsigned char pop() {
  if (stack_pointer == 0) {
    fprintf(stderr, "Stack underflow\n");
    exit(5);
  }
  return prog_stack[--stack_pointer];
}

int start_interpreting(int *tokens, size_t size) {
  for (size_t ip = 0; ip < size; ++ip) {
    int token = tokens[ip];
    switch (token) {
      case MOVE_LEFT: {
        DEBUG_PRINT("MOVE_LEFT");
        ++memory_pointer;
      } break;

      case MOVE_RIGHT: {
        DEBUG_PRINT("MOVE_RIGHT");
        --memory_pointer;
      } break;

      case READ: {
        DEBUG_PRINT("READ");
        unsigned char v = prog_mem[memory_pointer];
        push(v);
      } break;

      case WRITE: {
        DEBUG_PRINT("WRITE");
        unsigned char v = pop();
        prog_mem[memory_pointer] = v;
      } break;

      case LOAD_ONE: {
        DEBUG_PRINT("LOAD_ONE");
        push(1);
      } break;

      case DOUBLE_STACK_TOP: {
        DEBUG_PRINT("DOUBLE_STACK_TOP");
        unsigned char v = pop();
        push(2*v);
      } break;

      case JMP: {
        DEBUG_PRINT("JMP");
        unsigned char v = pop();
        switch (v) { // watch out for our special functions
          case NOOP: {
            continue;
          } break;
          
          default: {
            ip = (size_t)v - 2;
          } break;
        }
      } break;

      case CMP: {
        DEBUG_PRINT("CMP");
        char v = pop();
        unsigned char a = pop();
        unsigned char b = pop();
        unsigned char c = pop();
        if (v < 0) {
          push(a);
        } else if (v == 0) {
          push(b);
        } else {
          push(c);
        }
      } break;
      
      case READ_STDIN_NUM: {
        DEBUG_PRINT("READ_STDIN_NUM");
        int c;
        scanf("%d", &c);
        push((unsigned char)c);
      } break;
      
      case WRITE_STDOUT_NUM: {
        DEBUG_PRINT("WRITE_STDOUT_NUM");
        unsigned char c = pop();
        if (VERBOSE) printf("val: %d\n", (int)c);
        printf("%d\n", c);
      } break;

      case ADD: {
        DEBUG_PRINT("ADD");
        unsigned char a = pop();
        unsigned char b = pop();
        push(b + a);
      } break;
      
      case SUB: {
        DEBUG_PRINT("SUB");
        unsigned char a = pop();
        unsigned char b = pop();
        push(b - a);
      } break;
      
      case MUL: {
        DEBUG_PRINT("MUL");
        unsigned char a = pop();
        unsigned char b = pop();
        push(b * a);
      } break;
      
      case DIV: {
        DEBUG_PRINT("DIV");
        unsigned char a = pop();
        unsigned char b = pop();
        push(b % a);
        push(b / a);
      } break;

      case READ_STDIN: {
        DEBUG_PRINT("READ_STDIN");
        unsigned char c = getchar();
        push(c);
      } break;
      
      case WRITE_STDOUT: {
        DEBUG_PRINT("WRITE_STDOUT");
        unsigned char c = pop();
        if (VERBOSE) printf("val: %d\n", (int)c);
        putchar(c);
      } break;

      default: {
        fprintf(stderr, "Invalid op code: %d", token);
        return -1;
      } break;
    }
  }
  return 0;
}