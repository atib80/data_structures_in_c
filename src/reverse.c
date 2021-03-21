#include "../include/stack.h"
#include "../include/reverse.h"
#include <stdio.h>
#include <stdlib.h>

create_stack_of(char)

    void print_file_contents_in_reverse(FILE* fp) {
  const int BUFSIZE = 1024;
  char buffer[BUFSIZE];

  stack_t(char) s;
  stack_init(&s);

  while (NULL != fgets(buffer, BUFSIZE, fp)) {
    for (unsigned i = 0; 0 != buffer[i]; ++i) {
      stack_push(&s, buffer[i]);
    }
  }

  char ch;

  if (!stack_empty(&s) && stack_top(&s, &ch) && '\n' != ch) {
    stack_push(&s, '\n');
  }

  while (!stack_empty(&s)) {
    char ch;
    stack_top(&s, &ch);
    putchar(ch);
    stack_pop(&s);
  }

  putchar('\n');

  stack_destroy(&s);
}
