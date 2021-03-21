#include "../include/stack.h"

#include <stdio.h>

create_stack_of(int)

    int main() {
  stack_t(int) s1;

  stack_init(&s1);

  stack_push(&s1, 1);
  stack_push(&s1, 2);
  stack_push(&s1, 3);
  stack_push(&s1, 4);
  stack_push(&s1, 5);

  stack_print(&s1, "|", "\n[", "]\n");

  int top;
  if (stack_top(&s1, &top)) {
    printf("Top element of stack s1 = %d\n", top);
  } else {
    printf("Stack is empty!");
  }

  stack_pop(&s1);

  stack_print(&s1, "|", "\n[", "]\n");

  if (stack_top(&s1, &top)) {
    printf("Top element of stack s1 = %d\n", top);
  } else {
    printf("Stack is empty!");
  }

  while (!stack_empty(&s1)) {
    int current;
    stack_top(&s1, &current);
    stack_pop(&s1);
    printf("Current top element of stack s1 = %d\n", current);
  }

  stack_destroy(&s1);

  return 0;
}
