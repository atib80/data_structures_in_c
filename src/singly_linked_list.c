#include "../include/singly_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

void print(const sll_t* sll) {
  const node_t* current = sll->head;
  printf("\n[");
  while (NULL != current) {
    printf("%d%s", current->value, NULL != current->next ? " -> " : "]\n");
    current = current->next;
  }
}

bool insert_node_at_the_beginning(sll_t* sll, const int value) {
  node_t* new_node = (node_t*)malloc(sizeof(node_t));
  if (NULL == new_node)
    return false;
  new_node->value = value;

  if (NULL == sll->head) {
    new_node->next = NULL;
    sll->head = new_node;
    sll->tail = new_node;
    sll->size = 1U;
  } else {
    new_node->next = sll->head;
    sll->head = new_node;
    ++sll->size;
  }

  return true;
}

bool insert_node_at_the_end(sll_t* sll, const int value) {
  node_t* new_node = (node_t*)malloc(sizeof(node_t));
  if (NULL == new_node)
    return false;
  new_node->value = value;
  new_node->next = NULL;

  if (NULL == sll->head) {
    sll->head = new_node;
    sll->tail = new_node;
    sll->size = 1U;
  } else {
    node_t* current = sll->tail;
    current->next = new_node;
    sll->tail = new_node;
    ++sll->size;
  }

  return true;
}

bool insert_node_at_specified_position(sll_t* sll,
                                       const int value,
                                       const unsigned pos) {
  if (0U == pos || pos > sll->size)
    return false;

  if (NULL == sll->head) {
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    if (NULL == new_node)
      return false;
    new_node->value = value;
    new_node->next = NULL;
    sll->head = new_node;
    sll->tail = new_node;
    sll->size = 1U;
  } else {
    unsigned current_pos = 1U;
    node_t* current = sll->head;
    while (current_pos < pos && NULL != current->next) {
      current = current->next;
      ++current_pos;
    }

    if (current_pos < pos)
      return false;

    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    if (NULL == new_node)
      return false;
    new_node->value = value;
    new_node->next = current->next;
    current->next = new_node;
    ++sll->size;
  }

  return true;
}

bool delete_first_node(sll_t* sll) {
  if (NULL == sll->head)
    return false;

  node_t* current = sll->head;
  sll->head = current->next;
  free(current);
  if (NULL == sll->head)
    sll->tail = NULL;

  --sll->size;
  return true;
}

bool delete_last_node(sll_t* sll) {
  if (NULL == sll->head)
    return false;

  if (NULL == sll->head->next) {
    free(sll->head);
    sll->head = NULL;
    sll->tail = NULL;
    sll->size = 0U;
    return true;
  }

  node_t *current = sll->head, *prev;
  while (NULL != current->next) {
    prev = current;
    current = current->next;
  }

  prev->next = NULL;
  free(current);
  sll->tail = prev;
  --sll->size;
  return true;
}

bool delete_node_at_specified_position(sll_t* sll, const unsigned pos) {
  if (NULL == sll->head || 0U == pos || pos > sll->size)
    return false;

  if (1U == pos)
    return delete_first_node(sll);

  if (pos == sll->size)
    return delete_last_node(sll);

  node_t *current = sll->head, *prev;
  unsigned i = 1U;
  while (NULL != current->next && i < pos) {
    prev = current;
    current = current->next;
    ++i;
  }

  if (pos == i) {
    prev->next = current->next;
    free(current);
    --sll->size;
    return true;
  }

  return false;
}

void destroy_singly_linked_list(sll_t* sll) {
  node_t* current = sll->head;

  while (current != NULL) {
    node_t* next_node = current->next;
    current->next = NULL;
    free(current);
    current = next_node;
  }

  sll->head = NULL;
  sll->tail = NULL;
  sll->size = 0U;
}

bool reverse_singly_linked_list_in_place(sll_t* sll) {
  if (NULL == sll->head)
    return false;

  node_t *previous = NULL, *current = sll->head, *next_node = sll->head;
  sll->tail = sll->head;

  while (NULL != next_node) {
    next_node = next_node->next;

    current->next = previous;

    previous = current;

    current = next_node;
  }

  sll->head = previous;

  return true;
}

sll_t create_reversed_copy_of_specified_singly_linked_list(const sll_t* sll) {
  sll_t new_sll = {0};
  const node_t* current = sll->head;

  while (NULL != current) {
    insert_node_at_the_beginning(&new_sll, current->value);
    current = current->next;
  }

  return new_sll;
}
