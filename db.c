// database written in C, a clone of sqlite

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  sqlite starts a read-execute-print loop when you start it from the command line
  to do this, our main function will have an infinite loop that prints the prompt, 
  which gets the input to process:
*/
int main(int argc, char* argv[]) {
  InputBuffer* input_buffer = new_input_buffer();
  while (true) {
    print_prompt();
    read_input(input_buffer);

    if (strcmp(input_buffer->buffer, ".exit") == 0) {
      close_input_buffer(input_buffer);
      exit(EXIT_SUCCESS);
    } else {
      printf("Unrecognized command '%s'.\n", input_buffer->buffer);
    }
  }
}
/*
  now we have to define InputBuffer as a small wrapper 
  around the state we need to store with getLine().
*/
typedef struct {
  char* buffer;
  size_t buffer_length;
  ssize_t input_length;
} InputBuffer;

InputBuffer* new_input_buffer() {
  InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
  input_buffer->buffer = NULL;
  input_buffer->buffer_length = 0;
  input_buffer->input_length = 0;

  return input_buffer;
}

//hello world