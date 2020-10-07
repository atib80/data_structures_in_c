#ifndef _SINGLY_LINKED_LIST_H_
#define _SINGLY_LINKED_LIST_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define sll_node(type) type##_node
#define sll_node_t(type) type##_node_t
#define sll_t(type) type##_sll_t
#define singly_linked_list_t(type) type##_sll_t

#define define_singly_linked_list(type)                                      \
  typedef type item_type;                                                    \
  typedef struct sll_node(type) {                                            \
    item_type value;                                                         \
    struct sll_node(type) * next;                                            \
  }                                                                          \
  sll_node_t(type);                                                          \
  typedef struct {                                                           \
    sll_node_t(type) * head;                                                 \
    sll_node_t(type) * tail;                                                 \
    unsigned size;                                                           \
  } sll_t(type);                                                             \
                                                                             \
  void print(const sll_t(type) * sll, const char* sep, const char* prefix,   \
             const char* suffix) {                                           \
    const sll_node_t(type)* current = sll->head;                             \
    printf(prefix);                                                          \
    while (NULL != current) {                                                \
      printf("%d%s", current->value, NULL != current->next ? sep : suffix);  \
      current = current->next;                                               \
    }                                                                        \
  }                                                                          \
                                                                             \
  bool insert_node_at_the_beginning(sll_t(type) * sll, const int value) {    \
    sll_node_t(type)* new_node =                                             \
        (sll_node_t(type)*)malloc(sizeof(sll_node_t(type)));                 \
    if (NULL == new_node)                                                    \
      return false;                                                          \
    new_node->value = value;                                                 \
    if (NULL == sll->head) {                                                 \
      new_node->next = NULL;                                                 \
      sll->head = new_node;                                                  \
      sll->tail = new_node;                                                  \
      sll->size = 1U;                                                        \
    } else {                                                                 \
      new_node->next = sll->head;                                            \
      sll->head = new_node;                                                  \
      ++sll->size;                                                           \
    }                                                                        \
    return true;                                                             \
  }                                                                          \
                                                                             \
  bool insert_node_at_the_end(sll_t(type) * sll, const int value) {          \
    sll_node_t(type)* new_node =                                             \
        (sll_node_t(type)*)malloc(sizeof(sll_node_t(type)));                 \
    if (NULL == new_node)                                                    \
      return false;                                                          \
    new_node->value = value;                                                 \
    new_node->next = NULL;                                                   \
    if (NULL == sll->head) {                                                 \
      sll->head = new_node;                                                  \
      sll->tail = new_node;                                                  \
      sll->size = 1U;                                                        \
    } else {                                                                 \
      sll_node_t(type)* current = sll->tail;                                 \
      current->next = new_node;                                              \
      sll->tail = new_node;                                                  \
      ++sll->size;                                                           \
    }                                                                        \
    return true;                                                             \
  }                                                                          \
                                                                             \
  bool insert_node_at_specified_position(sll_t(type) * sll, const int value, \
                                         const unsigned pos) {               \
    if (0U == pos || pos > sll->size)                                        \
      return false;                                                          \
    if (NULL == sll->head) {                                                 \
      sll_node_t(type)* new_node =                                           \
          (sll_node_t(type)*)malloc(sizeof(sll_node_t(type)));               \
      if (NULL == new_node)                                                  \
        return false;                                                        \
      new_node->value = value;                                               \
      new_node->next = NULL;                                                 \
      sll->head = new_node;                                                  \
      sll->tail = new_node;                                                  \
      sll->size = 1U;                                                        \
    } else {                                                                 \
      unsigned current_pos = 1U;                                             \
      sll_node_t(type)* current = sll->head;                                 \
      while (current_pos < pos && NULL != current->next) {                   \
        current = current->next;                                             \
        ++current_pos;                                                       \
      }                                                                      \
      if (current_pos < pos)                                                 \
        return false;                                                        \
      sll_node_t(type)* new_node =                                           \
          (sll_node_t(type)*)malloc(sizeof(sll_node_t(type)));               \
      if (NULL == new_node)                                                  \
        return false;                                                        \
      new_node->value = value;                                               \
      new_node->next = current->next;                                        \
      current->next = new_node;                                              \
      ++sll->size;                                                           \
    }                                                                        \
    return true;                                                             \
  }                                                                          \
                                                                             \
  bool delete_first_node(sll_t(type) * sll) {                                \
    if (NULL == sll->head)                                                   \
      return false;                                                          \
    sll_node_t(type)* current = sll->head;                                   \
    sll->head = current->next;                                               \
    free(current);                                                           \
    if (NULL == sll->head)                                                   \
      sll->tail = NULL;                                                      \
    --sll->size;                                                             \
    return true;                                                             \
  }                                                                          \
                                                                             \
  bool delete_last_node(sll_t(type) * sll) {                                 \
    if (NULL == sll->head)                                                   \
      return false;                                                          \
    if (NULL == sll->head->next) {                                           \
      free(sll->head);                                                       \
      sll->head = NULL;                                                      \
      sll->tail = NULL;                                                      \
      sll->size = 0U;                                                        \
      return true;                                                           \
    }                                                                        \
    sll_node_t(type)* current = sll->head, *prev;                            \
    while (NULL != current->next) {                                          \
      prev = current;                                                        \
      current = current->next;                                               \
    }                                                                        \
    prev->next = NULL;                                                       \
    free(current);                                                           \
    sll->tail = prev;                                                        \
    --sll->size;                                                             \
    return true;                                                             \
  }                                                                          \
                                                                             \
  bool delete_node_at_specified_position(sll_t(type) * sll,                  \
                                         const unsigned pos) {               \
    if (NULL == sll->head || 0U == pos || pos > sll->size)                   \
      return false;                                                          \
    if (1U == pos)                                                           \
      return delete_first_node(sll);                                         \
    if (pos == sll->size)                                                    \
      return delete_last_node(sll);                                          \
    sll_node_t(type)* current = sll->head, *prev;                            \
    unsigned i = 1U;                                                         \
    while (NULL != current->next && i < pos) {                               \
      prev = current;                                                        \
      current = current->next;                                               \
      ++i;                                                                   \
    }                                                                        \
    if (pos == i) {                                                          \
      prev->next = current->next;                                            \
      free(current);                                                         \
      --sll->size;                                                           \
      return true;                                                           \
    }                                                                        \
    return false;                                                            \
  }                                                                          \
                                                                             \
  void destroy_singly_linked_list(sll_t(type) * sll) {                       \
    sll_node_t(type)* current = sll->head;                                   \
    while (current != NULL) {                                                \
      sll_node_t(type)* next_node = current->next;                           \
      current->next = NULL;                                                  \
      free(current);                                                         \
      current = next_node;                                                   \
    }                                                                        \
    sll->head = NULL;                                                        \
    sll->tail = NULL;                                                        \
    sll->size = 0U;                                                          \
  }                                                                          \
                                                                             \
  bool reverse_singly_linked_list_in_place(sll_t(type) * sll) {              \
    if (NULL == sll->head)                                                   \
      return false;                                                          \
    sll_node_t(type)* previous = NULL, *current = sll->head,                 \
                      *next_node = sll->head;                                \
    sll->tail = sll->head;                                                   \
    while (NULL != next_node) {                                              \
      next_node = next_node->next;                                           \
      current->next = previous;                                              \
      previous = current;                                                    \
      current = next_node;                                                   \
    }                                                                        \
    sll->head = previous;                                                    \
    return true;                                                             \
  }                                                                          \
                                                                             \
  sll_t(type) create_reversed_copy_of_specified_singly_linked_list(          \
      const sll_t(type) * sll) {                                             \
    sll_t(type) new_sll = {0};                                               \
    const sll_node_t(type)* current = sll->head;                             \
    while (NULL != current) {                                                \
      insert_node_at_the_beginning(&new_sll, current->value);                \
      current = current->next;                                               \
    }                                                                        \
    return new_sll;                                                          \
  }

#endif /* _SINGLY_LINKED_LIST_H_ */