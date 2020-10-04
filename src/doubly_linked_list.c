#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int value;
  struct node* prev;
  struct node* next;

} node_t;

typedef struct {
  node_t* head;
  node_t* tail;
  unsigned size;

} doubly_linked_list_t;

void swap(node_t** first, node_t** second) {
  node_t* temp = *first;
  *first = *second;
  *second = temp;
}

void print(const doubly_linked_list_t* dll) {
  const node_t* current = dll->head;
  printf("\n[");
  while (NULL != current) {
    printf("%d%s", current->value, NULL != current->next ? " <=> " : "]\n");
    current = current->next;
  }
}

bool insert_node_at_the_beginning(doubly_linked_list_t* dll, const int value) {
  node_t* new_node = (node_t*)malloc(sizeof(node_t));
  if (NULL == new_node)
    return false;
  new_node->value = value;
  new_node->prev = NULL;

  if (NULL == dll->head) {
    new_node->next = NULL;
    dll->head = new_node;
    dll->tail = new_node;
    dll->size = 1U;
  } else {
    new_node->next = dll->head;
    dll->head->prev = new_node;
    dll->head = new_node;
    ++dll->size;
  }

  return true;
}

bool insert_node_at_the_end(doubly_linked_list_t* dll, const int value) {
  node_t* new_node = (node_t*)malloc(sizeof(node_t));
  if (NULL == new_node)
    return false;
  new_node->value = value;
  new_node->next = NULL;

  if (NULL == dll->head) {
    new_node->prev = NULL;
    dll->head = new_node;
    dll->tail = new_node;
    dll->size = 1U;
  } else {
    new_node->prev = dll->tail;
    dll->tail->next = new_node;
    dll->tail = new_node;
    ++dll->size;
  }

  return true;
}

bool insert_node_before_specified_position(doubly_linked_list_t* dll,
                                           const int value,
                                           const unsigned pos) {
  if (NULL == dll->head) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    if (NULL == new_node)
      return false;
    new_node->value = value;
    new_node->prev = NULL;
    new_node->next = NULL;
    dll->head = dll->tail = new_node;
    dll->size = 1U;
    return true;
  }

  if (0U == pos || pos > dll->size)
    return false;

  if (1U == pos)
    return insert_node_at_the_beginning(dll, value);

  if (pos == dll->size)
    return insert_node_at_the_end(dll, value);

  unsigned current_pos = 1U;
  node_t* next_node = dll->head;
  while (current_pos < pos) {
    next_node = next_node->next;
    ++current_pos;
  }

  node_t* new_node = (node_t*)malloc(sizeof(node_t));
  if (NULL == new_node)
    return false;

  new_node->value = value;
  new_node->next = next_node;
  new_node->prev = next_node->prev;
  next_node->prev->next = new_node;
  next_node->prev = new_node;
  ++dll->size;

  return true;
}

bool insert_node_after_specified_position(doubly_linked_list_t* dll,
                                          const int value,
                                          const unsigned pos) {
  if (NULL == dll->head) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    if (NULL == new_node)
      return false;
    new_node->value = value;
    new_node->prev = NULL;
    new_node->next = NULL;
    dll->head = dll->tail = new_node;
    dll->size = 1U;
    return true;
  }

  if (0U == pos || pos > dll->size)
    return false;

  if (pos == dll->size)
    return insert_node_at_the_end(dll, value);

  unsigned current_pos = 1U;
  node_t* prev_node = dll->head;
  while (current_pos < pos) {
    prev_node = prev_node->next;
    ++current_pos;
  }

  node_t* new_node = (node_t*)malloc(sizeof(node_t));
  if (NULL == new_node)
    return false;
  new_node->value = value;
  new_node->next = prev_node->next;
  new_node->prev = prev_node;
  prev_node->next->prev = new_node;
  prev_node->next = new_node;
  ++dll->size;
  return true;
}

bool delete_first_node(doubly_linked_list_t* dll) {
  if (NULL == dll->head)
    return false;

  node_t* current = dll->head;
  dll->head = dll->head->next;
  dll->head->prev = current->next = NULL;
  free(current);

  if (NULL == dll->head) {
    dll->tail = NULL;
    dll->size = 0U;
  }

  return true;
}

bool delete_last_node(doubly_linked_list_t* dll) {
  if (NULL == dll->tail)
    return false;

  node_t* current = dll->tail;
  dll->tail = dll->tail->prev;
  dll->tail->next = current->prev = NULL;
  free(current);

  if (NULL == dll->tail) {
    dll->head = NULL;
    dll->size = 0U;
  }

  return true;
}

bool delete_node_at_specified_position(doubly_linked_list_t* dll,
                                       const unsigned pos) {
  if (NULL == dll->head || 0U == pos || pos > dll->size)
    return false;

  if (1U == pos)
    return delete_first_node(dll);

  if (pos == dll->size)
    return delete_last_node(dll);

  node_t *current = dll->head, *prev;
  unsigned i = 1U;
  while (i < pos) {
    prev = current;
    current = current->next;
    ++i;
  }

  if (dll->tail == current)
    return delete_last_node(dll);

  prev->next = current->next;
  current->next->prev = prev;
  current->prev = current->next = NULL;
  free(current);
  return true;
}

void destroy_doubly_linked_list(doubly_linked_list_t* dll) {
  node_t* current_node = dll->head;

  while (current_node != NULL) {
    node_t* next_node = current_node->next;
    current_node->prev = current_node->next = NULL;
    free(current_node);
    current_node = next_node;
  }

  dll->head = NULL;
  dll->tail = NULL;
  dll->size = 0U;
}

bool reverse_doubly_linked_list_in_place(doubly_linked_list_t* dll) {
  swap(&(dll->head), &(dll->tail));
  node_t* current = dll->head;
  while (NULL != current) {
    swap(&(current->prev), &(current->next));
    current = current->next;
  }

  return true;
}

doubly_linked_list_t create_reversed_copy_of_specified_doubly_linked_list(
    const doubly_linked_list_t* dll) {
  doubly_linked_list_t reversed_dll = {0};
  const node_t* current = dll->head;
  while (NULL != current) {
    if (!insert_node_at_the_beginning(&reversed_dll, current->value)) {
      destroy_doubly_linked_list(&reversed_dll);
      return reversed_dll;
    }

    current = current->next;
  }

  return reversed_dll;
}

int main() {
  doubly_linked_list_t dll = {0};

  insert_node_at_the_beginning(&dll, 1);
  insert_node_at_the_end(&dll, 3);
  insert_node_before_specified_position(&dll, 2, 2);
  insert_node_at_the_end(&dll, 5);
  insert_node_after_specified_position(&dll, 3, 4);
  insert_node_at_the_end(&dll, 7);
  insert_node_at_the_end(&dll, 8);
  insert_node_at_the_beginning(&dll, 0);

  print(&dll);

  delete_node_at_specified_position(&dll, 3);

  print(&dll);

  if (!reverse_doubly_linked_list_in_place(&dll)) {
    printf(
        "Error occurred during reversing specified doubly linked list in "
        "place!\n");
  } else {
    print(&dll);
  }

  doubly_linked_list_t dll2 =
      create_reversed_copy_of_specified_doubly_linked_list(&dll);

  print(&dll2);

  destroy_doubly_linked_list(&dll);
  destroy_doubly_linked_list(&dll2);

  return 0;
}
